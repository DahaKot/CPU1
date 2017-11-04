#include <stdio.h>
#include "assembler.h"

int main() {
    size_t len = 0;
    data_t *ram = File_Read(&len);

    File_Write(ram, len);

    return 0;
}