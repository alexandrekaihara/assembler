#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "assembler.hpp"


using namespace std;


Assembler::Assembler(int op, char* filename){
    option = op;
    read_file(filename);
    cout << text;
}


void Assembler::read_file(char* filename){
    ifstream infile(filename);
    if (infile.fail()) {
        cout << strerror(errno);
        exit(0)
    }
    stringstream buffer;
    buffer << infile.rdbuf();
    text = buffer.str();
}


void Assembler::run(){
    return;
}