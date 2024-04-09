//
//  day2.cpp
//  AoC-2015
//
//  Created by João Paulo Arnold Barros on 05/10/23.
//

#include "day2.hpp"
#define PRINT(X) std::cout << X << std::endl

void executeDay2Puzzle(){
    
    PuzzleSolverDay2 ps{};
//    int result = ps.resolveFinalPos();
    unsigned long long int resultIndex = ps.resolveRibbon();
    PRINT(resultIndex);
}
