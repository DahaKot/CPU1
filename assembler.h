//
// Created by dasch on 23.10.2017.
//

#ifndef ASSEMBLER_ASSEMBLER_H
#define ASSEMBLER_ASSEMBLER_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <mem.h>
#include <math.h>
#include <time.h>
#include "Constants.h"
#include "ASM_commands.h"

//set if(0) if you don't need this
#define ASM_DEBUG

typedef double data_t;

struct Label {
    char *name;
    size_t line;
};
data_t *File_Read(size_t *c_index);
void Log_write(int err_code, int line);
size_t Find_Line (struct Label **labels, char *Name, size_t num_labs);
struct Label *Label_Construct();
void File_Write(data_t *source, size_t len);
int Word_Treat (char **word, data_t **ram);

#endif //ASSEMBLER_ASSEMBLER_H
