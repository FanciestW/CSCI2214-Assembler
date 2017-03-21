//
//  Instructions.hpp
//  Project1
//
//  Created by William Lin on 3/5/17.
//  Copyright © 2017 William Lin. All rights reserved.
//

#ifndef Instructions_hpp
#define Instructions_hpp

#include "tools.hpp"

class Instructions{

private:
    vector<string> instrName;
    vector<int> opcode;
    vector<string> parseInstr(string);
    vector<string> rTypes;
    
public:
    Instructions(string);
    ~Instructions() = default;
    int getOpCode(string);
    bool isRType(string);
};

#endif /* Instructions_hpp */
