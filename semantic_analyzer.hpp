#ifndef SEMANTIC_ANALYZER_HPP_INCLUDED
#define SEMANTIC_ANALYZER_HPP_INCLUDED


#include <string>


class SemanticAnalyzer{
    private:
        int option;
    public:
        SemanticAnalyzer(int option);
        string analyze(string line);
};


#endif