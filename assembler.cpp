#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "etc.hpp"
#include "assembler.hpp"


using namespace std;


Assembler::Assembler(int op, char* filename){
    option = op;
    read_file(filename);
    load_directives(DIRECTIVEFILE);
    load_instructions(INSTRUCTIONFILE);
}


void Assembler::read_file(char* filename){
    ifstream infile(filename);
    stringstream buffer;
    buffer << infile.rdbuf();
    text = buffer.str();
    cout << "Assembler::read_file(char* filename): " << text;
}


void Assembler::run(){
    cout << "Assembler::run()";
}


void Assembler::load_directives(char* filename){
    cout << "Assembler::load_directives(char* filename)";
}


void Assembler::load_instructions(char* filename){
    cout << "Assembler::load_instructions(char* filename)";
}