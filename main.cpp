/*
Brief:
Author: 
g++ main.cpp assembler.cpp lexical_analyzer.cpp semantic_analyzer.cpp syntatic_analyzer.cpp
*/

#include <iostream>
#include <string.h>
#include <string>
#include "assembler.hpp"
#include "etc.hpp"

using namespace std;


int main(int argc, char const *argv[])
{
    int option=0;
    char* filename;

    // If the program receives any different number of parameters than 4, ends program
    if(argc != 4){
        cout << INSTRUCTIONS;
        exit(0);
    }

    // Set interpret the chosen option
    if(strcmp(argv[1], OPTION_PRE)==0)      option = OPTION_PRE_NUM;
    else if(strcmp(argv[1], OPTION_OBJ)==0) option = OPTION_OBJ_NUM;
    else if(strcmp(argv[1], OPTION_MAC)==0) option = OPTION_MAC_NUM;
    else{
        cout << INSTRUCTIONS;
        cout << "\nInvalid option. Use one of the options above.\n";
        exit(0);
    }

    filename = (char*)argv[2];
    Assembler* assembler = new Assembler(option, filename);
    //assembler->run();

    return 0;
}
