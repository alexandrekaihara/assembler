#include "lexical_analyzer.hpp"
#include "etc.hpp"
#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
#include <locale>

using namespace std;



LexicalAnalyzer::LexicalAnalyzer(int option, ErrorDealer* Err){
    this->option = option;
    this->Err = Err;
}


// Get all chars and converts them into its lower case form
string LexicalAnalyzer::to_lower(string line){
    locale loc;
    for (string::size_type i=0; i<line.length(); ++i)
        line[i] = tolower(line[i],loc);
    return line;
}


// Remove comment part from string, tabs, line breaks and spaces
string LexicalAnalyzer::clean_line(string line){
    // Remove all whitespaces from the begginning
    int i = 0;
    for (i; i<line.length(); ++i) if (line[i] != ' ') break;
    
    // Remove all char on pattern
    string pattern = "\t\n", newline = "";
    for (i; i<line.length(); ++i){
        if(pattern.find(line[i]) != -1) continue;
        if(line[i] == ' ') 
        newline += line[i];
    }
    
    // Remove all comment part
    return line.substr(0, newline.find(';'));
}


// Separates the line into tokens of strings
vector<string> LexicalAnalyzer::split(string line){
    int lastindex = 0, length;
    vector<string> tokens;
    string pattern = " :,";
    for (string::size_type i=0; i<line.length(); ++i){
        // If the current lastindex is a pattern char, jump to the next char
        while(pattern.find(line[lastindex]) != -1) lastindex++;
        // If the current position on the string if one of the char in pattern, add substring
        if(pattern.find(line[i]) != -1){
            // If it has as definition of a label, include the char 
            if(line[i] == ':'){
                length = i - lastindex + 1;
            }
            // Do not include the pattern char
            else length = i - lastindex;
            tokens.push_back(line.substr(lastindex, length));
            lastindex = i + 1;
            i++;
        }
    }
    // Add the last token
    length = line.length() - lastindex;
    tokens.push_back(line.substr(lastindex, length));
    return tokens;
}


// Remove all comments, change line into lower case and interprets each token.
// Returns the line without all commments, to lower case chars and labels. 
string LexicalAnalyzer::analyze(string line){
    line = this->to_lower(line);
    return line;
}