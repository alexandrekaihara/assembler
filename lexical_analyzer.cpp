#include "lexical_analyzer.hpp"
#include <unordered_map>
#include <string>


using namespace std;


LexicalAnalyzer::LexicalAnalyzer(unordered_map<string, int, int> SymbolsTable,\
            unordered_map<string, int, int> DirectivesTable,\
            unordered_map<string, int, int, int> InstructionsTable){
    ptrSymbolsTable = SymbolsTable;
    ptrDirectivesTable = DirectivesTable;
    ptrInstructionsTable = InstructionsTable;

    cout << *ptrSymbolsTable["ZERO"];
    cout << *ptrDirectivesTable["SPACE"];
    cout << *ptrInstructionsTable["ADD"];
}