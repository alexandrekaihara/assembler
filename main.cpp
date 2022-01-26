/*
Brief:
Author: 
*/

#include <iostream>
#include <string.h>
#include "assembler.hpp"
//#include "lexical_analyzer.hpp"
//#include "syntatic_analyzer.hpp"
//#include "semantic_analyzer.hpp"


using namespace std;


// Defines
#define OPTION_PRE "-p"
#define OPTION_PRE_NUM 0
#define OPTION_OBJ "-o"
#define OPTION_OBJ_NUM 1
#define INSTRUCTIONS "Assembler - Software Básico\nAlexandre Kaihara - 18/0029690\n\nCommands:\n./montador -p [program_name].asm\n./montador -p [programname].asm\n";




int main(int argc, char const *argv[])
{
    int option=0;
    char* filename;

    // Interprets the program input
    if(argc<2){
        cout << INSTRUCTIONS;
        exit(0);
    }
    if(strcmp(argv[1], OPTION_PRE)==0){
        cout << "option -p chosen\n";
        option = OPTION_PRE_NUM;
        filename = 
    }
    else if(strcmp(argv[1], OPTION_OBJ)==0){
        cout << "option -o chosen\n";
        option = OPTION_OBJ_NUM;
    }
    else{
        cout << INSTRUCTIONS;
        cout << "\nInvalid option. Use one of the options above.\n";
    }

    Assembler* assembler = new Assembler(option, filename);
    //assembler->run();

    return 0;
}
