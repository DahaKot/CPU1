#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include <math.h>
#include <time.h>

//set LOG = if(0) if you don't need it
#define DEBUG
#define POISON tan(M_PI/2)

static const int one = 1;
static const int no_line = -1;
static const size_t RAM_SIZE = 1024;                                //maximum size of array, RAM_SIZE/2 - max number of lines
static const size_t NUM_LABELS = 512;                               //number of labels is 100% less than RAM_SIZE/2
static const size_t COMMAND_LEN = 6;
static const size_t LABEL_LEN = 10;
static const char *PUSH_s = "push\0"; //2
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

typedef double data_t;

struct Label {
    char *name;
    size_t line;
};

data_t *File_Read(size_t *c_index);
void Log_write(int err_code, int line);
data_t stod (char *);                                               //convert a string to number
size_t Find_Line (struct Label **labels, char *Name, size_t num_labs);
struct Label *Label_Construct();
void File_Write(data_t *source, size_t len);

enum COMMAND_AND_LOG_CODES {
    NO_FILE = -6,
    BAD_PTR = -5,
    STOD = -4,
    START_READING = -3,
    INVALID_COMMAND = -2,
    NOT_ENOUGH_MEMORY = -1,
    WRONG_WORD = 0,
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
    JMP = 19
};

int main() {
    size_t len = 0;
    data_t *ram = File_Read(&len);

    int i = 0;
    while (i < len) {
        printf("%lg\n", ram[i]);
        i++;
    }

    File_Write(ram, len);

    free(ram);

    return 0;
}

struct Label *Label_Construct() {
    struct Label *new_one = calloc(one, sizeof(struct Label));

    new_one->name = calloc(LABEL_LEN, sizeof(char));
    if (new_one->name == NULL) {
        DEBUG Log_write(NOT_ENOUGH_MEMORY, __LINE__);
        return (void *) NOT_ENOUGH_MEMORY;
    }
    new_one->line = 0;

    return new_one;
}

data_t *File_Read(size_t *c_index) {
    DEBUG Log_write(START_READING, __LINE__);

    FILE *source;
    source = fopen("Source.txt", "r");
    if (source == NULL) {
        DEBUG Log_write(NO_FILE, __LINE__);
        return (void *) NO_FILE;
    }

    data_t *ram = calloc(RAM_SIZE, sizeof(data_t));
    struct Label **labels = calloc(NUM_LABELS, sizeof(struct Label *));
    if (labels == NULL) {
        DEBUG Log_write(NOT_ENOUGH_MEMORY, __LINE__);
        return (void *) NOT_ENOUGH_MEMORY;
    }

    *c_index = 0;
    size_t lab_count = 0;
    char *word = calloc(COMMAND_LEN, sizeof(char));
    if (word == NULL) {
        DEBUG Log_write(NOT_ENOUGH_MEMORY, __LINE__);
        return (void *) NOT_ENOUGH_MEMORY;
    }
    fscanf(source, "%s", word);

    while (strcmp(word, END_s) != 0) {
        if (word[strlen(word) - 1] == ':') {
            DEBUG Log_write(LABEL, __LINE__);

            labels[lab_count] = Label_Construct();
            labels[lab_count]->name = word;
            labels[lab_count]->line = (*c_index);
            lab_count++;

            fscanf(source, "%s", word);
            continue;
        }
        else if (strcmp(word, PUSH_s) == 0) {
            fscanf(source, "%s", word);
            if (word[0] < 58 && word[0] > 47) { //digit
                DEBUG Log_write(PUSH_NUMBER, __LINE__);

                ram[(*c_index)] = PUSH_NUMBER;
                (*c_index)++;
                if (stod(word) != POISON) {
                    ram[(*c_index)] = stod(word);
                }
                else {
                    DEBUG Log_write(INVALID_COMMAND, __LINE__);
                    return (void *) INVALID_COMMAND;
                }
            }
            else if (word[0] < 101 && word[0] > 96) { //alpha
                DEBUG Log_write(PUSH_REG, __LINE__);

                ram[(*c_index)] = PUSH_REG;
                (*c_index)++;
                ram[(*c_index)] = word[0] - 96;
            }
            else {
                DEBUG Log_write(INVALID_COMMAND, __LINE__);
                return (void *) INVALID_COMMAND;
            }
        }
        else if (strcmp(word, POP_s) == 0) {
            fscanf(source, "%s", word);

            if (word[0] < 101 && word[0] > 96) { //alpha
                DEBUG Log_write(POP_REG, __LINE__);

                ram[(*c_index)] = POP_REG;
                (*c_index)++;
                ram[(*c_index)] = word[0] - 96;
            }
            else {
                DEBUG Log_write(INVALID_COMMAND, __LINE__);
                return (void *) INVALID_COMMAND;
            }
        }
        else if (strcmp(word, ADD_s) == 0) {
            DEBUG Log_write(ADD, __LINE__);
            ram[(*c_index)] = ADD;
        }
        else if (strcmp(word, SUB_s) == 0) {
            DEBUG Log_write(SUB, __LINE__);
            ram[*c_index] = SUB;
        }
        else if (strcmp(word, MUL_s) == 0) {
            DEBUG Log_write(MUL, __LINE__);
            ram[*c_index] = MUL;
        }
        else if (strcmp(word, DIV_s) == 0) {
            DEBUG Log_write(DIV, __LINE__);
            ram[*c_index] = DIV;
        }
        else if (strcmp(word, MOD_s) == 0) {
            DEBUG Log_write(MOD, __LINE__);
            ram[*c_index] = MOD;
        }
        else if (strcmp(word, IDIV_s) == 0) {
            DEBUG Log_write(IDIV, __LINE__);
            ram[*c_index] = IDIV;
        }
        else if (strcmp(word, OUT_s) == 0) {
            DEBUG Log_write(OUT, __LINE__);
            ram[*c_index] = OUT;
        }
        else if (strcmp(word, IN_s) == 0) {
            DEBUG Log_write(IN, __LINE__);
            ram[*c_index] = IN;
        }
        else if (strcmp(word, SQRT_s) == 0) {
            DEBUG Log_write(SQRT, __LINE__);
            ram[*c_index] = SQRT;
        }
        else if (strcmp(word, SIN_s) == 0) {
            DEBUG Log_write(SIN, __LINE__);
            ram[*c_index] = SIN;
        }
        else if (strcmp(word, COS_s) == 0) {
            DEBUG Log_write(COS, __LINE__);
            ram[*c_index] = COS;
        }
        else if (strcmp(word, LOG_s) == 0) {
            fscanf(source, "%s", word);
            if (word[0] < 58 && word[0] > 47) { //digit
                DEBUG Log_write(LOG, __LINE__);

                ram[*c_index] = LOG;
                (*c_index)++;
                if (stod(word) != POISON) {
                    ram[*c_index] = stod(word);
                }
                else {
                    DEBUG Log_write(INVALID_COMMAND, __LINE__);
                    return (void *) INVALID_COMMAND;
                }
            }
            else {
                DEBUG Log_write(INVALID_COMMAND, __LINE__);
                return (void *) INVALID_COMMAND;
            }
        }
        else if (strcmp(word, POW_s) == 0) {
            DEBUG Log_write(POW, __LINE__);

            fscanf(source, "%s", word);
            if (word[0] < 58 && word[0] > 47) { //digit
                ram[*c_index] = POW;
                (*c_index)++;
                if (stod(word) != POISON) {
                    ram[*c_index] = stod(word);
                }
                else {
                    DEBUG Log_write(INVALID_COMMAND, __LINE__);
                    return (void *) INVALID_COMMAND;
                }
            }
            else {
                DEBUG Log_write(INVALID_COMMAND, __LINE__);
                return (void *) INVALID_COMMAND;
            }
        }
        else if (strcmp(word, JMP_s) == 0) {
            DEBUG Log_write(JMP, __LINE__);

            ram[*c_index] = JMP;
            (*c_index)++;
            ram[*c_index] = no_line;
        }
        else {
            DEBUG Log_write(INVALID_COMMAND, __LINE__);
            return (void *) INVALID_COMMAND;
        }

        (*c_index)++;
        fscanf(source, "%s", word);
    }
    ram[*c_index] = END;

    *c_index = 0;
    rewind(source);
    fscanf(source, "%s", word);

    while (strcmp(word, END_s) != 0) {
        if (strcmp(word, JMP_s) == 0) {
            fscanf(source, "%s", word);
            ram[*c_index] = Find_Line(labels, word, lab_count);
            if (ram[*c_index] == 0) {
                DEBUG Log_write(WRONG_WORD, __LINE__);
                return (void *) WRONG_WORD;
            }
        }

        fscanf(source, "%s", word);
        (*c_index)++;
    }

    fclose(source);

    return ram;
}

size_t Find_Line (struct Label **labels, char *Name, size_t num_labs) {
    size_t position = 0;
    while (position < num_labs) {
        if (strcmp(labels[position]->name, Name) == 0) {
            return labels[position]->line;
        }

        position++;
    }

    DEBUG Log_write(WRONG_WORD, __LINE__);
    return WRONG_WORD;
}

data_t stod (char *str) {
    DEBUG Log_write(STOD, __LINE__);
    if (str == NULL) {
        DEBUG Log_write(BAD_PTR, __LINE__);
        return BAD_PTR;
    }

    data_t number = 0;
    size_t c_digit = 0;
    int after_point = -1;

    while ((str[c_digit] < 58 && str[c_digit] > 47) || str[c_digit] == '.') {
        if (str[c_digit] == '.') {
            c_digit++;
            after_point++;
            continue;
        }
        if (after_point >= 0) {
            after_point++;
        }

        number = 10*number + (int) str[c_digit] - 48;
        c_digit++;
    }
    if (after_point >= 0) {
        number *= pow(10, (-1)*after_point);
    }

    return number;
}

void File_Write (data_t *source, size_t len) {
    FILE *Machine_code;
    Machine_code = fopen("Code.txt", "w");

    int i = 0;
    while (i < len) {
        if (source[i] == PUSH_REG || source[i] == JMP || source[i] == MOD || source[i] == POP_REG ||
                source[i] == LOG || source[i] == POW  || source[i] == PUSH_NUMBER) {
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
            fprintf(logs, "%s\n", "Label meeted");
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
        case (INVALID_COMMAND):
            fprintf(logs, "You have a typo in line %d\n", line);
            break;
        case (WRONG_WORD):
            fprintf(logs, "Label mismatch %d\n", line);
            break;
        case (NOT_ENOUGH_MEMORY):
            fprintf(logs, "Can't alloc memory in line %d :C\n", line);
            break;
        default: fprintf(logs, "Who knows, what's happening right now in %d?)\n", line);
    }

    fclose(logs);
}