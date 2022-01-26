/*
Brief:
Author: 
*/

#include <iostream>


using namespace std;


void arguments(int argc, char const *argv[]){
    for (int i=0; i<argc; i++) cout << argv[i] << '\n';    
}


int main(int argc, char const *argv[])
{
    arguments(argc, argv);
    return 0;
}
