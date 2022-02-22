#ifndef OBJECT_GENERATOR_HPP_INCLUDED
#define OBJECT_GENERATOR_HPP_INCLUDED


#include <string>
#include "error_dealer.hpp"


using namespace std;


class ObjectGenerator{
    private:
        int option;
        ErrorDealer* Err;
    public:
        ObjectGenerator(int option, ErrorDealer* Err);
        bool analyze(string line);
        void write(string line);
};


#endif