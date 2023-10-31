#include <iostream>
#include <fstream>
#include <vector>

#include "utils.hpp"

using namespace std;

class RangePair {
    private:
        tuple<int, int> range1;
        tuple<int, int> range2;

        static tuple<int, int> str_to_pair(string s) {
            int hpos = s.find('-');
            int start = stoi(s.substr(0, hpos));
            int end = stoi(s.substr(hpos+1));
            return make_tuple(start, end);
        }
    
    public:
        RangePair(string s) {
            int cpos = s.find(',');
            range1 = str_to_pair(s.substr(0, cpos));
            range2 = str_to_pair(s.substr(cpos+1));
        }

        bool contains_subset() {
            return (get<0>(range1) <= get<0>(range2) 
                && get<1>(range1) >= get<1>(range2))
                || (get<0>(range2) <= get<0>(range1) 
                && get<1>(range2) >= get<1>(range1));
        }

        bool contains_overlap() {
            int s1 = get<0>(range1);
            int s2 = get<0>(range2);
            int e1 = get<1>(range1);
            int e2 = get<1>(range2);

            return (s1 >= s2 && s1 <= e2) 
                || (e1 >= s2 && e1 <= e2)
                || (s1 <= s2 && e1 >= e2);
        }
};

int part1(vector<RangePair> rpairs) {
    return pcount(rpairs, (std::function<bool(RangePair)>) [](RangePair rp) -> bool {
        return rp.contains_subset();
    });
}

int part2(vector<RangePair> rpairs) {
    return pcount(rpairs, (std::function<bool(RangePair)>) [](RangePair rp) -> bool {
        return rp.contains_overlap();
    });
}

int main(int argc, char *argv[]) {
    ifstream file("../aoc2022/input_files/day04.txt");
    string line;
    vector<RangePair> rpairs;
    if (file.is_open()) {
        while (getline(file, line)) {
            rpairs.push_back(RangePair(line));
        }
    }

    int p1 = part1(rpairs);
    int p2 = part2(rpairs);

    cout << "*** 2022 Day 4 ***" << endl;
    cout << "Part 1: " << p1 << endl;
    cout << "Part 2: " << p2 << endl;
}
