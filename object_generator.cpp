#include "object_generator.hpp"


ObjectGenerator::ObjectGenerator(int option, ErrorDealer* Err, unordered_map<string, Directive> DirectivesTable, unordered_map<string, Instruction> InstructionsTable){
    this->option = option;
    this->Err = Err;
    this->DirectivesTable = DirectivesTable;
    this->InstructionsTable = InstructionsTable;
}


bool ObjectGenerator::analyze(string line){
    return true;
}


int ObjectGenerator::get_instruction_size(string token){
}


// Get the size of the directive by its directive name
int ObjectGenerator::get_directive_size(string token){}


// Add label to the SymbolsTable
bool ObjectGenerator::add_label(vector<string> tokens, string label){}


// Add a new line to the macro definition
bool ObjectGenerator::add_line_macro(string line){}


// If finds a name of a macro, substitute the current line for the lines of the macro
bool ObjectGenerator::substitute_macro(){}


// When find a IF, resolve it, ignoring the subsequent line or putting in the code
bool ObjectGenerator::resolve_IF(vector<string> tokens){}


// get opcode of a token
bool ObjectGenerator::resolve_OPCODE(string token){}


// Add a value to the object file
bool ObjectGenerator::add_to_objectfile(int value){}


void ObjectGenerator::further_reference_dealer(string label){}

