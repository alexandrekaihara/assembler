#ifndef OBJECT_GENERATOR_HPP_INCLUDED
#define OBJECT_GENERATOR_HPP_INCLUDED


#include <string>


using namespace std;


class ObjectGenerator{
    private:
        int option;
    public:
        ObjectGenerator(int option);
        void analyze(string line);
};


#endif