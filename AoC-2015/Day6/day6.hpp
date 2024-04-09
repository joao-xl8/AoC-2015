#ifndef day6_hpp
#define day6_hpp

#include <stdio.h>
#include <string>
#include <array>
#include <fstream>
#include <iostream>

// Because your neighbors keep defeating you in the holiday house decorating contest year after year, you've decided to deploy one million lights in a 1000x1000 grid.

//Furthermore, because you've been especially nice this year, Santa has mailed you instructions on how to display the ideal lighting configuration.
//
//Lights in your grid are numbered from 0 to 999 in each direction; the lights at each corner are at 0,0, 0,999, 999,999, and 999,0. The instructions include whether to turn on, turn off, or toggle various inclusive ranges given as coordinate pairs. Each coordinate pair represents opposite corners of a rectangle, inclusive; a coordinate pair like 0,0 through 2,2 therefore refers to 9 lights in a 3x3 square. The lights all start turned off.
//
//To defeat your neighbors this year, all you have to do is set up your lights by doing the instructions Santa sent you in order.
//
//For example:
//
//turn on 0,0 through 999,999 would turn on (or leave on) every light.
//toggle 0,0 through 999,0 would toggle the first line of 1000 lights, turning off the ones that were on, and turning on the ones that were off.
//turn off 499,499 through 500,500 would turn off (or leave off) the middle four lights.

// PART TWO
//The light grid you bought actually has individual brightness controls; each light can have a brightness of zero or more. The lights all start at zero.
//
//The phrase turn on actually means that you should increase the brightness of those lights by 1.
//
//The phrase turn off actually means that you should decrease the brightness of those lights by 1, to a minimum of zero.
//
//The phrase toggle actually means that you should increase the brightness of those lights by 2.
//
//What is the total brightness of all lights combined after following Santa's instructions?

enum type_instruction {
    TOGGLE,
    TURN_ON,
    TURN_OFF
};

struct instruction {
    type_instruction type;
    int from_x;
    int from_y;
    int to_x;
    int to_y;
    
    instruction(std::string instruction_str) {
        std::vector<std::string> commands;
        std::string st;
        for (int k = 0; k <= instruction_str.size(); k++) {
            
            if(instruction_str[k] != *" "){
                st.push_back(instruction_str[k]);
            }
            if(instruction_str[k] == *" " || k == instruction_str.size() - 1){
                commands.push_back(st);
                st.clear();
            }
        }
        for(int k = 0; k <= commands.size(); k++){
            std::string command = commands[k];
            if (k == 0) {
                if (command == "toggle") {
                    type = type_instruction::TOGGLE;
                } else {
                    if(commands[k+1] == "on"){
                        type = type_instruction::TURN_ON;
                    } else {
                        type = type_instruction::TURN_OFF;
                    }
                }
            }
            
            switch (type) {
                case type_instruction::TOGGLE:{
//                    std::cout << commands[1] << commands[3] << std::endl;
                    auto from_t = convertStrToPosition(commands[1]);
                    from_x = from_t.first;
                    from_y = from_t.second;
                    auto to_t = convertStrToPosition(commands[3]);
                    to_x = to_t.first;
                    to_y = to_t.second;
                    break;
                }
                default: {
//                    std::cout << commands[1] << commands[2] << commands[4] << \ std::endl;
                    auto from = convertStrToPosition(commands[2]);
                    from_x = from.first;
                    from_y = from.second;
                    auto to = convertStrToPosition(commands[4]);
                    to_x = to.first;
                    to_y = to.second;
                    break;
                }
            }
        }
    }
    
    std::pair<int, int> convertStrToPosition(std::string str) {
        std::string st;
        int first_pos;
        int second_pos;
        for (int i = 0; i < str.size(); i++) {
            if(str[i] == *"," || i == str.size()){
                first_pos = std::stoi(st);
                st.clear();
            }
            if (str[i] != *",") {
                st.push_back(str[i]);
            }
        }
        second_pos = std::stoi(st);
        
        std::pair<int, int> result{ first_pos, second_pos };
        return result;
    }
};

class PuzzleSolverDay6 {
public:
    PuzzleSolverDay6() {
        for(int i = 0; i < g.size();i++){
            for(int j = 0; j < g.size(); j++) {
                g[i][j] = 0;
            }
        }
    };
    
    ~PuzzleSolverDay6() {};
    
    void loadInstructions (){
        std::fstream instructions_file;
        instructions.clear();
        instructions_file.open("Day6/instructions.txt", std::ios::in);
        
        if(instructions_file.is_open()){
            std::string line;
            while (std::getline(instructions_file, line)) {
                instruction k(line);
                
                instructions.push_back(k);
            }
        }
        instructions_file.close();
    }
    
    void execute(instruction i){
        for (int x = i.from_x; x <= i.to_x; x++) {
            for (int y = i.from_y;  y <= i.to_y; y++) {
                switch (i.type) {
                    case type_instruction::TOGGLE:
                        g[x][y] = g[x][y] + 2;
                        break;
                    case type_instruction::TURN_OFF:
                        if (g[x][y] > 0) {
                            g[x][y]--;
                        }
                        break;
                    case type_instruction::TURN_ON:
                        g[x][y]++;
                        break;
                    default:
                        break;
                }
            }
        }
    }
    
    int resolveSumOfLights () {
        for(auto i: instructions){
            execute(i);
        }
        
        int sum_lights = 0;
        
        std::cout << g.size() << std::endl;
        for(int i = 0; i < g.size();i++){
            for(int j = 0; j < g.size(); j++) {
                sum_lights += g[i][j];
                
            }
        }
        return sum_lights;
    };
private:
    std::array<std::array<int, 1000>, 1000> g;
    std::vector<instruction> instructions;
};

void executeDay6Puzzle();

#endif /* day6_hpp */
