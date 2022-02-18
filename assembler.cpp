#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "etc.hpp"
#include "assembler.hpp"


using namespace std;


// Initilizes all variables, modules, read input file, load files
Assembler::Assembler(int op, char* inputfile, char* outputfile){
    this->option = op;
    this->outputfile = outputfile;
    
    this->Lex = new LexicalAnalyzer();
    this->Syn = new SyntaticAnalyzer();
    this->Sem = new SemanticAnalyzer();

    this->text = this->read_file(inputfile);
    this->load_directives(DIRECTIVEFILE);
    this->load_instructions(INSTRUCTIONFILE);
}


// This function reads a file and returns a string
string Assembler::read_file(char* filename){
    ifstream infile(filename);
    stringstream buffer;
    buffer << infile.rdbuf();
    text = buffer.str();
    cout << "Assembler::read_file(char* filename): " << text << "\n";
    return text
}


void Assembler::run(){
    cout << "Assembler::run()" << "\n";
    istringstream iss(this->text); 
    for (string line; getline(iss, line);){

    }
}


void Assembler::load_directives(const string filename){
    cout << "Assembler::load_directives(const string filename)" << "\n";
}


void Assembler::load_instructions(const string filename){
    cout << "Assembler::load_instructions(const string filename)" << "\n";
}