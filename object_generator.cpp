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
void ObjectGenerator::add_line_preprocessed_file(string line){
    this->preprocessed_lines.push_back(line);
}


// Adds the line if option -p was given
void ObjectGenerator::remove_line_pre_option(){
    if(this->option == OPTION_PRE_NUM)
        this->preprocessed_lines.pop_back();
}


// Adds the line if option -m was given
void ObjectGenerator::remove_line_mac_option(){
    if(this->option == OPTION_MAC_NUM)
        this->preprocessed_lines.pop_back();
}


// Get the last reference value of a symbol
int ObjectGenerator::get_last_occurence_symbol(string label){
    return (*this->SymbolsTable)[label].last_occurence;
}


// Creates a file with the object file content separated by a single whitespace
void ObjectGenerator::generate_file(string filename){
    if(this->option == OPTION_OBJ_NUM){
        string objecttext;
        for(int i=0; i<this->objectfile.size(); i++){
            objecttext += to_string(this->objectfile[i]);
            if(i<this->objectfile.size()-1)
                objecttext += " ";
        }
        std::ofstream outfile (filename);
        outfile << objecttext;
        outfile.close();
    }
    else if(this->option == OPTION_MAC_NUM || this->option == OPTION_PRE_NUM){
        string text;
        for(int i=0; i<this->preprocessed_lines.size(); i++)
            text += this->preprocessed_lines[i] + "\n";
        std::ofstream outfile (filename);
        outfile << text;
        outfile.close();   
    }
}


// Returns if the label represents the definition of a space
bool ObjectGenerator::is_a_space_label(string label){
    for(int i=0; i<this->spacedefinition.size(); i++)
        if(this->spacedefinition[i].name.compare(label) == 0)
            return true;
    return false;
}


void ObjectGenerator::substitute_equ_pre_file(string token, string str_to_be_replaced){
    //int sz = this->preprocessed_lines.size();
    //int index = this->preprocessed_lines[sz-1].find(str_to_be_replaced);
    //this->preprocessed_lines[sz-1].replace(index, token.length(), token);
    if(this->option == OPTION_PRE_NUM){
        int sz = this->preprocessed_lines.size();
        int index = this->preprocessed_lines[sz-1].find(str_to_be_replaced);
        string pattern = ", ;";
        // Find the end of the token
        int i=index;
        for(; i<sz; i++)
            if(pattern.find(this->preprocessed_lines[sz-1]) == 0) break;
        // If the string to be replaced is at the end of the string, just add it
        cout << this->preprocessed_lines[sz-1] << " " << index << " " << i << " " << this->preprocessed_lines[sz-1][i] << ' ';
        if(i == sz)
            this->preprocessed_lines[sz-1] = this->preprocessed_lines[sz-1].substr(0, index) + token;
        else{
            string start = this->preprocessed_lines[sz-1].substr(0, index);
            string end = this->preprocessed_lines[sz-1].substr(i, sz-i);
            this->preprocessed_lines[sz-1] = start + token + end; 
        }
        cout << this->preprocessed_lines[sz-1] << "\n";
    }
}



// This function substitutes the equ definitions inside the parameter of instructions or directives
void ObjectGenerator::substitute_equ_variables_in_macro_definitions(vector<string> tokens){
    if(this->option == OPTION_PRE_NUM){
        for(int j=1; j<tokens.size(); j++){
        // If the token is defined as EQU, substitute it
            if(this->is_equ_definition(tokens[j])){
                string equtoken = this->resolve_equ_definitions(tokens[j]);
                this->substitute_equ_pre_file(equtoken, tokens[j]);
            }
        }
    }
}
