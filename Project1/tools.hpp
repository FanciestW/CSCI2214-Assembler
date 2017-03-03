//                    -*- mode:c++; tab-width:4 -*-
// modified September 2016
// file: tools.hpp ----------------------------------------------------------- 
// header file for the tools library.                                          
// --------------------------------------------------------------------------- 
// Local definitions and portability code.                                     
// Please enter your own system, name, class, and printer stream name.         
// --------------------------------------------------------------------------- 
#pragma once
#define NAME    "William Lin"
#define CLASS   "CSCI 4526"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <limits>

#include <cstdio>      // for NULL      
#include <cstdlib>     // for malloc() and calloc()     
#include <cstring>
#include <cerrno>
#include <cmath>      
#include <ctime>        
#include <cctype>      // for isspace() and isdigit()  
#include <cstdarg>     // for functions with variable # of arguments 

using namespace std;

// --------------------------------------------------------------------------- 
// Macros for debugging.                                                       
// --------------------------------------------------------------------------- 
#define DUMPp(p) "\n" <<"    " #p " @ " <<&p <<"    value = " <<p <<"    " #p " --> " <<*p 
#define DUMPv(k) "\n" <<"    " #k " @ " <<&k <<"    value = " <<k 

// --------------------------------------------------------------------------- 
// I/O Extension. ------------------------------------------------------------ 
// --------------------------------------------------------------------------- 
istream& flush( istream& is );         // Use: cin >> x >> flush;

// --------------------------------------------------------------------------- 
// Routine screen and process management.------------------------------------- 
// --------------------------------------------------------------------------- 
void     fbanner( ostream& fout );
void     banner();
void     bye( void );                                    
void     hold( void );                                    
void     say( const char* format, ... );

// --------------------------------------------------------------------------- 
// Error handling. ----------------------------------------------------------- 
// --------------------------------------------------------------------------- 
void    fatal( const char* format, ... );

// --------------------------------------------------------------------------- 
// time and date. -------------------------------------------------------------
// --------------------------------------------------------------------------- 
void   when( char* date, char* hour );
char*  today( char* date );
char*  oclock( char* hour );

// --------------------------------------------------------------------------- 
// Menu handling.                           
// --------------------------------------------------------------------------- 
int    menu( char* title, int n, const char* menu[] );
char   menu_c( const char* title, int n, const char* menu[], const string valid );
