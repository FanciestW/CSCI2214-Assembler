//
//  Instructions.cpp
//  Project1
//
//  Created by William Lin on 3/5/17.
//  Copyright © 2017 William Lin. All rights reserved.
//

#include "Instructions.hpp"

Instructions::Instructions(string filename){
    ifstream in(filename);
    for(;;){
        string line;
        getline(in, line);
        if(in.eof()) break;
        vector<string> instrParse = parseInstr(line);
        instrName.push_back(instrParse.at(0));
        opcode.push_back(stoi(instrParse.at(1)));
    }
}

vector<string> Instructions::parseInstr(string line){
    vector<string> parsedStr;
    int begin = 0;
    unsigned long int br = line.find_first_of(" ");
    if(line.find_first_of(':') != string::npos){
        begin = 2;
        rTypes.push_back(line.substr(begin, br - begin));
    }
    parsedStr.push_back(line.substr(begin, br - begin));
    parsedStr.push_back(line.substr(br + 1, line.size()));
    return parsedStr;
}

int Instructions::getOpCode(string name){
    vector<string>::iterator iter = find(instrName.begin(), instrName.end(), name);
    if(iter == instrName.end()) fatal("Instruction unknown");
    return opcode.at(iter - instrName.begin());
}

bool Instructions::isRType(string opcode){
    if(find(rTypes.begin(), rTypes.end(), opcode) != rTypes.end()){
        return true;
    } else {
        return false;
    }
}
