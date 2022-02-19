#ifndef SYNTATIC_ANALYZER_HPP_INCLUDED
#define SYNTATIC_ANALYZER_HPP_INCLUDED


#include <string>


using namespace std;


class SyntaticAnalyzer{
    private:
        int option;
        
    public:
    SyntaticAnalyzer(int option);
    string analyze(string line);
};


#endif