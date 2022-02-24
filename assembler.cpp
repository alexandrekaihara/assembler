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
    this->Syn = new SyntacticAnalyzer(this->option, this->Err, this->DirectivesTable, this->InstructionsTable);
    this->Sem = new SemanticAnalyzer(this->option, this->Err, this->SymbolsTable);
    this->ObjGen = new ObjectGenerator(this->option, this->Err, &this->DirectivesTable, &this->InstructionsTable);

    this->text = this->read_file(inputfile);
    this->load_directives(DIRECTIVEFILE);
    this->load_instructions(INSTRUCTIONFILE);
}


// This function reads a file and returns a string
string Assembler::read_file(char* filename){
    ifstream infile(filename);
    stringstream buffer;
    buffer << infile.rdbuf();
    return buffer.str();
}


// This run the algorithm to assemble the file
void Assembler::run(){
    // For each line inside the file
    istringstream iss(this->text); 
    for(string line; getline(iss, line);){
        // Clean comments, double whitespaces, tabs, breaklines
        line = this->Lex->to_upper(line);
        line = this->Lex->clean_line(line);
        
        // Split line into tokens
        vector<string> tokens = this->Lex->split(line);
        
        // If there is a definition of label
        string label;
        if(this->Lex->is_label(tokens[0])){
            // Remove de double dots at the end of label
            label = tokens[0].substr(0, tokens[0].length()-1);
            this->Lex->is_valid_variable_name(label, this->line_counter);
            tokens.erase(tokens.begin());
            // If the line contains only the label, continue the process (it is equal to ignore breaks)
            if(tokens.size() == 0){
                this->line_counter++;
                continue;
            }
        }

        // REMOVER DEPOIS
        for(int i=0; i<tokens.size(); i++)
            cout << tokens[i] << "/"; 
        cout << '\n';

        // Verify if the tokens of the line respects the correct syntax of the language
        this->Syn->analyze(tokens, this->line_counter);

        this->line_counter++;
    }
    // Checks if all labels that were used in code, were defined
    this->Sem->check_if_all_labels_defined();
}


// Loads the directives especifications of this assembly language into the DirectivesTable
void Assembler::load_directives(const string filename){
    string aux = this->read_file((char*)filename.c_str());
    
    istringstream iss(aux); 
    for (string line; getline(iss, line);){
        // Split line into tokens separated by whitespace
        int lastindex = 0;
        vector<string> aux;
        for(int i=0; i<line.length(); i++){
            if(line[i] == ' '){
                int difference = i - lastindex;
                aux.push_back(line.substr(lastindex, difference));
                lastindex = i + 1;
            }
        }
        // Get last element
        int difference = line.length() - lastindex;
        aux.push_back(line.substr(lastindex, difference));
                
        string key = aux[0];
        int operands = stoi(aux[1]);
        int size = stoi(aux[2]);
        Directive dir = {operands, size};
        this->DirectivesTable[key] = dir; 
    }
}


// Loads the instructions especifications of this assembly language into the InstructionsTable
void Assembler::load_instructions(const string filename){
    string aux = this->read_file((char*)filename.c_str());
    
    istringstream iss(aux); 
    for (string line; getline(iss, line);){
        // Split line into tokens separated by whitespace
        int lastindex = 0;
        vector<string> aux;
        for(int i=0; i<line.length(); i++){
            if(line[i] == ' '){
                int difference = i - lastindex;
                aux.push_back(line.substr(lastindex, difference));
                lastindex = i + 1;
            }
        }
        // Get last element
        int difference = line.length() - lastindex;
        aux.push_back(line.substr(lastindex, difference));
        

        string key = aux[0];
        int operands = stoi(aux[1]);
        int opcode = stoi(aux[2]);
        int size = stoi(aux[3]);
        Instruction inst = {operands, opcode, size};
        this->InstructionsTable[key] = inst; 
    }
}