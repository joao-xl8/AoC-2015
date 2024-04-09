#ifndef day3_hpp
#define day3_hpp

#include <stdio.h>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <iostream>

struct position {
    int x;
    int y;
};

class PuzzleSolverDay3 {
public:
    PuzzleSolverDay3() {
        std::fstream instructions_file;
        instructions.clear();
        instructions_file.open("Day3/instructions.txt", std::ios::in);
        
        if(instructions_file.is_open()){
            std::string line;
            while (std::getline(instructions_file, line )) {
                instructions += line;
            }
        }
        instructions_file.close();
        pos.x = 0;
        pos.y = 0;
        robot_pos.x = 0;
        robot_pos.y = 0;
        houses_visited.clear();
    };
    ~PuzzleSolverDay3() {};
    
    int assertNewPos(std::map<std::string,int>& hv, bool santas_turn) {
        if (santas_turn) {
            if (hv.find(std::string(std::to_string(pos.x)+";"+std::to_string(pos.y))) == hv.end()) {
                hv[std::string(std::to_string(pos.x)+";"+std::to_string(pos.y))] = 1;
                return 1;
            } else {
                hv[std::string(std::to_string(pos.x)+";"+std::to_string(pos.y))] += 1;
            }
        }else {
            if (hv.find(std::string(std::to_string(robot_pos.x)+";"+std::to_string(robot_pos.y))) == hv.end()) {
                hv[std::string(std::to_string(robot_pos.x)+";"+std::to_string(robot_pos.y))] = 1;
                return 1;
            } else {
                hv[std::string(std::to_string(robot_pos.x)+";"+std::to_string(robot_pos.y))] += 1;
            }
        }
       
        return 0;
    }
    
    int resolveAtLeastOnePresent() {
        int sum = 0;
        for (auto& instruction: instructions) {
            if (instruction == *"^"){
                pos.y++;
            } else if (instruction == *"v"){
                pos.y--;
            } else if (instruction == *">"){
                pos.x++;
            } else if (instruction == *"<"){
                pos.x--;
            }
//            std::cout << pos.x <<  " " << pos.y << std::endl;
            sum += assertNewPos(houses_visited, true);
        }
        return sum;
    }
    
    int resolveAtLeastOnePresentWithRobot() {
        int sum = 0;
        bool santas_turn = true;
        for (auto& instruction: instructions) {
            if(santas_turn){
                if (instruction == *"^"){
                    pos.y++;
                } else if (instruction == *"v"){
                    pos.y--;
                } else if (instruction == *">"){
                    pos.x++;
                } else if (instruction == *"<"){
                    pos.x--;
                }
            }else {
                if (instruction == *"^"){
                    robot_pos.y++;
                } else if (instruction == *"v"){
                    robot_pos.y--;
                } else if (instruction == *">"){
                    robot_pos.x++;
                } else if (instruction == *"<"){
                    robot_pos.x--;
                }
            }
           
            std::cout << pos.x <<  " " << pos.y << std::endl;
            sum += assertNewPos(houses_visited, santas_turn);
            santas_turn = !santas_turn;
        }
        return sum;
    }
    
private:
    position pos;
    position robot_pos;
    std::map<std::string, int> houses_visited;
    std::string instructions;
};

void executeDay3Puzzle();

#endif /* day3_hpp */
