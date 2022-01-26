/*
Brief:
Author: 
*/

#include <iostream>
#include <string.h>


using namespace std;


#define OPTION_PRE "-p"
#define OPTION_OBJ "-o"


int main(int argc, char const *argv[])
{
    if(strcmp(argv[1], OPTION_PRE)==0){
        cout << "option -p chosen\n"
    }
    else if(strcmp(argv[1], OPTION_OBJ)==0){
        cout << "option -o chosen\n"
    }
    else{
        cout << "UnB - Software Básico - Assembler\n\nCommands:\n.\
        /montador -p [programname].asm\n./montador -p [programname]\
        .asm\n\nInvalid option. Use one of the optionss above.\n"
    }
    return 0;
}
