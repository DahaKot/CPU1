//
// Created by dasch on 22.10.2017.
//

#ifndef ASSEMBLER_ASM_COMMANDS_H
#define ASSEMBLER_ASM_COMMANDS_H

enum COMMAND_CODES {
    PUSH_NUMBER = 1,
    POP_REG = 2,
    ADD = 3,
    SUB = 4,
    MUL = 5,
    DIV = 6,
    MOD = 7,
    IDIV = 8,
    OUT = 9,
    IN = 10,
    PUSH_REG = 11,
    SQRT = 12,
    END = 13,
    SIN = 14,
    COS = 15,
    LOG = 16,
    POW = 17,
    LABEL = 18,
    JMP = 19,
    JE = 20,
    JNE = 21,
    JA = 22,
    JAE = 23,
    JB = 24,
    JBE = 25,
    CALL = 26,
    RET = 27
};

static const char *PUSH_s = "push"; //2
static const char *POP_s = "pop";   //2
static const char *ADD_s = "add";   //1
static const char *SUB_s = "sub";
static const char *MUL_s = "mul";
static const char *DIV_s = "div";
static const char *MOD_s = "mod";   //2
static const char *IDIV_s = "idiv";
static const char *OUT_s = "out";
static const char *IN_s = "in";
static const char *SQRT_s = "sqrt";
static const char *END_s = "end";
static const char *SIN_s = "sin";
static const char *COS_s = "cos";
static const char *LOG_s = "log";    //2
static const char *POW_s = "pow";    //2
static const char *JMP_s = "jmp";    //2
static const char *JE_s = "je";    //2
static const char *JNE_s = "jne";    //2
static const char *JA_s = "ja";    //2
static const char *JAE_s = "jae";    //2
static const char *JB_s = "jb";    //2
static const char *JBE_s = "jbe";    //2
static const char *CALL_s = "call";  //2
static const char *RET_s = "ret";

#endif //ASSEMBLER_ASM_COMMANDS_H