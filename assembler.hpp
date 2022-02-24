#ifndef ASSEMBLER_HPP_INCLUDED
#define ASSEMBLER_HPP_INCLUDED
#include <string>
#include <unordered_map>
#include "error_dealer.hpp"
#include "lexical_analyzer.hpp"
#include "object_generator.hpp"
#include "semantic_analyzer.hpp"
#include "syntactic_analyzer.hpp"


using namespace std;




class Assembler{
    private:
        int option;
        int line_counter = 1;
        int position_counter = 0;
        
        string text;
        string outputfile;
        string macrolabel;
        string macrodefinition;

        bool save_macro_lines = false;

        vector<string> lines;
        vector<vector<string>> text_tokens;
        
        string read_file(char* filename);
        void load_directives(const string filename);
        void load_instructions(const string filename);
    public:
        Assembler(int option, char* inputfile, char* outputfile);
        
        unordered_map<string, Symbol> SymbolsTable;
        unordered_map<string, Directive> DirectivesTable;
        unordered_map<string, Instruction> InstructionsTable;

        ErrorDealer* Err;
        LexicalAnalyzer* Lex;
        SyntacticAnalyzer* Syn;
        SemanticAnalyzer* Sem;
        ObjectGenerator* ObjGen;

        void first_pass();
        void second_pass();
        void run();
        void obj_op(vector<string> tokens, string label, int line_counter, string line);
        void mac_op(vector<string> tokens, string label, int line_counter, string line);
        void pre_op(vector<string> tokens, string label, int line_counter, string line);
};


#endif