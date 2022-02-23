#ifndef SYNTATIC_ANALYZER_HPP_INCLUDED
#define SYNTATIC_ANALYZER_HPP_INCLUDED


#include <string>
#include "error_dealer.hpp"


using namespace std;


class SyntaticAnalyzer{
    private:
        int option;
        ErrorDealer* Err;
    public:
    SyntaticAnalyzer(int option, ErrorDealer* Err);
    string analyze(string line);
    bool is_label(string token);
};


#endif