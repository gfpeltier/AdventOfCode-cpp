#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <algorithm>
#include <sstream>

using namespace std;

class EmuFile {
    private:
        string name;
        EmuFile* parent;
        vector<EmuFile*> children;
        int size = 0;

    public:
        EmuFile(string fname): name(fname), parent(NULL) {}

        EmuFile(string fname, EmuFile* fparent): name(fname), parent(fparent) {}

        EmuFile(string fname, EmuFile* fparent, int fsize): name(fname), parent(fparent), size(fsize) {}

        string getName() { return name; }

        void setParent(EmuFile* parent) { this->parent = parent; }

        EmuFile* getParent() { return this->parent; }

        vector<EmuFile*> getChildren() { return children; }

        void addChild(EmuFile* child) {
            child->setParent(this);
            children.push_back(child);
        }

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
            cout << "CWD: " << cwd->getName() << endl;
            if (cwd->getName() != root->getName()) {
                cout << "Parent: " << cwd->getParent()->getName() << endl;
            }
            cout << "full path: " << cwd->getLocation() << endl;
            cout << "Moving to: " << dest << endl;
            cwd->printChildren();
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
                    EmuFile child = **fit;
                    cwd = &child;
                    cout << "New CWD: " << cwd->getLocation() << endl;
                } else {
                    EmuFile* child = new EmuFile(dest, cwd);
                    cout << "New parent 0: " << (*child).getParent()->getName() << endl;
                    cwd->addChild(child);
                    cwd->printChildren();
                    cwd = child;
                    cout << "New child: " << (*child).getName() << endl;
                    cout << "New parent: " << (*child).getParent()->getName() << endl;
                }
            }
        } else if (cmd == "$ ls") {
            cout << "CWD: " << cwd->getName() << endl;
            cout << "listing files in " << cwd->getLocation() << endl;
            for (auto oit = it->begin() + 1; oit != it->end(); ++oit) {
                if (regex_search(*oit, match, outDir)) {  // child dir
                    cout << "Cwd ptr start 0: " << cwd << endl;
                    cout << "PWD start: " << cwd->getName() << endl;
                    cout << "Cwd ptr start 1: " << cwd << endl;
                    string dirName = match.str(1);
                    EmuFile* dchild = new EmuFile(dirName, cwd);
                    cout << "PWD made child: " << cwd->getName() << endl;
                    cwd->addChild(dchild);
                    cout << "New child dir: " << dchild->getName() << endl;
                    cout << "New parent dir: " << dchild->getParent()->getName() << endl;
                    cout << "PWD after: " << cwd->getName() << endl;
                    cout << "Child ptr: " << dchild << endl;
                    cout << "Cwd ptr: " << cwd << endl;
                } else if (regex_search(*oit, match, outFile)) { // child file
                    int fsize = stoi(match.str(1));
                    string fname = match.str(2);
                    EmuFile* fchild = new EmuFile(fname, cwd, fsize);
                    cout << "New child file: " << fchild->getName() << endl;
                    cout << "New file parent: " << fchild->getParent()->getName() << endl;
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

int part1() {
    return 0;
}

int part2() {
    return 0;
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

    cout << "Total size: " << fsys.getSize() << endl;
    cout << "Num children: " << fsys.getChildren().size() << endl;

    int p1 = part1();
    int p2 = part2();

    cout << "*** 2022 Day 7 ***" << endl;
    cout << "Part 1: " << p1 << endl;
    cout << "Part 2: " << p2 << endl;
}