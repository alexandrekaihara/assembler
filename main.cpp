/*
Brief:
Author: 
*/

#include <iostream>
#include <string.h>

using namespace std;

#define OPTION_PRE "-p"
#define OPTION_OBJ "-o"


void arguments(int argc, char const *argv[]){
    cout << OPTION_PRE << '\n';
    cout << OPTION_OBJ << '\n';
}


int main(int argc, char const *argv[])
{
    arguments(argc, argv);
    return 0;
}
