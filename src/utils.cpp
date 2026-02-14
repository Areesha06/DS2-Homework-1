#include "../include/utils.hpp"
#include <sstream>
#include <iomanip>


std::string removeTrailingZeros(long double number) {
    
    std::string s = std::to_string(number);  

    while (!s.empty() and s.back() == '0') {
        s.pop_back();
    }

    if (!s.empty() and s.back() == '.') {
        s.pop_back();
    }

    return s;
}

std::vector<std::string> str_split(std::string line) {
    std::vector<std::string> tokens;
    std::string token;

    for (char c : line) {             // go through every character
        if (c != ' ') {               // if it's not a space
            token += c;               // add it to the current word
        } else {                      // if it's a space
            if (token.empty() == false) {     // we finished a word
                tokens.push_back(token);
                token = "";           // reset for next word
            }
        }
    }

    if (token.empty() == false) {             // add the last word if any
        tokens.push_back(token);
    }

    return tokens;
}