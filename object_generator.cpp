#include "object_generator.hpp"


ObjectGenerator::ObjectGenerator(int option, ErrorDealer* Err, unordered_map<string, Directive>* DirectivesTable, unordered_map<string, Instruction>* InstructionsTable, unordered_map<string, Symbol>* SymbolsTable){
    this->option = option;
    this->Err = Err;
    this->DirectivesTable = DirectivesTable;
    this->InstructionsTable = InstructionsTable;
    this->SymbolsTable = SymbolsTable;
}


// Adds a new symbol to the SymbolsTable
void ObjectGenerator::add_symbol(string symbol, bool defined, int last_occurence, int position){
    this->SymbolsTable[symbol] = {defined, last_occurence, position};
}


// Update the data of a existing symbol
void ObjectGenerator::update_symbol(string symbol, bool defined, int last_occurence, int position){
    *this->SymbolsTable[symbol] = {defined, last_occurence, position};
}


// Returns a existing Symbol object
Symbol ObjectGenerator::get_symbol(string symbol){
    return *this->SymbolsTable[symbol];
} 


// Verifies if the symbol is already defined 
bool ObjectGenerator::is_symbol_defined(string symbol){
    return *this->SymbolsTable[symbol].defined;
}


// Verifies if teh symbol exists on SymbolsTable
bool ObjectGenerator::symbol_exists(string symbol){
    return 
}


// Adds a EQU definition to the EQUdefinition map
void ObjectGenerator::add_equ_definition(string equlabel, string token, bool used){}
        

// Returns an existing EQU object
EQU ObjectGenerator::get_equ(string equlabel){}

        
// Set the used value to true on a EQU definition
void ObjectGenerator::set_equ_used(string equlabel){}


// Get opcode of a token
int ObjectGenerator::get_opcode(string token){}


// Updates a vale of a specific position of the object file
void ObjectGenerator::update_objectfile(int value, int position){}


// Add a value to the object file
bool ObjectGenerator::add_to_objectfile(int value){}


// returns the size of a instruction
int ObjectGenerator::get_instruction_size(string token){
}


// Get the size of the directive by its directive name
int ObjectGenerator::get_directive_size(string token){}


// Resolve all pending references of a defined label
void ObjectGenerator::further_reference_dealer(string label){}


// Resolves all EQU definitions
string ObjectGenerator::resolve_equ_definitions(string token){
}


// checks if the token is defined asa EQU
bool ObjectGenerator::is_equ_definition(string token){}



// 
bool ObjectGenerator::analyze(string line){
    return true;
}


// Add a space to be defined at the end of file
bool ObjectGenerator::add_space_definition(string label, int value){}


// Add to the object file all the spaces created and resolve all spaces references
bool ObjectGenerator::add_spaces_to_objectfile(){}


// Adds the line if option -p was given
bool ObjectGenerator::add_line_pre_option(string line){}


// Adds the line if option -m was given
bool ObjectGenerator::add_line_mac_option(string line){}
