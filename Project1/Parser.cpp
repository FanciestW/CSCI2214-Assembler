//
//  Parser.cpp
//  Project1
//
//  Created by William Lin on 3/15/17.
//  Copyright © 2017 William Lin. All rights reserved.
//

#include "Parser.hpp"

Parser::Parser(string inputFile, string instrFile) : instr(instrFile){
    ifstream in(inputFile);
    vector<string> line;
    string temp = "";
    for(;;){
        char c;
        in >> noskipws >> c;
        if(in.eof()) break;
        if(isalpha(c) || isnumber(c) || c == '#') temp+=c;
        else if(c == '\n'){
            parsedStr.push_back(line);
            line.clear();
        }
        else if(c == ':'){
            labels.push_back(temp);
            lblIndex.push_back(parsedStr.size());
            temp.clear();
        }
        else{
            line.push_back(temp);
            temp.clear();
        }
    }
}

void Parser::encode(string filename){
    ofstream out(filename);
    for(int i = 0; i < parsedStr.size(); i++){
        vector<string> line = parsedStr.at(i);
        unsigned int test = lineEncode(line, i);
        out << "0x" << setfill('0') << setw(8) << hex << test << " ";
        cout << "0x" << setfill('0') << setw(8) << hex << test << " ";
        out << '\n';
        cout << '\n';
    }
}

unsigned int Parser::lineEncode(vector<string> line, int lineNum){
    bool rTypeFlag = instr.isRType(line[0]);
    int cursor = 32;
    unsigned int toReturn = 0;
    unsigned int instrOpCode = instr.getOpCode(line[0]);
    unsigned int maskedOpCode = 0;
    if(line.size() == 2){
        maskedOpCode = instrOpCode << (cursor - 6);
        toReturn |= maskedOpCode;
        vector<string>::iterator iter = find(labels.begin(), labels.end(), line[1]);
        signed int lbl = lblIndex[iter - labels.begin()] - (lineNum * 4);
        signed int masker = 67108863;
        lbl *= 4;
        lbl &= masker;
        toReturn |= lbl;
    } else if(rTypeFlag == true){
        cursor -= 6;
        for(int i = 1; i < line.size(); i++){
            string temp = line[i];
            if(temp.at(0) == 'r'){
                int reg = stoi(temp.substr(1));
                if(reg > 32) fatal("Register too large");
                unsigned int maskR = reg << (cursor - 5);
                toReturn |= maskR;
                cursor -= 5;
            } else if (temp.at(0) == '#'){
                fatal("Wrong Instruction Type");
            } else if (temp.at(0) == '('){
                //TODO::Handle ()
            } else {
                
            }
        }
        if(cursor == 11) toReturn |= instrOpCode;
        else fatal("Something went wrong");
    } else {
        maskedOpCode = instrOpCode << (cursor - 6);
        toReturn |= maskedOpCode;
        cursor -= 6;
        for(int i = 1; i < line.size(); i++){
            string temp = line[i];
            if(temp.at(0) == 'r'){
                int reg = stoi(temp.substr(1));
                unsigned int maskR = reg << (cursor - 5);
                toReturn |= maskR;
                cursor -= 5;
            } else if (temp.at(0) == '#'){
                int imm = stoi(temp.substr(1));
                unsigned int maskI = imm << (cursor - 16);
                toReturn |= maskI;
                cursor -= 16;
            } else if (temp.at(0) == '('){
                //TODO::Handle ()
            } else {
                
            }
        }
    }
    return toReturn;
}

int Parser::getInstrType(string instr){
    return -1;
}
