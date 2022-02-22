#ifndef SEMANTIC_ANALYZER_HPP_INCLUDED
#define SEMANTIC_ANALYZER_HPP_INCLUDED


#include <string>
#include "error_dealer.hpp"


using namespace std;


class SemanticAnalyzer{
    private:
        int option;
        ErrorDealer* Err;
    public:
        SemanticAnalyzer(int option, ErrorDealer* Err);
        string analyze(string line);
};


#endif