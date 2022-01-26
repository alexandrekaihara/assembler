#ifndef ASSEMBLER_HPP_INCLUDED
#define ASSEMBLER_HPP_INCLUDED
#include <string>


class Assembler{
    private:
        int option;
        string text;
        string read_file(char* file_name);
    public:
        Assembler(int option, char* filename);
        void run();
}


#endif