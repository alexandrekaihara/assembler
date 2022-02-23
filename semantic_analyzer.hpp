#ifndef SEMANTIC_ANALYZER_HPP_INCLUDED
#define SEMANTIC_ANALYZER_HPP_INCLUDED


#include <string>
#include <vector>
#include <unordered_map>
#include "etc.hpp"
#include "error_dealer.hpp"


using namespace std;


class SemanticAnalyzer{
    private:
        int option;
        bool can_define_EQU = true;
        bool waiting_for_ENDMACRO = false;
        bool macro_used = false;
        string macro_label;
        ErrorDealer* Err;
    public:
        unordered_map<string, EQU> EQU_definitions;
        unordered_map<string, Symbol> SymbolsTable;
        SemanticAnalyzer(int option, ErrorDealer* Err, unordered_map<string, Symbol> SymbolsTable);
        bool analyze(vector<string> tokens, string label, int line_counter);
        bool check_EQU(vector<string> tokens, string label, int line_counter);
        bool check_IF(vector<string> tokens, int line_counter);
        bool check_MACRO(vector<string> tokens, string label, int line_counter);
        bool check_if_all_labels_defined();
        bool check_if_all_EQU_used();
        bool end_check_MACRO(int line_counter);
        void set_macro_used(){ this->macro_used = true; };
};


#endif