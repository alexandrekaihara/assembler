#ifndef ERROR_DEALER_HPP_INCLUDED
#define ERROR_DEALER_HPP_INCLUDED


#include <string>


using namespace std;


class ErrorDealer{
    private:
        int option;
    public:
        ErrorDealer(int option);
        void register_err(int line, int code);
};


#endif