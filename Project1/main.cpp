//
//  main.cpp
//  Project1
//
//  Created by William Lin on 2/24/17.
//  Copyright © 2017 William Lin. All rights reserved.
//

#include "Parser.hpp"

vector<string> allString;


vector<string> parse(string);
string stringToLower(string);

int main(int argc, const char * argv[]) {
    ifstream in("text.txt");
    for(;;){
        string line;
        getline(in, line);
        if(in.eof()) break;
        vector<string> parsedStr = parse(stringToLower(line));
        for(int i = 0; i < parsedStr.size(); i++){
            cout << parsedStr.at(i) << " ";
        } cout << endl;
        
    }
}

vector<string> parse(string line){
    vector<string> parsedStr;
    char str[line.length()-1];
    for(int i = 0; i < line.length()-1; i++){
        str[i] = line[i];
    }
    char * pch;
    pch = strtok (str," ,\n");
    while (pch != NULL)
    {
        parsedStr.push_back(pch);
        pch = strtok (NULL, " ,\n");
    }
    return parsedStr;
}

string stringToLower(string str){
    for(int i = 0; i < str.length(); i++){
        str[i] = tolower(str[i]);
    }
    return str;
}
