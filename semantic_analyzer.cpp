#include "semantic_analyzer.hpp"


SemanticAnalyzer::SemanticAnalyzer(int optio, ErrorDealer* Err, unordered_map<string, Symbol>* SymbolsTable){
    this->option = option;
    this->Err = Err;
    this->SymbolsTable = SymbolsTable;
}


bool SemanticAnalyzer::analyze(vector<string> tokens, string label, int line_counter){
    int err = 0;
    bool status = false;
    
    // If the label is already defined, raise error
    if((!label.empty()) && (this->SymbolsTable->count(label) != 0) && (*this->SymbolsTable)[label].defined){
        err = SEM_ERR_MULTIPLE_LABEL_DEF;
        this->Err->register_err(line_counter, err);
    }
    // If label was not defined
    else{
        status = this->check_EQU(tokens, label, line_counter);
    }

    // Verificar se IF tem uma declaração de EQU anterior
    status = this->check_IF(tokens, line_counter);

    status = this->check_MACRO(tokens, label, line_counter);

    // If an error was encountered, register
    if(err != 0) return false;
    return true;
}


// The EQU que be defined only in the begginning of the file
bool SemanticAnalyzer::check_EQU(vector<string> tokens, string label, int line_counter){
    int err = 0;
    bool status = false;

    // Se for a definição de uma EQU
    if(tokens[0].compare("EQU") == 0){
        // If define EQU is true, so enable the definition of EQU
        if(this->can_define_EQU)
            this->EQU_definitions[label] = {tokens[1], false};
        else {
            err = SEM_ERR_MISPLACED_EQU_DEF;
            this->Err->register_err(line_counter, err);
        }
    }
    // If it is not a definition of a EQU, then no other EQU must be defined
    else this->can_define_EQU = false;
    
    if(err != 0) return false;
    return (true || status);
}


bool SemanticAnalyzer::check_IF(vector<string> tokens, int line_counter){
    int err = 0;

    // If the directive is IF
    if(tokens[0].compare("IF") == 0){
        // If there is no definition of EQU on first parameter of IF, raise error
        if (this->EQU_definitions.count(tokens[1]) == 0){
            err = SEM_ERR_IF_WITHOUT_EQU_DEF;
            this->Err->register_err(line_counter, err);
        }
        else{
            EQU equ = this->EQU_definitions[tokens[1]];
            try {
                if(stoi(equ.token) > 1 || stoi(equ.token) < 0){
                    err = SEM_ERR_IF_WITH_INCORRECT_EQU_VAL;
                    this->Err->register_err(line_counter, err);
                }
            }
            catch(...){
                this->Err->register_err(line_counter, err);
                err = SEM_ERR_IF_WITH_NON_NUMERICAL_ARG;
            } 
        }
    }
    
    if(err != 0) return false;
    return true;
}


bool SemanticAnalyzer::check_if_all_labels_defined(){
    for(auto sym : *this->SymbolsTable){
        // If any symbol was not defined
        if(!sym.second.defined){
            this->Err->register_err(sym.second.last_occurence, SEM_ERR_LABEL_NOT_DEFINED);
            return false;
        }
    }
    return true;
}


bool SemanticAnalyzer::check_if_all_EQU_used(){
    for(auto equ : this->EQU_definitions){
        if(!equ.second.used){
            this->Err->register_err(-1, SEM_ERR_EQU_NOT_USED);
            return false;
        }
    }
    return true;
}


// Set the used value to true on a EQU definition
void SemanticAnalyzer::set_equ_used(string equlabel){
    EQU equ = this->EQU_definitions[equlabel];
    equ.used = true;
    this->EQU_definitions[equlabel] = equ;
}


bool SemanticAnalyzer::check_MACRO(vector<string> tokens, string label, int line_counter){
    int err = 0;

    if(tokens[0].compare("MACRO") == 0){
        // If already has defined a macro, raise error (only one permitted per program)
        if(!this->macro_label.empty())
            err = SEM_ERR_MULTIPLE_MACRO_DEF;
        else {
            this->waiting_for_ENDMACRO = true;
            this->macro_label = label;
        }
    }
    else if(tokens[0].compare("ENDMACRO") == 0){
        // If there was not defined a MACRO before ENDMACRO, raise error
        if(!this->waiting_for_ENDMACRO){
            err = SEM_ERR_ENDMACRO_WITHOUT_MACRO_DEF;
            this->Err->register_err(line_counter, err);
        }
        else
            this->waiting_for_ENDMACRO = false;
    }
    
    if(err != 0) return false;
    return true;
}


bool SemanticAnalyzer::end_check_MACRO(){
    int err = 0;

    if(!this->macro_label.empty() && !this->macro_used){
        err = SEM_ERR_MACRO_NOT_USED;
        this->Err->register_err(-1, err);
    }

    if(this->waiting_for_ENDMACRO){
        err = SEM_ERR_MACRO_WITHOUT_ENDMACRO_DEF;
        this->Err->register_err(-1, err);
    }

    if(err != 0)
        return false;
    return true;
}


void SemanticAnalyzer::set_macro_used(){ this->macro_used = true; }