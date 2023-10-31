#include <iostream>
#include <fstream>
#include <sstream>
#include <set>

using namespace std;

int part1 (string input) {
    int i = 3;
    while (i < input.length()) {
        set<char> s({ input[i-3], input[i-2], input[i-1], input[i] });
        if (s.size() == 4) {
            return i + 1;
        }
        i++;
    }
    return -1;
}

int part2 (string input) {
    int i = 14;
    while (i < input.length()) {
        set<char> s;
        for (int j = i - 14; j < i; j++) {
            s.insert(input[j]);
        }
        if (s.size() == 14) {
            return i;
        }
        i++;
    }
    return -1;
}

int main (int argc, char *argv[]) {
    ifstream file("../aoc2022/input_files/day06.txt");
    stringstream buffer;
    buffer << file.rdbuf();
    string input = buffer.str();

    int p1 = part1(input);
    int p2 = part2(input);

    cout << "*** 2022 Day 6 ***" << endl;
    cout << "Part 1: " << p1 << endl;
    cout << "Part 2: " << p2 << endl;
}