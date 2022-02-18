#ifndef LEXICAL_ANALYZER_HPP_INCLUDED
#define LEXICAL_ANALYZER_HPP_INCLUDED


#include <unordered_map>
#include <string>
#include <vector>


using namespace std;


class LexicalAnalyzer{
    private:
    public:
        string to_lower(string line);
        string remove_comments(string line);
        vector<string> analyze_tokens_from_line(string line);
        LexicalAnalyzer();
};


#endif