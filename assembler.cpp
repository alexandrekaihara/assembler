#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "etc.hpp"
#include "assembler.hpp"



using namespace std;


// Initilizes all variables, modules, read input file, load files
Assembler::Assembler(int op, char* inputfile, char* outputfile){
    this->option = op;
    this->outputfile = outputfile;
    
    this->Err = new ErrorDealer(this->option);
    this->Lex = new LexicalAnalyzer(this->option);
    this->Syn = new SyntaticAnalyzer(this->option);
    this->Sem = new SemanticAnalyzer(this->option);
    this->ObjGen = new ObjectGenerator(this->option);

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
    return text;
}


// This run the algorithm to assemble the file
void Assembler::run(){
    cout << "Assembler::run()" << "\n";
    // For each line inside the file
    istringstream iss(this->text); 
    for (string line; getline(iss, line);){
        line = this->Lex->analyze(line);
        line = this->Syn->analyze(line);
        line = this->Sem->analyze(line);
        if (this->ObjGen->analyze(line)){
            this->ObjGen->write(line);
        }
    }
}


// Loads the directives especifications of this assembly language into the DirectivesTable
void Assembler::load_directives(const string filename){
    cout << "Assembler::load_directives(const string filename)" << "\n";
}


// Loads the instructions especifications of this assembly language into the InstructionsTable
void Assembler::load_instructions(const string filename){
    cout << "Assembler::load_instructions(const string filename)" << "\n";
}