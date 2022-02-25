#ifndef OBJECT_GENERATOR_HPP_INCLUDED
#define OBJECT_GENERATOR_HPP_INCLUDED


#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include "etc.hpp"
#include "error_dealer.hpp"


using namespace std;


class ObjectGenerator{
    private:
        int option;
        int waiting_for_ENDMACRO = false;
        
        vector<int> objectfile;
        vector<string> preprocessed_lines;
        
        unordered_map<string, Symbol>* SymbolsTable;
        unordered_map<string, Directive>* DirectivesTable;
        unordered_map<string, Instruction>* InstructionsTable;
        unordered_map<string, EQU> EQU_definitions;
        
        ErrorDealer* Err;
    public:
        vector<Space> spacedefinition;

        ObjectGenerator(int option, ErrorDealer* Err, unordered_map<string, Directive>* DirectivesTable, unordered_map<string, Instruction>* InstructionsTable, unordered_map<string, Symbol>* SymbolsTable);
        void add_symbol(string symbol, bool defined, int last_occurence, int position);
        void update_symbol(string symbol, bool defined, int last_occurence, int position);
        Symbol get_symbol(string symbol);
        bool is_symbol_defined(string symbol);
        bool symbol_exists(string symbol);
        void add_equ_definition(string equlabel, string token, bool used);
        EQU get_equ(string equlabel);
        void set_equ_used(string equlabel);
        int get_opcode(string token);
        void update_objectfile(int value, int position);
        void add_to_objectfile(int value);
        int get_instruction_size(string token);
        int get_directive_size(string token);
        void further_reference_dealer(string label, int lastoccurence);
        string resolve_equ_definitions(string label);
        bool is_equ_definition(string label);
        void add_space_definition(string label, int value);
        void add_spaces_to_objectfile(int position_counter);
        bool add_line_pre_option(string line);
        bool add_line_mac_option(string line);
        int get_last_occurence_symbol(string label);
        void generate_objectfile(string filename);
        
};


#endif