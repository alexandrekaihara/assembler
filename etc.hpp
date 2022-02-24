#ifndef ETC_HPP_INCLUDED
#define ETC_HPP_INCLUDED


#include <string>


using namespace std;


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
#define LEX_ERR_99CHAR 110
#define LEX_ERR_STARTNUM 120
#define LEX_ERR_INVALIDCHAR 130
#define SYN_ERR_INST_DIR_NOT_FOUND 210
#define SYN_ERR_INVALID_NUM_OF_PARAM 220
#define SYN_ERR_INVALID_COPY_SYNTAX 230
#define SYN_ERR_INVALID_CONST_SYNTAX 240
#define SEM_ERR_MISPLACED_EQU_DEF 310
#define SEM_ERR_MULTIPLE_LABEL_DEF 320
#define SEM_ERR_IF_WITHOUT_EQU_DEF 330
#define SEM_ERR_LABEL_NOT_DEFINED 340
#define SEM_ERR_EQU_NOT_USED 350
#define SEM_ERR_IF_WITH_INCORRECT_EQU_VAL 351
#define SEM_ERR_MULTIPLE_MACRO_DEF 360
#define SEM_ERR_ENDMACRO_WITHOUT_MACRO_DEF 370
#define SEM_ERR_MACRO_NOT_USED 380
#define SEM_ERR_MACRO_WITHOUT_ENDMACRO_DEF 390


struct EQU{
    string token;
    bool used = false;
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

struct Space{
    string name;
    int value = 0;
}

#endif