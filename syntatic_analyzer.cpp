#include "syntatic_analyzer.hpp"


SyntaticAnalyzer::SyntaticAnalyzer(int option, ErrorDealer* Err){
    this->option = option;
    this->Err = Err;
}


string SyntaticAnalyzer::analyze(string token){

}


bool SyntaticAnalyzer::is_label(string token){
    if(token.find(':') != -1) return true;
    else return false;
}