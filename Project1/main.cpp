//
//  main.cpp
//  Project1
//
//  Created by William Lin on 2/24/17.
//  Copyright © 2017 William Lin. All rights reserved.
//

#include "Parser.hpp"

vector<vector<string>> allString;


vector<string> parse(string);
string stringToLower(string);

int main(int argc, const char * argv[]) {
    Parser parser("text.txt", "instr.txt");
    parser.encode("output.txt");
}
