//
//  day4.cpp
//  AoC-2015
//
//  Created by João Paulo Arnold Barros on 05/10/23.
//

#include "day4.hpp"

void executeDay4Puzzle() {
    unsigned long int n = 0;
    std::string hash;
    do{
        n++;
        auto key = std::string("iwrupvqb" + std::to_string(n));
        // need to pass the key on every iter but md5 dont accept
        hash = md5(key);
        std::cout << hash.substr(0,6) << ": " << key << std::endl;
    } while (hash.substr(0,6) != "000000");
    std::cout << "iter n: " << n << std::endl;
}
