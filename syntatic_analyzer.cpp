#include "syntatic_analyzer.hpp"


SyntaticAnalyzer::SyntaticAnalyzer(int option, ErrorDealer* Err, unordered_map<string, Directive> DirectivesTable, unordered_map<string, Instruction> InstructionsTable){
    this->option = option;
    this->Err = Err;
    this->DirectivesTable = DirectivesTable;
    this->InstructionsTable = InstructionsTable;
}


bool SyntaticAnalyzer::analyze(vector<string> tokens, int line_counter){
    int err = 0;
    // If there is the key, so get the diretive or instruction info
    if(this->DirectivesTable.count(tokens[0]) != 0)
        Directive data = this->DirectivesTable[tokens[0]];
    else if(this->InstructionsTable.count(tokens[0]) != 0)
        Instruction data = this->InstructionsTable[tokens[0]];
    else{
        err = SIN_ERR_INST_DIR_NOT_FOUND;
    } 

    // Check the number of operands
    if(tokens.size()-1 != data.operands)
        err = SIN_ERR_INVALID_NUM_OF_PARAM;

    // Register error if enabled option -o
    if ((err != 0) && (this->option == OPTION_OBJ_NUM))
        this->Err->register_err(line_counter, err);

    return data;
}


