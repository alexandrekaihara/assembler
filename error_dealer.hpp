#ifndef ERROR_DEALER_HPP_INCLUDED
#define ERROR_DEALER_HPP_INCLUDED


#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include "etc.hpp"


using namespace std;


class ErrorDealer{
    private:
        int option;
        vector<Error> errors;
        unordered_map<int, int> print_options;
    public:
        ErrorDealer(int option);
        void register_err(int line, int code);
        void print_error(int line, int code);
        void clean_errors();
        void show();
};


#endif