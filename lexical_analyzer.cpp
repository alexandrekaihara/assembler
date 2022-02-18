#include "lexical_analyzer.hpp"
#include <unordered_map>
#include <string>
#include <iostream>



using namespace std;


LexicalAnalyzer::LexicalAnalyzer(unordered_map SymbolsTable,\
            unordered_map DirectivesTable,\
            unordered_map InstructionsTable){
    this->SymbolsTable = SymbolsTable;
    this->DirectivesTable = DirectivesTable;
    this->InstructionsTable = InstructionsTable;

    //cout << this->SymbolsTable["ZERO"];
    //cout << this->DirectivesTable["SPACE"];
    //cout << this->InstructionsTable["ADD"];
}