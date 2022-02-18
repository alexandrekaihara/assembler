#include "lexical_analyzer.hpp"
#include <unordered_map>
#include <string>
#include <iostream>
#include <locale>

using namespace std;



LexicalAnalyzer::LexicalAnalyzer(){
    
}


string LexicalAnalyzer::to_lower(string line){
    locale loc;
    for (string::size_type i=0; i<line.length(); ++i)
        line[i] = tolower(line[i],loc);
    return str;
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