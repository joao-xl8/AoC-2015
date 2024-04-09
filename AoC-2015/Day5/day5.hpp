#ifndef day5_hpp
#define day5_hpp

#include <stdio.h>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <iostream>

//Santa needs help figuring out which strings in his text file are naughty or nice.
//
//A nice string is one with all of the following properties:
//
//It contains at least three vowels (aeiou only), like aei, xazegov, or aeiouaeiouaeiou.
//It contains at least one letter that appears twice in a row, like xx, abcdde (dd), or aabbccdd (aa, bb, cc, or dd).
//It does not contain the strings ab, cd, pq, or xy, even if they are part of one of the other requirements.

// Part two
//It contains a pair of any two letters that appears at least twice in the string without overlapping, like xyxy (xy) or aabcdefgaa (aa), but not like aaa (aa, but it overlaps).
//It contains at least one letter which repeats with exactly one letter between them, like xyx, abcdefeghi (efe), or even aaa.


static std::map<char, char> vowels {
    { *"a", *"a"},
    { *"e", *"e"},
    { *"i", *"i"},
    { *"o", *"o"},
    { *"u", *"u"},
};
static std::map<std::string, std::string> disallowed {
    { "ab", "ab"},
    { "cd", "cd"},
    { "pq", "pq"},
    { "xy", "xy"},
};
class PuzzleSolverDay5 {
public:
    PuzzleSolverDay5() {
        std::fstream instructions_file;
        strings.clear();
        instructions_file.open("Day5/instructions.txt", std::ios::in);
        
        if(instructions_file.is_open()){
            std::string line;
            while (std::getline(instructions_file, line )) {
                strings.push_back(line);
            }
        }
        instructions_file.close();
    };
    ~PuzzleSolverDay5() {};
    
    int resolveNiceStrings() {
        int n_nice_strings = 0;
        for(std::string name : strings) {
            bool double_letter = false;
            bool disallowed_string = false;
            int n_vowels = 0;
            std::string prev_char;
            int offset = 0;
            for(auto ch : name){
                n_vowels += checkIsVowel(ch);
                if(offset > 0) {
                    std::string sil = prev_char + ch;
                    if(disallowed.contains(sil)){
                        disallowed_string = true;
                    }
                    if (prev_char[0] == ch) {
                        double_letter = true;
                    }
                }
                offset++;
                prev_char = ch;
            }
            
            //validate requiremnts
            if(n_vowels >= 3 && double_letter && !disallowed_string){
                n_nice_strings++;
            }
        }
        return n_nice_strings;
    };
    
    int resolveNewNiceStrings() {
        int n_nice_strings = 0;
        
        for(int i=0;i < strings.size(); i++) {
            std::string name = std::move(strings[i]);
            //conditions to be a nice name
            bool pair_char = false;
            bool between_two_exact = false;
            // map = ("letterA","letterB") : position_of_letterB
            std::map<std::pair<char,char>, int> name_pairs{};
            
            for(int j = 1; j < name.length(); j++){
                // It contains a pair of any two letters that appears at least twice in the string without overlapping, like xyxy (xy) or aabcdefgaa (aa), but not like aaa (aa, but it overlaps).
                std::pair<char, char> current_pair (name[j-1], name[j]);
                
                if (name_pairs.contains(current_pair)) {
                    // contains
                    if (name_pairs[current_pair] < j - 1) {
                        // dont overlap
                        pair_char = true;
                    }
                } else {
                    // add new pair (current_pair) with value of the last char pos
                    name_pairs[current_pair] = j;
                }
                
                if (j > 1) {
                    //It contains at least one letter which repeats with exactly one letter between them, like xyx, abcdefeghi (efe), or even aaa.
                    if(name[j] == name[j-2]) {
                        between_two_exact = true;
                    }
                }
            }
            
            //validate requiremnts
            if(pair_char == true && between_two_exact == true){
                std::cout << "NICE: " << name << std::endl;
                n_nice_strings++;
            }
            name_pairs.clear();
        }
        return n_nice_strings;
    };
    
private:
    std::vector<std::string> strings;
    
    int checkIsVowel(auto& ch) {
        if (vowels.contains(ch)){
            return 1;
        }
        return 0;
    }
    
    int checkIsDisallowed(auto& sil) {
        if(disallowed.contains(sil)){
            return 1;
        }
        return 0;
    }
    
    bool checkDoublePair(auto& sil) {
        if(disallowed.contains(sil)){
            return 1;
        }
        return 0;
    }
};

void executeDay5Puzzle();
#endif /* day5_hpp */
