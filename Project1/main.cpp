//
//  main.cpp
//  Project1
//
//  Created by William Lin on 2/24/17.
//  Copyright © 2017 William Lin. All rights reserved.
//

#include "Parser.hpp"

int main(int argc, const char * argv[]) {
    Parser parser("test.txt", "instr.txt");
    parser.encode("output.txt");
}
