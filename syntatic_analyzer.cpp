#include "syntatic_analyzer.hpp"


SyntaticAnalyzer::SyntaticAnalyzer(int option, ErrorDealer* Err){
    this->option = option;
    this->Err = Err;
}


string SyntaticAnalyzer::analyze(string line){}
