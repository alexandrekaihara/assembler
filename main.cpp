/*
Brief:
Author: 
*/

#include <iostream>
#include <string.h>
#include <string>
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
#define OPTION_MAC "-m"
#define OPTION_MAC_NUM 2
#define INSTRUCTIONS "Assembler - Software Básico\nAlexandre Kaihara - 18/0029690\n\nCommands:\n./montador -o [program_name].asm [output_name].obj\n./montador -p [program_name].asm [output_name].obj\n./montador -m [program_name].asm [output_name].obj\n";


int main(int argc, char const *argv[])
{
    int option=0;
    char* filename;

    // Interprets the program input
    if(argc != 4){
        cout << INSTRUCTIONS;
        exit(0);
    }
    if(strcmp(argv[1], OPTION_PRE)==0 && argc == 4){
        cout << "option -p chosen\n";
        option = OPTION_PRE_NUM;
        filename = (char*)argv[2];
    }
    else if(strcmp(argv[1], OPTION_OBJ)==0 && argc == 4){
        cout << "option -o chosen\n";
        option = OPTION_OBJ_NUM;
        filename = (char*)argv[2];
    }
    else if(strcmp(argv[1], OPTION_MAC)==0 && argc == 4){
        cout << "option -o chosen\n";
        option = OPTION_MAC_NUM;
        filename = (char*)argv[2];
    }
    else{
        cout << INSTRUCTIONS;
        cout << "\nInvalid option. Use one of the options above.\n";
        exit(0);
    }

    Assembler* assembler = new Assembler(option, filename);
    //assembler->run();

    return 0;
}
