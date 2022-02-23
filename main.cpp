/*
Brief:
Author: 
g++ main.cpp assembler.cpp lexical_analyzer.cpp semantic_analyzer.cpp syntactic_analyzer.cpp error_dealer.cpp object_generator.cpp
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

    char* inputfile = (char*)argv[2];
    char* outputfile = (char*)argv[3];
    Assembler* assembler = new Assembler(option, inputfile, outputfile);
    assembler->run();

    return 0;
}
