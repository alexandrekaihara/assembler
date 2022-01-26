#ifndef ASSEMBLER_HPP_INCLUDED
#define ASSEMBLER_HPP_INCLUDED
#include <string>


using namespace std;


class Assembler{
    private:
        int option;
        string text;
        void read_file(char* filename);
    public:
        Assembler(int option, char* filename);
        void run();
};


#endif