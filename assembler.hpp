#ifndef ASSEMBLER_HPP_INCLUDED
#define ASSEMBLER_HPP_INCLUDED
#include <string>
#include <unordered_map>

using namespace std;


class Assembler{
    private:
        int option;
        int line_counter = 1;
        int position_counter = 0;
        string text;
        unordered_map<string, int, int> SymbolsTable;
        unordered_map<string, int, int, int> InstructionsTable;
        unordered_map<string, int, int> DirectivesTable;
        string macrodefinition;
        void read_file(char* filename);
    public:
        Assembler(int option, char* filename);
        void run();
};


#endif