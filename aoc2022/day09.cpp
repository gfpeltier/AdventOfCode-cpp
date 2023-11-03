#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <tuple>

using namespace std;

using point = tuple<int, int>;

enum Direction { UP, DOWN, LEFT, RIGHT };

class Step {
    private:
        int distance;
        Direction direction;

    public:
        Step(Direction dir, int dist): distance(dist), direction(dir) {}

        Step(string desc) {
            regex tmpl("([UDLR]) ([0-9]+)");
            smatch match;
            if (!regex_search(desc, match, tmpl)) {
                throw runtime_error("Unknown step");
            }
            switch (match.str(1)[0])
            {
            case 'U':
                direction = UP;
                break;
            case 'D':
                direction = DOWN;
                break;
            case 'L':
                direction = LEFT;
                break;
            case 'R':
                direction = RIGHT;
                break;
            }
            distance = stoi(match.str(2));
        }
};

int get_x(point p) { return get<0>(p); }

int get_y(point p) { return get<1>(p); }

int point_dist(point p1, point p2) {
    return abs(get_x(p2) - get_x(p1)) + abs(get_y(p2) - get_y(p1));
}

int part1() {
    return 0;
}

int part2() {
    return 0;
}

int main () {
    ifstream file("../aoc2022/input_files/day09.txt");
    vector<Step> steps;
    string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            steps.push_back(Step(line));
        }
    }

    int p1 = part1();
    int p2 = part2();

    cout << "*** 2022 Day 9 ***" << endl;
    cout << "Part 1: " << p1 << endl;
    cout << "Part 2: " << p2 << endl;
}
