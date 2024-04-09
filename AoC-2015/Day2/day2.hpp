#ifndef day2_hpp
#define day2_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

//The elves are running low on wrapping paper, and so they need to submit an order for more. They have a list of the dimensions (length l, width w, and height h) of each present, and only want to order exactly as much as they need.
//
//Fortunately, every present is a box (a perfect right rectangular prism), which makes calculating the required wrapping paper for each gift a little easier: find the surface area of the box, which is 2*l*w + 2*w*h + 2*h*l. The elves also need a little extra paper for each present: the area of the smallest side.
//For example:
//
//A present with dimensions 2x3x4 requires 2*6 + 2*12 + 2*8 = 52 square feet of wrapping paper plus 6 square feet of slack, for a total of 58 square feet.
//A present with dimensions 1x1x10 requires 2*1 + 2*10 + 2*10 = 42 square feet of wrapping paper plus 1 square foot of slack, for a total of 43 square feet.

//2*l*w + 2*w*h + 2*h*l + smallest side area

struct dimension {
    int w;
    int h;
    int l;
};

class PuzzleSolverDay2 {
public:
    PuzzleSolverDay2() {
        dimensions.clear();
        
        std::fstream instructions_file;
        instructions_file.open("Day2/instructions.txt", std::ios::in);
        
        if(instructions_file.is_open()){
            std::string line;
            while (std::getline(instructions_file, line )) {
                // LxWxH
                dimension dm;
                if (line.length() <= 0) continue;
                int index_prop = 0;
                std::string string_holder;
                for(int i=0; i <= line.length(); i++){
                    if (line[i] != *"x" && line.length() >= i + 1){
                        string_holder.push_back(line[i]);
                    } else{
                        switch (index_prop) {
                            case 0:
                                dm.l = std::stoi(string_holder);
                                break;
                            case 1:
                                dm.w = std::stoi(string_holder);
                            case 2:
                                dm.h = std::stoi(string_holder);
                            default:
                                break;
                        }
                        index_prop++;
                        string_holder.clear();
                    }
                }
                dimensions.push_back(dm);
            }
        }
        instructions_file.close();
    };
    ~PuzzleSolverDay2() {};
    
    
    unsigned long long int resolveTotalArea() {
        unsigned long long int total = 0;
        for(dimension instruction: dimensions) {
            int sideA = (instruction.l * instruction.w);
            int sideB = (instruction.w * instruction.h);
            int sideC = (instruction.h * instruction.l);
            int* smallestSide = 0;
            
            if( sideA <= sideB && sideA <= sideC){
                smallestSide = &sideA;
            } else if (sideB <= sideA && sideB <= sideC) {
                smallestSide = &sideB;
            } else {
                smallestSide = &sideC;
            }
            unsigned long long int cur_total = (2 * sideA) + (2 * sideB) + (2 * sideC) + *smallestSide;
            total += cur_total;
        }
        return total;
    };
    
    unsigned long long int resolveRibbon() {
        unsigned long long int total = 0;
        for(dimension instruction: dimensions) {
            int* smallestPerimeter = 0;
            int perimeterA = 2 * (instruction.l + instruction.w);
            int perimeterB = 2 * (instruction.l + instruction.h);
            int perimeterC = 2 * (instruction.w + instruction.h);
            int volume = instruction.l * instruction.w * instruction.h;
            if(perimeterA <= perimeterB && perimeterA <= perimeterC){
                smallestPerimeter = &perimeterA;
            }else if(perimeterB <= perimeterA && perimeterB <= perimeterC){
                smallestPerimeter = &perimeterB;
            } else{
                smallestPerimeter = &perimeterC;
            }
            
            unsigned long long int cur_total =  *smallestPerimeter + volume;
            std::cout << cur_total << std::endl;
            total += cur_total;
        }
        return total;
    };
    
private:
    std::string instructions;
    std::vector<dimension> dimensions;
};

void executeDay2Puzzle();

#endif /* day2_hpp */
