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
        vector<int> findlocation(string str, char character);
    public:
        LexicalAnalyzer(int option, ErrorDealer* Err);
        string to_lower(string line);
        string clean_line(string line);
        string analyze(string line);
        vector<string> split(string line);

};


#endif