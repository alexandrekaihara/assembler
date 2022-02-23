#include "syntatic_analyzer.hpp"


SyntaticAnalyzer::SyntaticAnalyzer(int option, ErrorDealer* Err){
    this->option = option;
    this->Err = Err;
}


void SyntaticAnalyzer::analyze(vector<string> tokens, vector<string, Directives> DirectivesTable){
    for(int i=0; i<tokens; i++){
        i++;
    }
}
