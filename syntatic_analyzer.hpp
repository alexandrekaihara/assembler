#ifndef SYNTATIC_ANALYZER_HPP_INCLUDED
#define SYNTATIC_ANALYZER_HPP_INCLUDED


#include <string>
#include <vector>
#include <unordered_map>
#include "error_dealer.hpp"


using namespace std;


class SyntaticAnalyzer{
    private:
        int option;
        ErrorDealer* Err;
    public:
    SyntaticAnalyzer(int option, ErrorDealer* Err);
    void analyze(vector<string> tokens, vector<string, Directives> DirectivesTable);
};


#endif