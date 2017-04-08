
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
    if(!in.is_open()) fatal("Input File Error");
    vector<string> line;
    string temp = "";
    for(;;){
        char c;
        in >> noskipws >> c;
        c = tolower(c);
        if(in.eof()) break;
        if(isalpha(c) || isnumber(c) || c == '#' || c == '(' || c == ')' || c == '-') temp+=c;
        else if(c == '\n'){
            line.push_back(temp);
            allLines.push_back(line);
            line.clear();
            temp.clear();
        }
        else if(c == ':'){
            labels.push_back(temp);
            lblIndex.push_back(allLines.size());
            temp.clear();
        }
        else if(c == ' ' || c == ','){
            line.push_back(temp);
            temp.clear();
        }
    }
}

void Parser::encode(string filename){
    ofstream out(filename);
    for(int i = 0; i < allLines.size(); i++){
        vector<string> line = allLines.at(i);
        unsigned int test = lineEncode(line, i);
        out << setfill('0') << setw(8) << hex << test << " ";
        cout << setfill('0') << setw(8) << hex << test << " ";
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
    signed int offsetMasker = 0x3FFFFFF;
    if(line.size() == 2){ //handles jump instructions
        maskedOpCode = instrOpCode << (cursor - 6);
        toReturn |= maskedOpCode;
        cursor -= 6;
        if(instrOpCode == 2 || instrOpCode == 3){ //J label / JAL label
            signed int lbl = (getLblIndex(line.at(1)) * 4) - (lineNum * 4 + 4);
            lbl &= offsetMasker;
            toReturn |= lbl;
        } else { //JR R1 / JALR R1
            int rs1 = stoi(line[1].substr(1));
            unsigned int maskR1 = rs1 << (cursor - 5);
            toReturn |= maskR1;
            cursor -= 21;
        }
        
    } else if(line.size() == 3){ //handles load, store and branch instructions
        
        maskedOpCode = instrOpCode << (cursor - 6);
        toReturn |= maskedOpCode;
        cursor -= 6;
        if(line.at(2).find('(') != string::npos){
            //Ex: lh r3,4(R4)
            string immStr = line.at(2);
            signed int imm = stoi(immStr.substr(0, immStr.find('(')));
            int rs1 = stoi(immStr.substr(immStr.find('r')+1, immStr.size()-1));
            int rs2 = stoi(line.at(1).substr(1));
            unsigned int maskR1 = rs1 << (cursor -5);
            toReturn |= maskR1;
            cursor -= 5;
            unsigned int maskR2 = rs2 << (cursor - 5);
            toReturn |= maskR2;
            cursor -= 5;
            signed int maskImm = imm << (cursor - 16);
            maskImm &= 0x00FFFF;
            toReturn |= maskImm;
        } else if(line.at(1).find('(') != string::npos){
            //Ex: sb 4(r4),r3
            string immStr = line.at(1);
            signed int imm = stoi(immStr.substr(0, immStr.find('(')));
            int rs1 = stoi(immStr.substr(immStr.find('r')+1, immStr.size()-1));
            int rs2 = stoi(line.at(2).substr(1));
            unsigned int maskR1 = rs1 << (cursor -5);
            toReturn |= maskR1;
            cursor -= 5;
            unsigned int maskR2 = rs2 << (cursor - 5);
            toReturn |= maskR2;
            cursor -= 5;
            signed int maskImm = imm << (cursor - 16);
            maskImm &= 0x00FFFF;
            toReturn |= maskImm;
        } else {
            //Ex: beqz r1,label
            int rs1 = stoi(line[1].substr(1));
            if(rs1 > 31) fatal("Register too large");
            unsigned int maskR = rs1 << (cursor - 5);
            toReturn |= maskR;
            cursor -= 5;
            signed int lblOffset = (getLblIndex(line.at(2)) * 4) - (lineNum * 4 + 4);
            cursor -= 5; //Skip rs2
            lblOffset &= offsetMasker;
            toReturn |= lblOffset;
        }
        
    } else if(rTypeFlag == true){ //handles r type instructions
        
        cursor -= 6;
        for(int i = 2; i < line.size(); i++){
            string temp = line[i];
            if(temp.at(0) == 'r'){
                int reg = stoi(temp.substr(1));
                if(reg > 31) fatal("Register too large");
                unsigned int maskR = reg << (cursor - 5);
                toReturn |= maskR;
                cursor -= 5;
            } else if (temp.at(0) == '#'){
                fatal("Wrong Instruction Type");
            } else fatal("Instruction Error");
        }
        string temp = line[1];
        if(temp.at(0) == 'r'){
            int reg = stoi(temp.substr(1));
            if(reg > 31) fatal("Register too large");
            unsigned int maskR = reg << (cursor - 5);
            toReturn |= maskR;
            cursor -= 5;
        } else fatal("Instruction error with RType");
        if(cursor == 11) toReturn |= instrOpCode;
        else fatal("Something went wrong");
        
    } else if(rTypeFlag == false){ //handles i type instructions
        
        maskedOpCode = instrOpCode << (cursor - 6);
        toReturn |= maskedOpCode;
        cursor -= 6;
        for(int i = 2; i < line.size(); i++){
            string temp = line[i];
            if(temp.at(0) == 'r'){
                cursor = 26;
                int reg = stoi(temp.substr(1));
                unsigned int maskR = reg << (cursor - 5);
                toReturn |= maskR;
            } else if (temp.at(0) == '#' && i == line.size() - 1){
                cursor = 16;
                int imm = stoi(temp.substr(1));
                unsigned int maskI = imm << (cursor - 16);
                maskI &= 0x00FFFF;
                toReturn |= maskI;
            } else if (isdigit(temp.at(temp.size()-1)) && line.size() - 1){
                cursor = 16;
                int imm = stoi(temp);
                unsigned int maskI = imm << (cursor - 16);
                maskI &= 0x00FFFF;
                toReturn |= maskI;
            }
            else fatal("Instruction Error");
        }
        if(line[1].at(0) == 'r'){
            cursor = 21;
            int reg = stoi(line[1].substr(1));
            unsigned int maskR = reg << (cursor - 5);
            toReturn |= maskR;
        } else fatal("Instruction error with IType");
        
        
    }
    
    return toReturn;
}

int Parser::getLblIndex(string lblName){
    vector<string>::iterator iter = find(labels.begin(), labels.end(), lblName);
    if(iter == labels.end()){
        fatal("Label not found");
        return -1;
    } else {
        int index = lblIndex[iter - labels.begin()];
        return index;
    }
}
