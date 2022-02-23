#ifndef ETC_HPP_INCLUDED
#define ETC_HPP_INCLUDED


//#include <string>


//using namespace std;


// Defines
#define OPTION_PRE "-p"
#define OPTION_PRE_NUM 0
#define OPTION_OBJ "-o"
#define OPTION_OBJ_NUM 1
#define OPTION_MAC "-m"
#define OPTION_MAC_NUM 2
#define INSTRUCTIONS "Assembler - Software Básico\nAlexandre Kaihara - 18/0029690\n\nCommands:\n./montador -o [program_name].asm [output_name].obj\n./montador -p [program_name].asm [output_name].obj\n./montador -m [program_name].asm [output_name].obj\n"
#define INSTRUCTIONFILE "instructions.txt"
#define DIRECTIVEFILE "directives.txt"
#define LABELCHAR ':'
#define SPACECHAR ' '
#define LEX_ERR_99CHAR 11
#define LEX_ERR_STARTNUM 12
#define LEX_ERR_INVALIDCHAR 13
#define SYN_ERR_INST_DIR_NOT_FOUND 21
#define SYN_ERR_INVALID_NUM_OF_PARAM 22
#define SYN_ERR_INVALID_COPY_SYNTAX 23
#define SYN_ERR_INVALID_CONST_SYNTAX 24
#define SEM_ERR_MISPLACED_EQU_DEF 31
#define SEM_ERR_MULTIPLE_LABEL_DEF 32
#define SEM_ERR_IF_WITHOUT_EQU_DEF 33
#define SEM_ERR_LABEL_NOT_DEFINED 34
#define SEM_ERR_EQU_NOT_USED 35
#define SEM_ERR_MULTIPLE_MACRO_DEF 36
#define SEM_ERR_ENDMACRO_WITHOUT_MACRO_DEF 37
#define SEM_ERR_MACRO_NOT_USED 38
#define SEM_ERR_MACRO_WITHOUT_ENDMACRO_DEF 39



struct EQU{
    string token;
    bool defined = false;
};


struct Symbol{
    bool defined = false;
    int last_occurence = -1;
    int position = -1;
};


struct Directive {
    int operands = -1;
    int size = -1;
};


struct Instruction{
    int operands = -1;
    int opcode = -1;
    int size = -1;
};


#endif