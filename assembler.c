//
// Created by dasch on 28.10.2017.
//

/*комменты
 *
 * комменты, вывод котика во время ошибки
 *
 * обработка strtod()?
 * */

#include <ctype.h>
#include "assembler.h"

struct Label *Label_Construct() {
    struct Label *new_one = calloc(one, sizeof(struct Label));

    new_one->name = calloc(LABEL_LEN, sizeof(char));
    if (new_one->name == NULL) {
        ASM_DEBUG Log_write(NOT_ENOUGH_MEMORY, __LINE__);
        return (void *) NOT_ENOUGH_MEMORY;
    }
    new_one->line = 0;

    return new_one;
}

data_t *File_Read(size_t *c_index) {
    ASM_DEBUG Log_write(START_READING, __LINE__);

    FILE *source;
    source = fopen("Source.txt", "r");
    if (source == NULL) {
        ASM_DEBUG Log_write(NO_FILE, __LINE__);
        return (void *) NO_FILE;
    }

    data_t *ram = calloc(RAM_SIZE, sizeof(data_t));
    struct Label **labels = calloc(NUM_LABELS, sizeof(struct Label *));
    if (labels == NULL) {
        ASM_DEBUG Log_write(NOT_ENOUGH_MEMORY, __LINE__);
        return (void *) NOT_ENOUGH_MEMORY;
    }

    *c_index = 0;
    size_t lab_count = 0;
    char *word = calloc(COMMAND_LEN, sizeof(char));
    if (word == NULL) {
        ASM_DEBUG Log_write(NOT_ENOUGH_MEMORY, __LINE__);
        return (void *) NOT_ENOUGH_MEMORY;
    }

    while (!feof(source)) {
        fscanf(source, "%s", word);
        printf("The word is: %s\n", word);
        printf("The command number: %d\n", *c_index);

        if (word[strlen(word)-1] == ':') {
            ASM_DEBUG Log_write(LABEL, __LINE__);

            printf("Label\n");

            labels[lab_count] = Label_Construct();

            printf("Label\n");

            int i = 0;
            for ( ; i < strlen(word); i++) {
                labels[lab_count]->name[i] = word[i];
            }

            printf("Label\n");

            labels[lab_count]->line = (*c_index);

            lab_count++;

            printf("=\n");
            for (int l = 0; l < lab_count; l++) {
                printf("%d", l);
                printf("Label %s points on %d line\n", labels[l]->name, labels[l]->line);
            }
            printf("=\n");

            (*c_index)--;
        }
        cmd(ADD_s,  ADD)
        cmd(SUB_s,  SUB)
        cmd(MUL_s,  MUL)
        cmd(DIV_s,  DIV)
        cmd(IDIV_s, IDIV)
        cmd(OUT_s,  OUT)
        cmd(IN_s,   IN)
        cmd(SQRT_s, SQRT)
        cmd(SIN_s,  SIN)
        cmd(COS_s,  COS)
        cmd(RET_s,  RET)
        cmd(END_s,  END)
        cmd(MEOW_s, MEOW)
        else if (strcmp(word, PUSH_s) == 0) {
            fscanf(source, "%s", word);
            if (isdigit((int) word[0]) || word[0] == '-') {
                ASM_DEBUG Log_write(PUSH_NUMBER, __LINE__);

                ram[(*c_index)] = PUSH_NUMBER;
                (*c_index)++;
                if (strtod(word, NULL) != POISON) {
                    ram[(*c_index)] = strtod(word, NULL);
                }
                else {
                    ASM_DEBUG Log_write(INVALID_COMMAND, __LINE__);
                    return (void *) INVALID_COMMAND;
                }
            }
            else if (isalpha((int) word[0])) {
                ASM_DEBUG Log_write(PUSH_REG, __LINE__);

                ram[(*c_index)] = PUSH_REG;
                (*c_index)++;
                ram[(*c_index)] = word[0] - 96 + 40;
            }
            else {
                ASM_DEBUG Log_write(INVALID_COMMAND, __LINE__);
                return (void *) INVALID_COMMAND;
            }
        }
        else if (strcmp(word, POP_s) == 0) {
            fscanf(source, "%s", word);

            if (word[0] < 101 && word[0] > 96) { //alpha
                ASM_DEBUG Log_write(POP_REG, __LINE__);

                ram[(*c_index)] = POP_REG;
                (*c_index)++;
                ram[(*c_index)] = word[0] - 96 + 40;
            }
            else {
                ASM_DEBUG Log_write(INVALID_COMMAND, __LINE__);
                return (void *) INVALID_COMMAND;
            }
        }
        else if (strcmp(word, LOG_s) == 0) {
            fscanf(source, "%s", word);
            if (isdigit((int) word[0])) { //digit
                ASM_DEBUG Log_write(LOG, __LINE__);

                ram[*c_index] = LOG;
                (*c_index)++;
                if (strtod(word, NULL) != POISON) {
                    ram[*c_index] = strtod(word, NULL);
                }
                else {
                    ASM_DEBUG Log_write(INVALID_COMMAND, __LINE__);
                    return (void *) INVALID_COMMAND;
                }
            }
            else {
                ASM_DEBUG Log_write(INVALID_COMMAND, __LINE__);
                return (void *) INVALID_COMMAND;
            }
        }
        else if (strcmp(word, POW_s) == 0) {
            ASM_DEBUG Log_write(POW, __LINE__);

            fscanf(source, "%s", word);
            if (word[0] < 58 && word[0] > 47) { //digit
                ram[*c_index] = POW;
                (*c_index)++;
                if (strtod(word, NULL) != POISON) {
                    ram[*c_index] = strtod(word, NULL);
                }
                else {
                    ASM_DEBUG Log_write(INVALID_COMMAND, __LINE__);
                    return (void *) INVALID_COMMAND;
                }
            }
            else {
                ASM_DEBUG Log_write(INVALID_COMMAND, __LINE__);
                return (void *) INVALID_COMMAND;
            }
        }
        else if (word[0] == 'j') {
            ASM_DEBUG Log_write(JMP, __LINE__);

            if (strcmp(word, JMP_s) == 0) {
                ram[*c_index] = JMP;
            }
            jump(JE_s, JE)
            jump(JNE_s, JNE)
            jump(JA_s, JA)
            jump(JAE_s, JAE)
            jump(JB_s, JB)
            jump(JBE_s, JBE)
            else {
                ASM_DEBUG Log_write(INVALID_COMMAND, __LINE__);
                return (void *) INVALID_COMMAND;
            }

            (*c_index)++;
            fscanf(source, "%s", word);
            ram[*c_index] = no_line;
        }
        else if (strcmp(word, CALL_s) == 0) {
            ASM_DEBUG Log_write(CALL, __LINE__);

            ram[*c_index] = CALL;
            (*c_index)++;
            fscanf(source, "%s", word);

            ram[*c_index] = no_line;
        }
        else if (word[0] == '\n') {
            ASM_DEBUG Log_write(EMPTY_STRING, __LINE__);
            continue;
        }
        else {
            ASM_DEBUG Log_write(INVALID_COMMAND, __LINE__);
            return (void *) INVALID_COMMAND;
        }

        (*c_index)++;
    }

    ram[*c_index] = EOP;

    size_t Len = *c_index;
    rewind(source);
    *c_index = 0;
    fscanf(source, "%s", word);

    while (*c_index <= Len) {
        if (word[0] == 'j' || strcmp(word, CALL_s) == 0) {
            (*c_index)++;
            fscanf(source, "%s", word);

            ram[(*c_index)] = Find_Line(labels, word, lab_count);
            if (ram[*c_index] == WRONG_WORD) {
                ASM_DEBUG Log_write(WRONG_WORD, __LINE__);
                return (void *) WRONG_WORD;
            }
        }
        if (word[strlen(word) - 1] == ':') {
            fscanf(source, "%s", word);
            continue;
        }

        fscanf(source, "%s", word);
        (*c_index)++;
    }

    fclose(source);

    return ram;
}

size_t Find_Line (struct Label **labels, char *Name, size_t num_labs) {
    size_t position = 0;

    int j = 0;
    int i = 0;
    int match = 0;

    for ( ; position < num_labs; position++) {
        if (strlen(labels[position]->name) - strlen(Name) != 1) {
            continue;
        }
        if (labels[position]->name[0] == Name[0]) { //if the beginnings are the same...
            j = 1;
            i = 1;
            match = 1;
            while (labels[position]->name[i] != ':') {
                if (labels[position]->name[i] != Name[j]) {
                    match = 0;
                    break;
                }
                i++;
                j++;
            }

            if (match > 0) {
                return labels[position]->line;
            }
        }
    }

    ASM_DEBUG Log_write(WRONG_WORD, __LINE__);
    return WRONG_WORD;
}

void File_Write (data_t *source, size_t len) {
    FILE *Machine_code;
    Machine_code = fopen("Code.txt", "w");

    int i = 0;
    while (i < len) {
        if (source[i] == JMP || source[i] == PUSH_REG || source[i] == MOD || source[i] == POP_REG ||
            source[i] == LOG || source[i] == POW  || source[i] == PUSH_NUMBER || source[i] == CALL ||
            source[i] == JA || source[i] == JAE || source[i] == JB || source[i] == JBE ||
            source[i] == JE || source[i] == JNE) {
            fprintf(Machine_code, "%lg ", source[i]);
            i++;
            fprintf(Machine_code, "%lg\n", source[i]);
        }
        else {
            fprintf(Machine_code, "%lg\n", source[i]);
        }
        i++;
    }

    fclose(Machine_code);
}

void Log_write(int err_code, int line) {
    FILE *logs;
    logs = fopen("ASM Log.txt", "a+");

    static int start = 0;
    if (start == 0) {
        time_t current_time;
        time(&current_time);

        fprintf(logs, "==========================================================\n");
        fprintf(logs, "Program started: %s", ctime(&current_time));
        start++;
    }

    switch(err_code) {
        case (BAD_PTR):
            fprintf(logs, "Use NULL pointer in %d line", line);
            break;
        case (STOD):
            fprintf(logs, "Start converting string to number\n");
            break;
        case (START_READING):
            fprintf(logs, "Start reading.\n");
            break;
        case (LABEL):
            fprintf(logs, "%s\n", "Label met");
            break;
        case (PUSH_NUMBER):
            fprintf(logs, "%s.\n", PUSH_s);
            break;
        case (PUSH_REG):
            fprintf(logs, "%s.\n", PUSH_s);
            break;
        case (POP_REG):
            fprintf(logs, "%s.\n", POP_s);
            break;
        case (ADD):
            fprintf(logs, "%s.\n", ADD_s);
            break;
        case (SUB):
            fprintf(logs, "%s.\n", SUB_s);
            break;
        case (MUL):
            fprintf(logs, "%s.\n", MUL_s);
            break;
        case (DIV):
            fprintf(logs, "%s.\n", DIV_s);
            break;
        case (MOD):
            fprintf(logs, "%s.\n", MOD_s);
            break;
        case (IDIV):
            fprintf(logs, "%s.\n", IDIV_s);
            break;
        case (OUT):
            fprintf(logs, "%s.\n", OUT_s);
            break;
        case (IN):
            fprintf(logs, "%s.\n", IN_s);
            break;
        case (SQRT):
            fprintf(logs, "%s.\n", SQRT_s);
            break;
        case (SIN):
            fprintf(logs, "%s.\n", SIN_s);
            break;
        case (COS):
            fprintf(logs, "%s.\n", COS_s);
            break;
        case (LOG):
            fprintf(logs, "%s.\n", LOG_s);
            break;
        case (POW):
            fprintf(logs, "%s.\n", POW_s);
            break;
        case (JMP):
            fprintf(logs, "%s\n", JMP_s);
            break;
        case (CALL):
            fprintf(logs, "%s\n", CALL_s);
            break;
        case (RET):
            fprintf(logs, "%s\n", RET_s);
            break;
        case (END):
            fprintf(logs, "%s\n", END_s);
            break;
        case (INVALID_COMMAND):
            fprintf(logs, "You have a typo in line %d\n", line);
            break;
        case (WRONG_WORD):
            fprintf(logs, "Label mismatch %d\n", line);
            break;
        case (NOT_ENOUGH_MEMORY):
            fprintf(logs, "Can't alloc memory in line %d :C\n", line);
            break;
        case (STACK):
            fprintf(logs, "Check stack. May be, you are stupid\n");
            break;
        case (EMPTY_STRING):
            fprintf(logs, "Empty string met.\n");
            break;
        default: fprintf(logs, "Who knows, what's happening right now in %d?)\n", line);
    }

    fclose(logs);
}