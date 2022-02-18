#include "lexical_analyzer.hpp"
#include <unordered_map>
#include <string>
#include <iostream>



using namespace std;


LexicalAnalyzer::LexicalAnalyzer(unordered_map<string, int, int> SymbolsTable,\
            unordered_map<string, int, int> DirectivesTable,\
            unordered_map<string, int, int, int> InstructionsTable){
    this->SymbolsTable = SymbolsTable;
    this->DirectivesTable = DirectivesTable;
    this->InstructionsTable = InstructionsTable;

    for (auto& x: this->SymbolsTable) {
        std::cout << x.first << ": " << x.second << std::endl;
    }
    //cout << this->SymbolsTable["ZERO"];
    //cout << this->DirectivesTable["SPACE"];
    //cout << this->InstructionsTable["ADD"];
}