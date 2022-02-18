#ifndef ASSEMBLER_HPP_INCLUDED
#define ASSEMBLER_HPP_INCLUDED
#include <string>
#include <unordered_map>
#include "lexical_analyzer.hpp"
#include "semantic_analyzer.hpp"
#include "syntatic_analyzer.hpp"


using namespace std;


struct Symbol{
    int defined = 0;
    int last_occurence = -1;
};


struct Directive {
    int operands = -1;
    int size = -1;
};


struct Instruction{
    int operands = -1;
    int opcode = -1;
    int size = -1;
};


class Assembler{
    private:
        int option;
        int line_counter = 1;
        int position_counter = 0;
        
        string text;
        string outputfile;
        string macrodefinition;

        unordered_map<string, Symbol> SymbolsTable;
        unordered_map<string, Directive> DirectivesTable;
        unordered_map<string, Instruction> InstructionsTable;

        void read_file(char* filename);
        void load_instructions(const string filename);
        void load_directives(const string filename);
    public:
        Assembler(int option, char* inputfile, char* outputfile);
        
        LexicalAnalyzer* Lex;
        SyntaticAnalyzer* Syn;
        SemanticAnalyzer* Sem;

        void run();
};


#endif