#include <map>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

template <typename K, typename V>
set<K> map_keyset(map<K, V> m) {
    set<K> keys;
    for (auto it = m.begin(); it != m.end(); ++it) {
        keys.insert(it->first);
    }
    return keys;
}

template <typename T>
set<T> intersect(set<T> s1, set<T> s2) {
    set<T> out;
    for (auto it = s1.begin(); it != s1.end(); ++it) {
        if(s2.contains(*it)) {
            out.insert(*it);
        }
    }
    return out;
}

char determine_badge_char(vector<map<char, int>> freqList) {
    set<char> common = map_keyset(freqList.back());
    freqList.pop_back();
    for (auto freqs : freqList) {
        common = intersect(common, map_keyset(freqs));
    }
    return *common.begin();
}

map<char, int> character_freqs(string s) {
    map<char, int> freqs;

    for (char c : s) {
        if (freqs.count(c)) {
            freqs[c] += 1;
        } else {
            freqs[c] = 1;
        }
    }

    return freqs;
}

// a-z => 1-26
// A-Z => 27-52
int char_priority(char c) {
    if (int(c) >= int('a')) {
        return int(c) - int('a') + 1;
    }
    return int(c) - int('A') + 27;
}

int part1(vector<string> backpacks) {
    int sum = 0;
    for (string backpack : backpacks) {
        sum += char_priority(determine_badge_char({ 
            character_freqs(backpack.substr(0, backpack.length()/2)),
            character_freqs(backpack.substr(backpack.length()/2))
        }));
    }
    return sum;
}

int part2(vector<string> backpacks) {
    int i = 0;
    vector<vector<map<char, int>>> elfGroups;
    elfGroups.push_back(vector<map<char, int>>());
    for (string line : backpacks) {
        if (i == 3) {
            i = 0;
            elfGroups.push_back(vector<map<char, int>>());
        }
        elfGroups.back().push_back(character_freqs(line));
        i++;
    }
    int sum = 0;
    for (vector<map<char, int>> group : elfGroups) {
        char bc = determine_badge_char(group);
        sum += char_priority(bc);
    }
    return sum;
}

int main(int argc, char *argv[]) {
    ifstream file("../aoc2022/input_files/day03.txt");
    string line;
    vector<string> allLines;
    
    if (file.is_open()) {
        while (getline(file, line)) {
            allLines.push_back(line);
        }
    }

    int p1 = part1(allLines);
    int p2 = part2(allLines);

    cout << "*** 2022 Day 3 ***" << endl;
    cout << "Part 1: " << p1 << endl;
    cout << "Part 2: " << p2 << endl;
}