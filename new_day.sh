#!/bin/sh
# Generate the boilerplate for a new day solution
#

if [ $# -ne 2 ]; then
    echo Usage: $0 \<year\> \<day\>
    exit 1
fi

year=$1
day=$2

src_dir=aoc$year

if [ ${#day} -ne 2 ]; then
    day=0$day
fi
fname=day$day.cpp

content=$(cat <<-END
#include <iostream>
#include <fstream>


using namespace std;

int part1() {
    return 0;
}

int part2() {
    return 0;
}

int main () {
    ifstream file("../$src_dir/input_files/day$day.txt");

    int p1 = part1();
    int p2 = part2();

    cout << "*** $year Day $day ***" << endl;
    cout << "Part 1: " << p1 << endl;
    cout << "Part 2: " << p2 << endl;
}

END
)

echo "$content" > $src_dir/$fname
