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
string LexicalAnalyzer::to_upper(string line){
    locale loc;
    for (string::size_type i=0; i<line.length(); ++i)
        line[i] = toupper(line[i],loc);
    return line;
}


// Remove comment part from string, tabs, line breaks and spaces
string LexicalAnalyzer::clean_line(string line){
    int i = 0;
    int j = 0;

    // Remove all comment part
    line = line.substr(0, line.find(';'));
    
    // Remove all whitespaces from the end
    for(j=line.length()-1; j >= 0; j--) if (line[j] != ' ') break;

    // Remove all whitespaces from the begginning
    for(i; i<line.length(); i++) if (line[i] != ' ') break;
    
    // Remove all char on pattern
    string pattern = "\t\n", newlinestr;
    bool first_space = false;
    for(; i<=j; i++){
        // Ignore if finds a tab or newline
        if(pattern.find(line[i]) != -1) continue;
        // Consider the first whitespace, and ignores all others
        else if(line[i] == ' '){
            if(first_space == false)
                first_space = true;
            else{
                continue;
            }
        } 
        else first_space = false;
        newlinestr += line[i];
    }
    return newlinestr;
}


// Separates the line into tokens of strings
vector<string> LexicalAnalyzer::split(string line){
    int lastindex = 0, length;
    vector<string> tokens;
    string pattern = " :,";
    line += " ";
    for (string::size_type i=0; i<line.length(); ++i){
        // If the current lastindex is a pattern char, jump to the next char
        while((lastindex == line.length()-1) || (pattern.find(line[lastindex]) != -1)) lastindex++;
        // If the current position on the string if one of the char in pattern, add substring
        if(pattern.find(line[i]) != -1){
            // If it has as definition of a label, include the char 
            if(line[i] == ':')
                length = i - lastindex + 1;
            // In case of having a ', ', save the char and check if there is another whitespace after
            else if (line[i] == ',')
                if(line[i+1] == ' ')
                    length = i - lastindex + 2;
                else length = i - lastindex + 1;
            // Do not include the pattern char
            else length = i - lastindex;
            tokens.push_back(line.substr(lastindex, length));
            lastindex = i + 1;
            i++;
        }
    }
    return tokens;
}


// Check if the variable name has more than 99 char or starts with number or has a char different from underscore, number and letters
bool LexicalAnalyzer::is_valid_variable_name(string token, int linenumber){
    int err = 0;
    if(token.length() > 99){
        err = LEX_ERR_99CHAR;
        this->Err->register_err(linenumber, err);
    }
    if(isdigit(token[0])){
        err = LEX_ERR_STARTNUM;
        this->Err->register_err(linenumber, err);
    }
    for (int i=0; i<token.length(); i++)
        if (!isalpha(token[i]) && !isdigit(token[i]) && token[i] != '_'){
            err = LEX_ERR_INVALIDCHAR;
            this->Err->register_err(linenumber, err);
        }
    if(err != 0) return false;
    return true;
}


bool LexicalAnalyzer::is_label(string token){
    if(token.find(':') != -1) return true;
    else return false;
}


bool LexicalAnalyzer::is_empty_line(string line){
    line = this->clean_line(line);
    if(line.empty())
        return true;
    return false;
}