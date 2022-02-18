#ifndef LEXICAL_ANALYZER_HPP_INCLUDED
#define LEXICAL_ANALYZER_HPP_INCLUDED


#include <unordered_map>
#include <string>


class LexicalAnalyzer{
    private:
        unordered_map<string, int, int> * ptrSymbolsTable;
        unordered_map<string, int, int>* ptrDirectivesTable;
        unordered_map<string, int, int, int>* ptrInstructionsTable;

    public:
        LexicalAnalyzer(unordered_map<string, int, int>* SymbolsTable,\
            unordered_map<string, int, int>* DirectivesTable,\
            unordered_map<string, int, int, int>* InstructionsTable)
};


#endif