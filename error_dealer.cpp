#include "error_dealer.hpp"


ErrorDealer::ErrorDealer(int option){
    this->option = option;
}


// Save all logs of all errors
void ErrorDealer::register_err(int line, int code){
    switch (code)
    {
    case LEX_ERR_99CHAR:
        cout << "Error LEX_ERR_99CHAR on line " << line << "\n";
        break;
    case LEX_ERR_STARTNUM:
        cout << "Error LEX_ERR_STARTNUM on line " << line << "\n";
        break;
    case LEX_ERR_INVALIDCHAR:
        cout << "Error LEX_ERR_INVALIDCHAR on line " << line << "\n";
        break;
    case SYN_ERR_INST_DIR_NOT_FOUND:
        cout << "Error SYN_ERR_INST_DIR_NOT_FOUND on line " << line << "\n";
        break;
    case SYN_ERR_INVALID_NUM_OF_PARAM:
        cout << "Error SYN_ERR_INVALID_NUM_OF_PARAM on line " << line << "\n";
        break;
    case SYN_ERR_INVALID_COPY_SYNTAX:
        cout << "Error SYN_ERR_INVALID_COPY_SYNTAX on line " << line << "\n";
        break;
    case SYN_ERR_INVALID_CONST_SYNTAX:
        cout << "Error SYN_ERR_INVALID_CONST_SYNTAX on line " << line << "\n";
        break;
    default:
        break;
    }
}