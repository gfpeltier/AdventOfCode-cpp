#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <algorithm>
#include <sstream>
#include <queue>
#include <limits.h>

using namespace std;

class EmuFile {
    private:
        string name;
        EmuFile* parent;
        vector<EmuFile*> children;
        int size;

    public:
        EmuFile(string fname): name(fname), parent(NULL), size(0) {}

        EmuFile(string fname, EmuFile* fparent): name(fname), parent(fparent), size(0) {}

        EmuFile(string fname, EmuFile* fparent, int fsize): name(fname), parent(fparent), size(fsize) {}

        string getName() { return name; }

        void setParent(EmuFile* parent) { this->parent = parent; }

        EmuFile* getParent() { return this->parent; }

        vector<EmuFile*> getChildren() { return children; }

        void addChild(EmuFile* child) {
            child->setParent(this);
            children.push_back(child);
        }

        bool isDir() { return size == 0; }

        string getLocation() {
            stringstream stream;

            if (parent != NULL) {
                stream << parent->getLocation();
            }
            stream << name << "/";
            return stream.str();
        }

        int getSize() {
            if (children.size() > 0) {
                int totalSize = 0;
                for (auto child : children) {
                    totalSize += child->getSize();
                }
                return totalSize;
            } else {
                return size;
            }
        }

        void printChildren() {
            stringstream ss;
            ss << name << " children: " << endl;
            for (auto child : children) {
                ss << "    " << child->getName() << endl;
            }
            cout << ss.str() << endl;
        }
};

EmuFile parse_commands(vector<vector<string>> commands) {
    EmuFile* root = new EmuFile("/");
    EmuFile* cwd = root;
    regex cdCommand("\\$ cd ([\\/\\w\\.]+)");
    regex outDir("dir (\\w+)");
    regex outFile("([0-9]+) ([\\w\\.]+)");

    smatch match;

    for (auto it = commands.begin() + 1; it != commands.end(); ++it) {
        string cmd = it->front();
        if (regex_search(cmd, match, cdCommand)) {
            string dest = match.str(1);
            if (dest == "..") {
                cwd = cwd->getParent();
            } else {
                vector<EmuFile*> currChildren = cwd->getChildren();
                if (
                    auto fit = find_if(currChildren.begin(), currChildren.end(), [dest](EmuFile* f) -> bool {
                        return f->getName() == dest;
                    }); 
                    fit != cwd->getChildren().end()
                ) {
                    cwd = *fit;
                } else {
                    EmuFile* child = new EmuFile(dest, cwd);
                    cwd->addChild(child);
                    cwd = child;
                }
            }
        } else if (cmd == "$ ls") {
            for (auto oit = it->begin() + 1; oit != it->end(); ++oit) {
                if (regex_search(*oit, match, outDir)) {  // child dir
                    string dirName = match.str(1);
                    EmuFile* dchild = new EmuFile(dirName, cwd);
                    cwd->addChild(dchild);
                } else if (regex_search(*oit, match, outFile)) { // child file
                    int fsize = stoi(match.str(1));
                    string fname = match.str(2);
                    EmuFile* fchild = new EmuFile(fname, cwd, fsize);
                    cwd->addChild(fchild);
                } else {
                    throw runtime_error("Unrecognized ls output");
                }
            }
        } else {
            throw runtime_error("Unrecognized command '" + cmd + "'");
        }
    }

    return *root;
}

int part1(EmuFile fsys) {
    int sumSize = 0; 
    queue<EmuFile> q({ fsys });
    while (!q.empty()) {
        EmuFile curr = q.front();
        q.pop();
        for (auto child : curr.getChildren()) {
            if (child->isDir()) {
                q.push(*child);
            }
        }
        if (curr.getSize() < 100000) {
            sumSize += curr.getSize();
        }
    }
    return sumSize;
}

int part2(EmuFile fsys) {
    const int totalSpace = 70000000;
    const int spaceRequired = 30000000;
    const int usedSpace = fsys.getSize();
    const int spaceRemaining = totalSpace - usedSpace;
    const int spaceToFree = spaceRequired - spaceRemaining;

    int freed = INT_MAX;
    queue<EmuFile> q({ fsys });
    while (!q.empty()) {
        EmuFile curr = q.front();
        q.pop();
        for (auto child : curr.getChildren()) {
            if (child->isDir()) {
                q.push(*child);
            }
        }
        int dirSize = curr.getSize();
        if (dirSize > spaceToFree && dirSize < freed) {
            freed = dirSize;
        }
    }

    return freed;
}

int main(int argc, char *argv[]) {
    vector<vector<string>> commands;
    ifstream file("../aoc2022/input_files/day07.txt");
    string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            if (line[0] == '$') {
                commands.push_back(vector<string>());
            }
            commands.back().push_back(line);
        }
    }

    EmuFile fsys = parse_commands(commands);

    int p1 = part1(fsys);
    int p2 = part2(fsys);

    cout << "*** 2022 Day 7 ***" << endl;
    cout << "Part 1: " << p1 << endl;
    cout << "Part 2: " << p2 << endl;
}
