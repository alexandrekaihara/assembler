#ifndef LEXICAL_ANALYZER_HPP_INCLUDED
#define LEXICAL_ANALYZER_HPP_INCLUDED


#include <unordered_map>
#include <string>
#include <vector>


using namespace std;


class LexicalAnalyzer{
    private:
        int option;
    public:
        string to_lower(string line);
        string remove_comments(string line);
        string analyze(string line);
        LexicalAnalyzer();
};


#endif