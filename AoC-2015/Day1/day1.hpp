#ifndef day1_hpp
#define day1_hpp

#include <stdio.h>
#include <string>
#include <iostream>

//Santa is trying to deliver presents in a large apartment building, but he can't find the right floor - the directions he got are a little confusing. He starts on the ground floor (floor 0) and then follows the instructions one character at a time.
//An opening parenthesis, (, means he should go up one floor, and a closing parenthesis, ), means he should go down one floor.
//The apartment building is very tall, and the basement is very deep; he will never find the top or bottom floors.
//For example:
// (()) and ()() both result in floor 0.
// ((( and (()(()( both result in floor 3.
// ))((((( also results in floor 3.
// ()) and ))( both result in floor -1 (the first basement level).
// ))) and )())()) both result in floor -3.
//To what floor do the instructions take Santa?

//infos
// s_floor = 0
// ( = +1 floor
// ) = -1 floor

class PuzzleSolverDay1 {
public:
    PuzzleSolverDay1(std::string& inst) :instructions{inst} {};
    ~PuzzleSolverDay1() {};
    
    int resolveFinalPos() {
        int pos = 0;
        for (auto &ch : instructions) {
            if (ch == *"(") {
                pos++;
            } else if (ch == *")") {
                pos--;
            }
        }
        return pos;
    };
    
    int resolveIndexEnterBasement() {
        int pos = 0;
        
        for (int i = 0; i < instructions.length(); i++) {
            if (pos < 0) return i;
            if (instructions[i] == *"(") {
                pos++;
            } else if (instructions[i] == *")") {
                pos--;
            }
        }
        return -1;
    }
    std::string parse(int target, int n_moves) const;
private:
    std::string instructions;
};

void executeDay1Puzzle ();

#endif /* day1_hpp */
