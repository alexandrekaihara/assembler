#include "syntatic_analyzer.hpp"


SyntaticAnalyzer::SyntaticAnalyzer(int option, ErrorDealer* Err){
    this->option = option;
    this->Err = Err;
}


void SyntaticAnalyzer::analyze(vector<string> tokens, unordered_map<string, Directive> DirectivesTable){
    for(int i=0; i<tokens.size(); i++){
        i++;
    }
}
