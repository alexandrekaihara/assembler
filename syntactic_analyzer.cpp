#include "syntactic_analyzer.hpp"


SyntacticAnalyzer::SyntacticAnalyzer(int option, ErrorDealer* Err, unordered_map<string, Directive>* DirectivesTable, unordered_map<string, Instruction>* InstructionsTable){
    this->option = option;
    this->Err = Err;
    this->DirectivesTable = DirectivesTable;
    this->InstructionsTable = InstructionsTable;
}


bool SyntacticAnalyzer::analyze(vector<string> tokens, int line_counter){
    int err = 0;

    if(this->is_directive(tokens[0])){
        // Check the number of operands
        if((tokens.size()-1) != this->DirectivesTable->at(tokens[0]).operands){
            err = SYN_ERR_INVALID_NUM_OF_PARAM;
            this->Err->register_err(line_counter, err);
        }
        else if(tokens[0].compare("CONST") == 0 && !this->is_number(tokens[1])){
            err = SYN_ERR_INVALID_CONST_SYNTAX;
            this->Err->register_err(line_counter, err);
        }
    }
    else if(this->is_instruction(tokens[0])){
        // Check the number of operands
        if(tokens.size()-1 != this->InstructionsTable->at(tokens[0]).operands){
            err = SYN_ERR_INVALID_NUM_OF_PARAM;
            this->Err->register_err(line_counter, err);
        }
        // Check if the COPY instruction has ", "
        else if((tokens[0].compare("COPY") == 0) && (tokens[1].find(", ") == -1)){
            err = SYN_ERR_INVALID_COPY_SYNTAX;
            this->Err->register_err(line_counter, err);
        }
    }
    else if(this->macroname.compare(tokens[0]) != 0){
        err = SYN_ERR_INST_DIR_NOT_FOUND;
        this->Err->register_err(line_counter, err);
    }
    
    // Register error if enabled option -o
    if (err != 0) return false;
    return true;
}


bool SyntacticAnalyzer::is_number(string number){
    // If the first char is a negative sign, it is correct
    int i = 0;
    if(number[0] == '-')
        i = 1;

    // Check if all subsequent char are number
    for(; i<number.length(); i++)
        if(!isdigit(number[i])) return false;
    return true;
}


bool SyntacticAnalyzer::is_directive(string token){
    if(this->DirectivesTable->count(token) != 0) 
        return true;
    return false;
}


bool SyntacticAnalyzer::is_instruction(string token){
    if(this->InstructionsTable->count(token) != 0) 
        return true;
    return false;
}
