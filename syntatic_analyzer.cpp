#include "syntatic_analyzer.hpp"


SyntaticAnalyzer::SyntaticAnalyzer(int option, ErrorDealer* Err, unordered_map<string, Directive> DirectivesTable, unordered_map<string, Instruction> InstructionsTable){
    this->option = option;
    this->Err = Err;
    this->DirectivesTable = DirectivesTable;
    this->InstructionsTable = InstructionsTable;
}


void SyntaticAnalyzer::analyze(vector<string> tokens){
    for(int i=0; i<tokens.size(); i++){
        i++;
    }
}
