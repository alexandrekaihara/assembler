#include "error_dealer.hpp"


ErrorDealer::ErrorDealer(int option){
    this->option = option;

    this->print_options[LEX_ERR_99CHAR] = OPTION_OBJ_NUM;
    this->print_options[LEX_ERR_STARTNUM] = OPTION_OBJ_NUM;
    this->print_options[LEX_ERR_INVALIDCHAR] = OPTION_OBJ_NUM;
    this->print_options[SYN_ERR_INST_DIR_NOT_FOUND] = OPTION_OBJ_NUM;
    this->print_options[SYN_ERR_INVALID_NUM_OF_PARAM] = OPTION_OBJ_NUM;
    this->print_options[SYN_ERR_INVALID_COPY_SYNTAX] = OPTION_OBJ_NUM;
    this->print_options[SYN_ERR_INVALID_CONST_SYNTAX] = OPTION_OBJ_NUM;
    this->print_options[SEM_ERR_MISPLACED_EQU_DEF] = OPTION_OBJ_NUM;
    this->print_options[SEM_ERR_MULTIPLE_LABEL_DEF] = OPTION_OBJ_NUM;
    this->print_options[SEM_ERR_IF_WITHOUT_EQU_DEF] = OPTION_PRE_NUM;
    this->print_options[SEM_ERR_LABEL_NOT_DEFINED] = OPTION_OBJ_NUM;
    this->print_options[SEM_ERR_MULTIPLE_LABEL_DEF_ON_SAME_LINE] = OPTION_OBJ_NUM;
    this->print_options[SEM_ERR_EQU_NOT_USED] = OPTION_PRE_NUM;
    this->print_options[SEM_ERR_IF_WITH_INCORRECT_EQU_VAL] = OPTION_PRE_NUM;
    this->print_options[SEM_ERR_IF_WITH_NON_NUMERICAL_ARG] = OPTION_PRE_NUM;
    this->print_options[SEM_ERR_MULTIPLE_MACRO_DEF] = OPTION_MAC_NUM;
    this->print_options[SEM_ERR_ENDMACRO_WITHOUT_MACRO_DEF] = OPTION_MAC_NUM;
    this->print_options[SEM_ERR_MACRO_NOT_USED] = OPTION_MAC_NUM;
    this->print_options[SEM_ERR_MACRO_WITHOUT_ENDMACRO_DEF] = OPTION_MAC_NUM;
}


// Save all logs of all errors
void ErrorDealer::register_err(int line, int code){
    this->errors.push_back({line, code});
}


// Clear all errors registered so far
void ErrorDealer::clean_errors(){
    this->errors.clear();
}


// prints all errors according to the option given
void ErrorDealer::show(){
    for(int i=0; i<this->errors.size(); i++){
        Error err = this->errors[i];
        if(this->print_options[err.code] == this->option)
            this->print_error(err.line, err.code);
    }
}


// printas all errors
void ErrorDealer::show_all(){
    for(int i=0; i<this->errors.size(); i++){
        Error err = this->errors[i];
        this->print_error(err.line, err.code);
    }
}


// Prints the error according to the code
void ErrorDealer::print_error(int line, int code){
    switch (code)
    {
    case LEX_ERR_99CHAR:
        cout << "Error on line " << line << ": Variable with more than 99 char (Lexical)\n";
        break;
    case LEX_ERR_STARTNUM:
        cout << "Error on line " << line << ": Illegal variable name starting with number (Lexical)\n";
        break;
    case LEX_ERR_INVALIDCHAR:
        cout << "Error on line " << line << ": Illegal variable name. Only numeric, alphabetic and undescore permitted (Lexical)\n";
        break;
    case SYN_ERR_INST_DIR_NOT_FOUND:
        cout << "Error on line " << line << ": Incorrect Instruction or Directive name (Syntactic)\n";
        break;
    case SYN_ERR_INVALID_NUM_OF_PARAM:
        cout << "Error on line " << line << ": Invalid number of parameters (Syntactic)\n";
        break;
    case SYN_ERR_INVALID_COPY_SYNTAX:
        cout << "Error on line " << line << ": COPY syntax expects two parameters separated by comma and space (Syntactic)\n";
        break;
    case SYN_ERR_INVALID_CONST_SYNTAX:
        cout << "Error on line " << line << ": CONST expects a numerical argument (Syntactic)\n";
        break;
    case SEM_ERR_MISPLACED_EQU_DEF:
        cout << "Error on line " << line << ": All EQU definitions must be declared at the top of the file ONLY (Semantic)\n";
        break;
    case SEM_ERR_MULTIPLE_LABEL_DEF:
        cout << "Error on line " << line << ": Label already defined (Semantic)\n";
        break;
    case SEM_ERR_IF_WITHOUT_EQU_DEF:
        cout << "Error on line " << line << ": IF expects only a EQU definition as argument (Semantic)\n";
        break;
    case SEM_ERR_LABEL_NOT_DEFINED:
        cout << "Error on line " << line << ": Label definition  not found (Semantic)\n";
        break;
    case SEM_ERR_MULTIPLE_LABEL_DEF_ON_SAME_LINE:
        cout << "Error on line " << line << ": Multiple label definition for the same line. Only supported ona label for each line (Semantic)\n";
        break;
    case SEM_ERR_EQU_NOT_USED:
        cout << "Error on line " << line << ": EQU not used (Semantic)\n";
        break;
    case SEM_ERR_IF_WITH_INCORRECT_EQU_VAL:
        cout << "Error on line " << line << ": IF directive expects as value only 1 or 0 (Semantic)\n";
        break;
    case SEM_ERR_IF_WITH_NON_NUMERICAL_ARG:
        cout << "Error on line " << line << ": IF directive accept only numerical arguments. Non-numerical given (Semantic)\n";
        break;
    case SEM_ERR_MULTIPLE_MACRO_DEF:
        cout << "Error on line " << line << ": Multiple MACRO definitions. Only one supported by program (Semantic)\n";
        break;
    case SEM_ERR_ENDMACRO_WITHOUT_MACRO_DEF:
        cout << "Error on line " << line << ": Definition of ENDMACRO without MACRO declaration (Semantic)\n";
        break;
    case SEM_ERR_MACRO_NOT_USED:
        cout << "Error on line " << line << ": MACRO defined but not used (Semantic)\n";
        break;
    case SEM_ERR_MACRO_WITHOUT_ENDMACRO_DEF:
        cout << "Error on line " << line << ": Definition of MACRO without ENDMACRO declaration (Semantic)\n";
        break;
    default:
        break;
    }
}
