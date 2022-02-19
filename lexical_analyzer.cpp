#include "lexical_analyzer.hpp"
#include <unordered_map>
#include <string>
#include <iostream>
#include <locale>

using namespace std;



LexicalAnalyzer::LexicalAnalyzer(int option){
    this->option = option;
}


string LexicalAnalyzer::to_lower(string line){
    locale loc;
    for (string::size_type i=0; i<line.length(); ++i)
        line[i] = tolower(line[i],loc);
    return line;
}


// Remove comment part from string
string LexicalAnalyzer::remove_comments(string line){
    return line;
}


// Remove all comments, change line into lower case and interprets each token.
// Returns the line without all commments, to lower case chars and labels. 
string LexicalAnalyzer::analyze(string line){
    line = this->remove_comments(line);
    line = this->to_lower(line);
    return line
}