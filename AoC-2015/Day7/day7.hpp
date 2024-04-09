#ifndef day7_hpp
#define day7_hpp

#include <stdio.h>
#include <string>
#include <array>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>

typedef unsigned short SIXTEEN_BIT_I;

// 16-bit (0000000000000000)
const SIXTEEN_BIT_I INITIAL_VALUE = 0;

class PuzzleSolverDay7 {
public:
    PuzzleSolverDay7() {};
    ~PuzzleSolverDay7() {};
    
    void loadAndExecute () {
        std::fstream instructions_file;
        instructions_file.open("Day7/instructions.txt", std::ios::in);
        
        circuit.clear();
        if(instructions_file.is_open()){
            std::string line;
            while (std::getline(instructions_file, line)) {
                // split by space and store in vector
                std::vector<std::string> elements;
                std::string str_elem;
                std::istringstream iss(line);
                while (std::getline(iss, str_elem, ' ')) {
                    elements.push_back(str_elem);
                }
                
                //NOT x -> h
                if (elements[0] == "NOT" && circuit.count(elements[1]) > 0) {
                    circuit[elements[3]] = (~circuit[elements[1]]);
                }
                
                //123 -> x
                //y -> x
                if(elements[1] == "->" && (isdigit(elements[0][0]) || circuit.count(elements[0]) > 0)){
                    SIXTEEN_BIT_I first_value = isdigit(elements[0][0]) ? std::stoi(elements[0]) : circuit[elements[0]];
                    circuit[elements[2]] = first_value;
                }
                
                //y RSHIFT 2 -> g
                //y LSHIFT 2 -> g
                if((elements[1] == "RSHIFT" || elements[1] == "LSHIFT") && circuit.count(elements[0]) > 0 ) {
                    SIXTEEN_BIT_I offset = std::stoi(elements[2]);
                    if(elements[1] == "RSHIFT") {
                        circuit[elements[4]] = (circuit[elements[0]] >> offset);
                    } else{
                        circuit[elements[4]] = (circuit[elements[0]] << offset);
                    }

                }
                
                //y AND x -> g
                //y OR x -> g
                //123 AND x -> g
                //y OR 123 -> g
                if ((elements[1] == "AND" || elements[1] == "OR")) {
                    if((!isdigit(elements[0][0]) && circuit.count(elements[0]) == 0)
                        || (!isdigit(elements[2][0]) && circuit.count(elements[2]) == 0)) continue;
                    SIXTEEN_BIT_I first_value = isdigit(elements[0][0]) ? std::stoi(elements[0]) : circuit[elements[0]];
                    SIXTEEN_BIT_I second_value = isdigit(elements[2][0]) ? std::stoi(elements[2]) : circuit[elements[2]];
                    if(elements[1] == "AND"){
                        circuit[elements[4]] = (first_value & second_value);
                    } else {
                        circuit[elements[4]] = (first_value | second_value);
                    }
                }
            }
        }
        instructions_file.close();
    };
    
    void iterateOverCircuit() {
        for(auto it = circuit.cbegin(); it != circuit.cend(); ++it){
            std::cout << "wire: " << it->first << ", value: " << it->second << std::endl;
        }
    }
    
    SIXTEEN_BIT_I getValue(std::string search){
        return circuit[search];
    };
private:
    // wire : (identifier, value)
    std::map<std::string, SIXTEEN_BIT_I> circuit;
};

void executeDay7Puzzle();
#endif /* day7_hpp */
