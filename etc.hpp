#ifndef ETC_HPP_INCLUDED
#define ETC_HPP_INCLUDED

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
#define SIN_ERR_INST_DIR_NOT_FOUND 21
#define SIN_ERR_INVALID_NUM_OF_PARAM 22
#define SIN_ERR_INVALID_COPY_SYNTAX 23
#define SIN_ERR_INVALID_CONST_SYNTAX 24

struct Symbol{
    int defined = 0;
    int last_occurence = -1;
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