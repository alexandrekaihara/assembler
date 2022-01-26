#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "assembler.hpp"


using namespace std;


Assembler::Assembler(int op, char* filename){
    option = op;
    text = read_file(filename);
    cout << text;
}


string Assembler::read_file(char* filename){
    ifstream infile(filename);
    stringstream buffer;
    buffer << infile.rdbuf();
    text = buffer.str();
}


void Assembler::run(){
    return;
}