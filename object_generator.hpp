#ifndef OBJECT_GENERATOR_HPP_INCLUDED
#define OBJECT_GENERATOR_HPP_INCLUDED


#include <string>
#include <vector>
#include <unordered_map>
#include "etc.hpp"
#include "error_dealer.hpp"


using namespace std;


class ObjectGenerator{
    private:
        int option;
        int waiting_for_ENDMACRO = false;
        ErrorDealer* Err;
        unordered_map<string, Directive>* DirectivesTable;
        unordered_map<string, Instruction>* InstructionsTable;
    public:
        ObjectGenerator(int option, ErrorDealer* Err, unordered_map<string, Directive> &DirectivesTable, unordered_map<string, Instruction> &InstructionsTable);
        bool analyze(string line);
        // Get the size of the instruction by its instruction name
        int get_instruction_size(string token);
        // Get the size of the directive by its directive name
        int get_directive_size(string token);
        // Add label to the SymbolsTable
        bool add_label(vector<string> tokens, label);
        // Add a new line to the macro definition
        bool add_line_macro(string line);
        // If finds a name of a macro, substitute the current line for the lines of the macro
        bool substitute_macro();
        // When find a IF, resolve it, ignoring the subsequent line or putting in the code
        bool resolve_IF(vector<string> tokens);
        // get opcode of a token
        bool resolve_OPCODE(string token);
        // Add a value to the object file
        bool add_to_objectfile(int value);
        void further_reference_dealer(string label);
};


#endif