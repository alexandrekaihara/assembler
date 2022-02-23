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
    this->Lex = new LexicalAnalyzer(this->option, this->Err);
    this->Syn = new SyntaticAnalyzer(this->option, this->Err);
    this->Sem = new SemanticAnalyzer(this->option, this->Err);
    this->ObjGen = new ObjectGenerator(this->option, this->Err);

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
    return text;
}


// This run the algorithm to assemble the file
void Assembler::run(){
    cout << "Assembler::run()" << "\n";
    // For each line inside the file
    istringstream iss(this->text); 
    for (string line; getline(iss, line);){
        // Clean comments, double whitespaces, tabs, breaklines
        line = this->Lex->to_lower(line);
        line = this->Lex->clean_line(line);
        
        // Split line into tokens
        vector<string> tokens = this->Lex->split(line);
        
        // Verify all tokens if they are valid 
        string token, label;
        for(int i=0; i<tokens.size(); i++)
            if(this->Lex->is_label(tokens[i]))
                this->Lex->is_valid_variable_name(tokens[i], line_counter);

        // REMOVER DEPOIS
        for(int i=0; i<tokens.size(); i++)
            cout << tokens[i] << "/"; 
        cout << '\n';



        this->line_counter++;
    }
}


// Loads the directives especifications of this assembly language into the DirectivesTable
void Assembler::load_directives(const string filename){
    string text = this->read_file((char*)filename.c_str());
    
    istringstream iss(this->text); 
    for (string line; getline(iss, line);){
        // Split line into tokens separated by whitespace
        int lastindex = 0;
        vector<string> aux;
        for(int i=0; i<line.length(); i++){
            if(line[i] == ' '){
                int difference = i - lastindex;
                aux.push_back(line.substr(lastindex, difference));
            }
        }

        string key = aux[0];
        int operands = stoi(aux[1], size_t);
        int size = stoi(aux[2], size_t);
        Directive dir = {operands, size};
        this->DirectivesTable[key] = dir; 
    }
    for (auto x : this->DirectivesTable)
        cout << x.first << " " << x.second.operands << " " << x.second.size << endl;
}


// Loads the instructions especifications of this assembly language into the InstructionsTable
void Assembler::load_instructions(const string filename){
    string text = this->read_file((char*)filename.c_str());
    
    istringstream iss(this->text); 
    for (string line; getline(iss, line);){
        // Split line into tokens separated by whitespace
        int lastindex = 0;
        vector<string> aux;
        for(int i=0; i<line.length(); i++){
            if(line[i] == ' '){
                int difference = i - lastindex;
                aux.push_back(line.substr(lastindex, difference));
            }
        }

        string key = aux[0];
        int operands = stoi(aux[1], size_t);
        int opcode = stoi(aux[2], size_t);
        int size = stoi(aux[3], size_t);
        Instruction inst = {operands, opcode, size};
        this->InstructionsTable[key] = inst; 
    }
    for (auto x : this->InstructionsTable)
        cout << x.first << " " << x.second.opcode << " " << x.second.operands << " " << x.second.size << endl;
}