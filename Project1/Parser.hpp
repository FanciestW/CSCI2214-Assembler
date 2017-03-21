//
//  Parser.hpp
//  Project1
//
//  Created by William Lin on 3/15/17.
//  Copyright © 2017 William Lin. All rights reserved.
//

#ifndef Parser_hpp
#define Parser_hpp

#include "Instructions.hpp"

class Parser{
private:
    vector<vector<string>> parsedStr;
    vector<string> labels;
    vector<unsigned long int> lblIndex;
    Instructions instr;
    
public:
    ~Parser() = default;
    Parser(string, string);
    void encode(string);
    vector<unsigned long int> encodeLine(vector<string>);
    void toHex(vector<unsigned long int>);
    unsigned int lineEncode(vector<string>, int);
    int getInstrType(string);
};

#endif /* Parser_hpp */
