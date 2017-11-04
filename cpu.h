//
// Created by dasch on 04.11.2017.
//

#ifndef CPU_CPU_H
#define CPU_CPU_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <sys/types.h>
#include <time.h>
#include "ASM_commands.h"
#include "Constants.h"
#include "stack.h"

#define CPU_DEBUG

#define cmd_do(num, func) else if (code[c_cmd] == num) {\
                            CPU_DEBUG CLog_write(num, __LINE__);\
                                                                            \
                            data_t thing_1 = Stack_Pop(&(cpu->stack));\
                            data_t thing_2 = Stack_Pop(&(cpu->stack));\
                            if (thing_1 == ERR || thing_2 == ERR || thing_1 == EMPTY || thing_2 == EMPTY) {\
                                CPU_DEBUG CLog_write(STACK, __LINE__);\
                                return ERR;\
                            }\
                            check = Stack_Push(&(cpu->stack), func(thing_1, thing_2));\
                            if (check != ALL_RIGHT) {\
                                CPU_DEBUG CLog_write(STACK, __LINE__);\
                                return ERR;\
                            }\
                        }

#define jump_do(num, func)  else if (code[c_cmd] == JE) {\
                                CPU_DEBUG CLog_write(JMP, __LINE__);\
                                                                    \
                                data_t a = Stack_Pop(&(cpu->stack));\
                                data_t b = Stack_Pop(&(cpu->stack));\
                                if (a == ERR || b == ERR || a == EMPTY || b == EMPTY) {\
                                    CPU_DEBUG CLog_write(STACK, __LINE__);\
                                    return ERR;\
                                }\
                                if (func(a, b)) {\
                                    c_cmd = (int) code[c_cmd + 1];\
                                    c_cmd--;\
                                }\
                                else {\
                                    c_cmd++;\
                                }\
                            }

struct CPU {
    data_t ax;
    data_t bx;
    data_t cx;
    data_t dx;

    struct K_Stack *stack;
    struct K_Stack *Func_Stack;
};

enum regs {
    AX = 41,
    BX = 42,
    CX = 43,
    DX = 44
};

struct CPU *CPU_Construct();
int CPU_Run();
data_t *File_Read(size_t *cmd_ind);
void CLog_write(int err_code, size_t line);
data_t Log(data_t x, data_t basis);
void Draw_a_cat();

#endif //CPU_CPU_H
