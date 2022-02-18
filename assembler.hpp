#ifndef ASSEMBLER_HPP_INCLUDED
#define ASSEMBLER_HPP_INCLUDED
#include <string>
#include <unordered_map>
#include "lexical_analyzer.hpp"

using namespace std;


class Assembler{
    private:
        int option;
        int line_counter = 1;
        int position_counter = 0;
        
        string text;
        string macrodefinition;

        unordered_map<string, int, int> SymbolsTable;
        unordered_map<string, int, int> DirectivesTable;
        unordered_map<string, int, int, int> InstructionsTable;

        void read_file(char* filename);
    public:
        Assembler(int option, char* filename);
        LexicalAnalyzer Lex = new LexicalAnalyzer(&SymbolsTable, &DirectivesTable, &InstructionsTable)
        void run();
};


#endif