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
    (*this->SymbolsTable)[symbol] = {defined, last_occurence, position};
}


// Update the data of a existing symbol
void ObjectGenerator::update_symbol(string symbol, bool defined, int last_occurence, int position){
    (*this->SymbolsTable)[symbol] = {defined, last_occurence, position};
}


// Returns a existing Symbol object
Symbol ObjectGenerator::get_symbol(string symbol){
    return (*this->SymbolsTable)[symbol];
} 


// Verifies if the symbol is already defined 
bool ObjectGenerator::is_symbol_defined(string symbol){
    return (*this->SymbolsTable)[symbol].defined;
}


// Verifies if teh symbol exists on SymbolsTable
bool ObjectGenerator::symbol_exists(string symbol){
    return ((*this->SymbolsTable).count(symbol) != 0);
}


// Adds a EQU definition to the EQUdefinition map
void ObjectGenerator::add_equ_definition(string equlabel, string token, bool used){
    this->EQU_definitions[equlabel] = {token, used};
}
        

// Returns an existing EQU object
EQU ObjectGenerator::get_equ(string equlabel){
    return this->EQU_definitions[equlabel];
}

        
// Set the used value to true on a EQU definition
void ObjectGenerator::set_equ_used(string equlabel){
    EQU equ = this->EQU_definitions[equlabel];
    equ.used = true;
    this->EQU_definitions[equlabel] = equ;
}


// Get opcode of a token
int ObjectGenerator::get_opcode(string token){
    return (*this->InstructionsTable)[token].opcode;
}


// Updates a vale of a specific position of the object file
void ObjectGenerator::update_objectfile(int value, int position){
    this->objectfile[position] = value;
}


// Add a value to the object file
void ObjectGenerator::add_to_objectfile(int value){
    this->objectfile.push_back(value);
}


// returns the size of a instruction
int ObjectGenerator::get_instruction_size(string token){
    return (*this->InstructionsTable)[token].size;
}


// Get the size of the directive by its directive name
int ObjectGenerator::get_directive_size(string token){
    return (*this->DirectivesTable)[token].size;
}


// Resolve all pending references of a defined label
void ObjectGenerator::further_reference_dealer(string label, int lastoccurence){
    Symbol sym = (*this->SymbolsTable)[label];
    sym.last_occurence = lastoccurence;
    int val;
    // While it doesn't find the -1, resolve the references with the position value of the label
    while(lastoccurence != -1){
        sym.last_occurence = this->objectfile[lastoccurence];
        this->objectfile[lastoccurence] = sym.position;
        lastoccurence = sym.last_occurence;
    }
}


// Returns the token value of a given equ label
string ObjectGenerator::resolve_equ_definitions(string label){
    return this->EQU_definitions[label].token;
}


// checks if the token is defined as EQU
bool ObjectGenerator::is_equ_definition(string label){
    return (this->EQU_definitions.count(label) != 0);
}


// Add a space to be defined at the end of file
void ObjectGenerator::add_space_definition(string label, int value){
    this->spacedefinition.push_back({label, value});
}


// Add to the object file all the spaces created and resolve all spaces references
void ObjectGenerator::add_spaces_to_objectfile(int position_counter){
    int value, lastoccurence;
    string label;
    for(int i=0; i<this->spacedefinition.size(); i++){
        value = this->spacedefinition[i].value;
        label = this->spacedefinition[i].name;
        // Adds the spaces into the objectfile
        this->add_to_objectfile(this->spacedefinition[i].value);
        // Resolve all pending references that this space
        lastoccurence = this->get_last_occurence_symbol(label);
        this->update_symbol(label, true, -1, position_counter);
        this->further_reference_dealer(label, lastoccurence);
        position_counter++;
    }
}


// Adds the line if option -p was given
void ObjectGenerator::add_line_pre_option(string line){
    if(this->option == OPTION_PRE_NUM)
        this->preprocessed_lines.push_back(line);
}


// Adds the line if option -m was given
void ObjectGenerator::add_line_mac_option(string line){
    if(this->option == OPTION_MAC_NUM)
        this->preprocessed_lines.push_back(line);
}


// Get the last reference value of a symbol
int ObjectGenerator::get_last_occurence_symbol(string label){
    return (*this->SymbolsTable)[label].last_occurence;
}


void ObjectGenerator::generate_objectfile(string filename){
    string objecttext;
    for(int i=0; i<this->objectfile.size(); i++){
        objecttext += to_string(this->objectfile[i]) + " ";
    }
    std::ofstream outfile (filename);
    outfile << objecttext;
    outfile.close();
    cout << objecttext << "\n";
}
