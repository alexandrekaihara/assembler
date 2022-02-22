#ifndef LEXICAL_ANALYZER_HPP_INCLUDED
#define LEXICAL_ANALYZER_HPP_INCLUDED


#include <string>
#include <vector>
#include <unordered_map>
#include "error_dealer.hpp"


using namespace std;


class LexicalAnalyzer{
    private:
        int option;
        ErrorDealer* Err;
    public:
        LexicalAnalyzer(int option, ErrorDealer* Err);
        string to_lower(string line);
        string remove_comments(string line);
        string analyze(string line);
};


#endif