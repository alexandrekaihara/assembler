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
    // Remove all comment part
    line = line.substr(0, line.find(';'));
    
    // Remove all whitespaces from the end
    int j = 0;
    for(j=line.length(); j==0; j++) if (line[j] != ' ') break;

    // Remove all whitespaces from the begginning
    int i = 0;
    for(i; i<line.length(); i++) if (line[i] != ' ') break;
    
    // Remove all char on pattern
    string pattern = "\t\n", newlinestr = "";
    for(i++; i<=j; i++){
        if(pattern.find(line[i]) != -1) continue;
        if (line[i] == ' ') && (line[i+1] == ' ') continue;
        newlinestr += line[i];
    }
    
    return newlinestr;
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


// Check if the variable name has more than 99 char or starts with number or has a char different from underscore, number and letters
bool LexicalAnalyzer::is_valid_variable_name(string token, int linenumber){
    int err = 0;
    if(token.length() > 99)
        err = LEX_ERR_99CHAR;
    if(isdigit(token[0]))
        err = LEX_ERR_99CHAR;
    char c;
    string pattern = "+-_";
    for (int i=0; i<token.length(); i++)
        if (!isalpha(token[i]) && !isdigit(token[i]) && pattern.find(token[i]) != 1)
            err = LEX_ERR_INVALIDCHAR;
    if(err != 0){
        if(this->option == OPTION_OBJ_NUM) this->Err->register_err(linenumber, err);
        return false;
    }
    return true;
}


bool LexicalAnalyzer::is_label(string token){
    if(token.find(':') != -1) return true;
    else return false;
}