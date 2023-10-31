#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

enum GamePlay { ROCK, PAPER, SCISSORS };

GamePlay decodeChar(char c) {
    switch (c)
    {
    case 'A':
    case 'X':
        return ROCK;
    case 'B':
    case 'Y':
        return PAPER;
    case 'C':
    case 'Z':
        return SCISSORS;
    default:
        throw runtime_error("Invalid move");
    }
}

class GameRound {
    private:
        GamePlay myPlay;
        GamePlay oppPlay;
    
    public:
        GameRound(GamePlay opp, GamePlay my) {
            oppPlay = opp;
            myPlay = my;
        }

        GameRound(string details) {
            oppPlay = decodeChar(details[0]);
            myPlay = decodeChar(details[2]);
        }

        int score_round() {
            int score = 0;
            if (myPlay == ROCK) {
                score += 1;
                if (oppPlay == SCISSORS) {
                    score += 6;
                } 
            } else if (myPlay == PAPER) {
                score += 2;
                if (oppPlay == ROCK) {
                    score += 6;
                }
            } else {
                score += 3;
                if (oppPlay == PAPER) {
                    score += 6;
                }
            }

            if (myPlay == oppPlay) {
                score += 3;
            }

            return score;
        }
};

GameRound roundFromStrategy(string s) {
    GamePlay oppPlay = decodeChar(s[0]);
    switch (s[2])
    {
    case 'X': // Lose
        switch (oppPlay)
        {
        case ROCK:
            return GameRound(oppPlay, SCISSORS);
        case PAPER:
            return GameRound(oppPlay, ROCK);
        case SCISSORS:
            return GameRound(oppPlay, PAPER);
        }
        break;
    case 'Y': // Draw
        return GameRound(oppPlay, oppPlay);
    case 'Z': // Win
        switch (oppPlay)
        {
        case ROCK:
            return GameRound(oppPlay, PAPER);
        case PAPER:
            return GameRound(oppPlay, SCISSORS);
        case SCISSORS:
            return GameRound(oppPlay, ROCK);
        }
        break;
    default:
        throw runtime_error("Unknown strategy");
    }
    throw runtime_error("Unknown strategy");
}

int part1(vector<string> roundStrs) {
    vector<GameRound> rounds;
    for (auto line : roundStrs) {
        rounds.push_back(GameRound(line));
    }
    int fullScore = 0;
    for (auto round : rounds) {
        fullScore += round.score_round();
    }
    return fullScore;
}

int part2(vector<string> roundStrs) {
    vector<GameRound> rounds;
    for (auto line : roundStrs) {
        rounds.push_back(roundFromStrategy(line));
    }
    int fullScore = 0;
    for (auto round : rounds) {
        fullScore += round.score_round();
    }
    return fullScore;
}

int main(int argc, char *argv[]) {
    ifstream file("../aoc2022/input_files/day02.txt");
    vector<string> roundStrs;
    string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            roundStrs.push_back(line);
        }
        file.close();
    }
    int p1 = part1(roundStrs);
    int p2 = part2(roundStrs);
    cout << "*** 2022 Day 2 ***" << endl;
    cout << "Part 1: " << p1 << endl;
    cout << "Part 2: " << p2 << endl;
}