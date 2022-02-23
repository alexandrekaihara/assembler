#include "syntatic_analyzer.hpp"


SyntaticAnalyzer::SyntaticAnalyzer(int option, ErrorDealer* Err, unordered_map<string, Directive> DirectivesTable, unordered_map<string, Instruction> InstructionsTable){
    this->option = option;
    this->Err = Err;
    this->DirectivesTable = DirectivesTable;
    this->InstructionsTable = InstructionsTable;
}


bool SyntaticAnalyzer::analyze(vector<string> tokens, int line_counter){
    int err = 0;

    if(this->is_directive(tokens[0]))
        // Check the number of operands
        cout << tokens[0] << " " << tokens.size() << " " << this->DirectivesTable.at(tokens[0]).operands << "\n";
        cout << "Compare to CONST " << tokens[0].compare("CONST") << " and is digit" << !isdigit(stoi(tokens[1])) << "\n";
        if(tokens.size()-1 != this->DirectivesTable.at(tokens[0]).operands)
            err = SIN_ERR_INVALID_NUM_OF_PARAM;
        else if(tokens[0].compare("CONST") == 0 && !isdigit(stoi(tokens[1])))
            err = SIN_ERR_INVALID_CONST_SYNTAX;
    else if(this->is_instruction(tokens[0]))
        // Check the number of operands
        if(tokens.size()-1 != this->InstructionsTable.at(tokens[0]).operands)
            err = SIN_ERR_INVALID_NUM_OF_PARAM;
        // Check if the COPY instruction has ", "
        else if((tokens[0].compare("COPY") == 0) && (tokens[1].find(", ") == -1))
            err = SIN_ERR_INVALID_COPY_SYNTAX;
    else err = SIN_ERR_INST_DIR_NOT_FOUND;
    
    // Register error if enabled option -o
    if (err != 0){
        if (this->option == OPTION_OBJ_NUM)
            this->Err->register_err(line_counter, err);
        return false;
    }
    return true;
}


bool SyntaticAnalyzer::is_directive(string token){
    if(this->DirectivesTable.count(token) != 0) 
        return true;
    return false;
}


bool SyntaticAnalyzer::is_instruction(string token){
    if(this->InstructionsTable.count(token) != 0) 
        return true;
    return false;
}
