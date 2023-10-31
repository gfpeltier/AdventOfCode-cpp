#include <iostream>
#include <fstream>
#include <vector>
#include <regex>

using namespace std;

class EmuFile {
    public:
        virtual string getName();
        virtual int getSize();
        virtual EmuFile getParent();
};

EmuFile parse_commands(vector<vector<string>> commands) {
    regex cdCommand("$ cd ([\\w\\.]+)");
    regex lsCommand("$ ls");
    regex outDir("dir (\\w+)");
    regex outFile("([0-9]+) ([\\w\\.]+)");


}

int part1() {}

int part2() {}

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

    int p1 = part1();
    int p2 = part2();

    cout << "*** 2022 Day 7 ***" << endl;
    cout << "Part 1: " << p1 << endl;
    cout << "Part 2: " << p2 << endl;
}