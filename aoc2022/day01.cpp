#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int part1(vector<vector<int>> elves) {
    vector<int> sums;

    for (vector<int> ecals : elves) {
        int sum = 0;
        for (int c : ecals) {
            sum += c;
        }
        sums.push_back(sum);
    }

    int max = 0;
    for (int i : sums) {
        if (i > max) {
            max = i;
        }
    }
    return max;
}

int part2(vector<vector<int>> elves) {
    vector<int> sums;

    for (vector<int> ecals : elves) {
        int sum = 0;
        for (int c : ecals) {
            sum += c;
        }
        sums.push_back(sum);
    }

    sort(sums.rbegin(), sums.rend());
    int topThree = 0;
    for (auto it = sums.begin(); it < sums.begin() + 3; it++) {
        topThree += *it;
    }

    return topThree;
}

int main(int argc, char *argv[]) {
    ifstream file("../aoc2022/input_files/day01.txt");
    string line;
    vector<vector<int>> elves;
    elves.push_back(vector<int>());
    if (file.is_open()) {
        while (getline(file, line)) {
            if (line.length() == 0) {
                elves.push_back(vector<int>());
                continue;
            }
            elves.back().push_back(stoi(line));
        }
        file.close();
    }

    int max = part1(elves);
    int topThree = part2(elves);
    cout << "*** 2022 Day 1 ***" << endl;
    cout << "Part 1: " << max << endl;
    cout << "Part 2: " << topThree << endl;
}
