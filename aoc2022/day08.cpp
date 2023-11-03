#include <iostream>
#include <fstream>
#include <algorithm>
#include <tuple>
#include <vector>

using namespace std;

enum Direction { NORTH, EAST, SOUTH, WEST };

bool is_vis_in_direction(vector<vector<int>> grid, int x, int y, Direction dir) {
    vector<tuple<int, int>> coords;

    switch (dir)
    {
    case NORTH:
        for (int i = 0; i < x; i++) {
            coords.push_back(make_tuple(i, y));
        }
        break;
    case EAST:
        for (int i = y+1; i < grid.front().size(); i++) {
            coords.push_back(make_tuple(x, i));
        }
        break;
    case SOUTH:
        for (int i = x+1; i < grid.size(); i++) {
            coords.push_back(make_tuple(i, y));
        }
        break;
    case WEST:
        for (int i = 0; i < y; i++) {
            coords.push_back(make_tuple(x, i));
        }
        break;
    }

    return all_of(coords.begin(), coords.end(), [&](tuple<int, int> coord) -> bool {
        return grid[get<0>(coord)][get<1>(coord)] < grid[x][y];
    });
}

int part1(vector<vector<int>> grid) {
    int count = 0;

    for (int x = 0; x < grid.size(); x++) {
        for (int y = 0; y < grid.back().size(); y++) {
            if (is_vis_in_direction(grid, x, y, NORTH)
                || is_vis_in_direction(grid, x, y, EAST)
                || is_vis_in_direction(grid, x, y, SOUTH)
                || is_vis_in_direction(grid, x, y, WEST)
            ) {
                count++;
            }
        }
    }

    return count;
}

int count_vis_in_direction(vector<vector<int>> grid, int x, int y, Direction dir) {
    vector<tuple<int, int>> coords;

    switch (dir)
    {
    case NORTH:
        for (int i = (x - 1); i >= 0; i--) {
            coords.push_back(make_tuple(i, y));
        }
        break;
    case EAST:
        for (int i = y+1; i < grid.front().size(); i++) {
            coords.push_back(make_tuple(x, i));
        }
        break;
    case SOUTH:
        for (int i = x+1; i < grid.size(); i++) {
            coords.push_back(make_tuple(i, y));
        }
        break;
    case WEST:
        for (int i = (y - 1); i >= 0; i--) {
            coords.push_back(make_tuple(x, i));
        }
        break;
    }

    int count = 0;
    for (auto coord : coords) {
        if (grid[get<0>(coord)][get<1>(coord)] >= grid[x][y]) {
            return count + 1;
        }
        count++;
    }
    return count;
}

int score_tree(vector<vector<int>> grid, int x, int y) {
    return count_vis_in_direction(grid, x, y, NORTH)
        * count_vis_in_direction(grid, x, y, EAST)
        * count_vis_in_direction(grid, x, y, SOUTH)
        * count_vis_in_direction(grid, x, y, WEST);
}

int part2(vector<vector<int>> grid) {
    int max_score = 0;

    for (int x = 1; x < (grid.size() - 1); x++) {
        for (int y = 1; y < (grid.back().size() - 1); y++) {
            int score = score_tree(grid, x, y);
            if (score > max_score) {
                max_score = score;
            }
        }
    }

    return max_score;
}

int main (int argc, char* argv[]) {
    ifstream file("../aoc2022/input_files/day08.txt");
    vector<vector<int>> grid;
    string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            grid.push_back(vector<int>());
            for (char c : line) {
                grid.back().push_back(c - '0');
            }
        }
    }

    int p1 = part1(grid);
    int p2 = part2(grid);

    cout << "*** 2022 Day 8 ***" << endl;
    cout << "Part 1: " << p1 << endl;
    cout << "Part 2: " << p2 << endl;
}
