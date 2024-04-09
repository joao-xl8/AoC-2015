//
//  day4.hpp
//  AoC-2015
//
//  Created by João Paulo Arnold Barros on 05/10/23.
//

#ifndef day4_hpp
#define day4_hpp

#include <stdio.h>
#include "md5.hpp"

//To do this, he needs to find MD5 hashes which, in hexadecimal, start with at least five zeroes. The input to the MD5 hash is some secret key (your puzzle input, given below) followed by a number in decimal. To mine AdventCoins, you must find Santa the lowest positive number (no leading zeroes: 1, 2, 3, ...) that produces such a hash.
//
//For example:
//
//If your secret key is abcdef, the answer is 609043, because the MD5 hash of abcdef609043 starts with five zeroes (000001dbbfa...), and it is the lowest such number to do so.
//If your secret key is pqrstuv, the lowest number it combines with to make an MD5 hash starting with five zeroes is 1048970; that is, the MD5 hash of pqrstuv1048970 looks like 000006136ef....

class PuzzleSolverDay4 {
public:
    PuzzleSolverDay4() {};
    ~PuzzleSolverDay4() {};
};

void executeDay4Puzzle();
#endif /* day4_hpp */
