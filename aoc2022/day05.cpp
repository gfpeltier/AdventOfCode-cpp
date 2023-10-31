#include <iostream>
#include <fstream>
#include <vector>
#include <regex>

using namespace std;

class CraneInstruction {
    private:
        int from;
        int to;
        int amount;
        
    public:
        CraneInstruction(string s) {
            regex regexp("move (\\d+) from (\\d+) to (\\d+)");
            smatch match;
            if (!regex_search(s, match, regexp)) {
                throw runtime_error("Invalid crane instruction");
            }
            amount = stoi(match.str(1));
            from = stoi(match.str(2));
            to = stoi(match.str(3));
        }

        int getAmount() { return amount; }
        int getTo() { return to; }
        int getFrom() { return from; }
};

class StacksState {
    private:
        vector<vector<char>> stacks;
    public:
        StacksState(vector<string> desc) {
            string header = desc.back();
            for (int i = 0; i < header.length(); i++) {
                if (isdigit(header[i])) {
                    stacks.push_back(vector<char>());
                    for (auto it = desc.rbegin()++; it != desc.rend(); ++it) {
                        if (isalpha((*it)[i])) {
                            stacks.back().push_back((*it)[i]);
                        }
                    }
                }
            }
        }

        void handle_instruction(CraneInstruction instr) {
            for (int i = 0; i < instr.getAmount(); i++) {
                
                char top = stacks[instr.getFrom()-1].back();
                stacks[instr.getFrom()-1].pop_back();
                stacks[instr.getTo()-1].push_back(top);
            }
        }

        void handle_instruction_multi(CraneInstruction instr) {
            vector<char> nFromStack = vector<char>(
                stacks[instr.getFrom()-1].begin(), 
                stacks[instr.getFrom()-1].end() - instr.getAmount()
            );
            vector<char> moving = vector<char>(
                stacks[instr.getFrom()-1].end() - instr.getAmount(),
                stacks[instr.getFrom()-1].end()
            );
            // Concat moved to destination stack
            stacks[instr.getTo()-1].insert(stacks[instr.getTo()-1].end(), moving.begin(), moving.end());
            stacks[instr.getFrom()-1] = nFromStack;
        }

        vector<char> stack_tops() {
            vector<char> tops;
            for (auto stack : stacks) {
                tops.push_back(stack.back());
            }
            return tops;
        }
};

string part1(StacksState initState, vector<CraneInstruction> instrs) {
    for (auto instr : instrs) {
        initState.handle_instruction(instr);
    }
    vector<char> tops = initState.stack_tops();
    return string(tops.begin(), tops.end());
}

string part2(StacksState initState, vector<CraneInstruction> instrs) {
    for (auto instr : instrs) {
        initState.handle_instruction_multi(instr);
    }
    vector<char> tops = initState.stack_tops();
    return string(tops.begin(), tops.end());
}

int main(int argc, char *argv[]) {
    ifstream file("../aoc2022/input_files/day05.txt");
    string line;
    // Contains stacks state in section 0 and instructions in section 1
    vector<string> sections[2];
    int i = 0;
    if (file.is_open()) {
        while (getline(file, line)) {
            if (line.length() == 0) {
                i = 1;
                continue;
            }
            sections[i].push_back(line);
        }
        file.close();
    }

    vector<CraneInstruction> instrs;
    for (auto it = sections[1].begin(); it != sections[i].end(); it++) {
        instrs.push_back(CraneInstruction(*it));
    }
    StacksState state(sections[0]);

    string p1 = part1(state, instrs);
    string p2 = part2(state, instrs);

    cout << "*** 2022 Day 5 ***" << endl;
    cout << "Part 1: " << p1 << endl;
    cout << "Part 2: " << p2 << endl;
}
