#include "lexical_analyzer.hpp"
#include <unordered_map>
#include <string>
#include <iostream>


using namespace std;


LexicalAnalyzer::LexicalAnalyzer(){
    
}


string LexicalAnalyzer::to_lower(string line){
    return transform(line.begin(), line.end(), line.begin(), ::tolower);
}


// Remove comment part from string
string LexicalAnalyzer::remove_comments(string line){
    return line;
}


//
string LexicalAnalyzer::analyze_tokens_from_line(string line){
    line = this->remove_comments(line);

    return line;
}