//
// Created by dasch on 04.11.2017.
//
#include "cpu.h"

data_t add (data_t a, data_t b)      { return b + a; }
data_t sub (data_t a, data_t b)      { return b - a; }
data_t mul (data_t a, data_t b)      { return b * a; }
data_t division (data_t a, data_t b) { return b / a; }
data_t mod (data_t a, data_t b)      { return (int) b % (int) a; }
data_t idiv (data_t a, data_t b)     { return (int) b / (int) a; }
int equal (data_t a, data_t b)       { return b == a; }
int not_equal (data_t a, data_t b)   { return b != a; }
int great (data_t a, data_t b)       { return b > a; }
int great_e (data_t a, data_t b)     { return b >= a; }
int less (data_t a, data_t b)        { return b < a; }
int less_e (data_t a, data_t b)      { return b <= a; }

struct CPU *CPU_Construct () {
    CPU_DEBUG CLog_write(CREATING_CPU, __LINE__);

    struct CPU *cpu = calloc(one, sizeof(struct CPU));
    assert(cpu != NULL);

    cpu->ax = POISON;
    cpu->bx = POISON;
    cpu->cx = POISON;
    cpu->dx = POISON;

    cpu->stack = Stack_Construct();
    cpu->Func_Stack = Stack_Construct();

    CPU_DEBUG CLog_write(CPU_CREATED, __LINE__);

    return cpu;
}

void CPU_Destruct (struct CPU **old_one) {
    CPU_DEBUG CLog_write(KILLING_CPU, __LINE__);

    if (*old_one != NULL) {
        Stack_Destruct(&(*old_one)->stack);
        Stack_Destruct(&(*old_one)->Func_Stack);
    }
    free(*old_one);
    *old_one = NULL;

    CPU_DEBUG CLog_write(CPU_KILLED, __LINE__);
}

data_t *File_Read(size_t *cmd_ind) {
    CPU_DEBUG CLog_write(START_READING, __LINE__);

    FILE *source;
    source = fopen("Code.txt", "r");
    if (source == NULL) {
        CPU_DEBUG CLog_write(NO_FILE, __LINE__);
        return (void *) NO_FILE;
    }

    data_t cmd = 0;
    char *command = calloc(COMMAND_LEN, sizeof(char));
    assert(command != NULL);

    fscanf(source, "%s", command);
    cmd = strtod(command, NULL);

    data_t *code_arr = calloc(RAM_SIZE, sizeof(data_t));
    assert(code_arr != NULL);

    *cmd_ind = 0;

    while (cmd != EOP) {
        code_arr[*cmd_ind] = cmd;

        fscanf(source, "%s", command);

        cmd = strtod(command, NULL);
        (*cmd_ind)++;
    }
    code_arr[*cmd_ind] = EOP;
    (*cmd_ind)++;

    fclose(source);

    CPU_DEBUG CLog_write(READ, __LINE__);

    return code_arr;
}

data_t Log (data_t x, data_t basis) {
    return 1;
}

int CPU_Run () {
    CPU_DEBUG CLog_write(START_CPU, __LINE__);

    size_t p_len = 0;
    data_t *code = File_Read(&p_len);
    if (code == (void *) NO_FILE) {
        CPU_DEBUG CLog_write(NO_FILE, __LINE__);
        return NO_FILE;
    }

    struct CPU *cpu = CPU_Construct();

    int c_cmd = 0;
    data_t check = 0;

    for ( ; code[c_cmd] != EOP; c_cmd++) {
        if (code[c_cmd] == PUSH_NUMBER) {
            CPU_DEBUG CLog_write(PUSH_NUMBER, __LINE__);

            check = Stack_Push(&(cpu->stack), code[++c_cmd]);

            if (check != ALL_RIGHT) {
                CPU_DEBUG CLog_write(STACK, __LINE__);
                return ERR;
            }
        }
        cmd_do(ADD, add)
        cmd_do(SUB, sub)
        cmd_do(MUL, mul)
        cmd_do(DIV, division)
        cmd_do(MOD, mod)
        cmd_do(IDIV, idiv)
        else if (code[c_cmd] == POP_REG) {
            CPU_DEBUG CLog_write(POP_REG, __LINE__);

            check = Stack_Pop(&(cpu->stack));
            if (check == ERR) {
                CPU_DEBUG CLog_write(STACK, __LINE__);
                return ERR;
            }
            c_cmd++;
            if (code[c_cmd] == AX) {
                cpu->ax = check;
            }
            else if (code[c_cmd] == BX) {
                cpu->bx = check;
            }
            else if (code[c_cmd] == CX) {
                cpu->cx = check;
            }
            else if (code[c_cmd] == DX) {
                cpu->dx = check;
            }
        }
        else if (code[c_cmd] == OUT) {
            CPU_DEBUG CLog_write(OUT, __LINE__);

            check = Stack_Pop(&(cpu->stack));
            if (check == ERR || check == EMPTY) {
                CPU_DEBUG CLog_write(STACK, __LINE__);
                return ERR;
            }
            printf("The last element is: %lg\n", check);
        }
        else if (code[c_cmd] == IN) {
            CPU_DEBUG CLog_write(IN, __LINE__);

            printf("Enter an element for the stack:\n");
            char *word = calloc(RAM_SIZE, sizeof(char));
            assert(word != NULL);

            scanf("%s", word);
            check = Stack_Push(&(cpu->stack), strtod(word, NULL));
            if (check != ALL_RIGHT) {
                CPU_DEBUG CLog_write(STACK, __LINE__);
                return ERR;
            }
        }
        else if (code[c_cmd] == PUSH_REG) {
            CPU_DEBUG CLog_write(PUSH_REG, __LINE__);

            ++c_cmd;
            if (code[c_cmd] == AX) {
                check = Stack_Push(&(cpu->stack), cpu->ax);
                if (check != ALL_RIGHT) {
                    CPU_DEBUG CLog_write(STACK, __LINE__);
                    return ERR;
                }
            }
            else if (code[c_cmd] == BX) {
                check = Stack_Push(&(cpu->stack), cpu->bx);
                if (check != ALL_RIGHT) {
                    CPU_DEBUG CLog_write(STACK, __LINE__);
                    return ERR;
                }
            }
            else if (code[c_cmd] == CX) {
                check = Stack_Push(&(cpu->stack), cpu->cx);
                if (check != ALL_RIGHT) {
                    CPU_DEBUG CLog_write(STACK, __LINE__);
                    return ERR;
                }
            }
            else if (code[c_cmd] == DX) {
                check = Stack_Push(&(cpu->stack), cpu->dx);
                if (check != ALL_RIGHT) {
                    CPU_DEBUG CLog_write(STACK, __LINE__);
                    return ERR;
                }
            }
        }
        else if (code[c_cmd] == SQRT) {
            CPU_DEBUG CLog_write(SQRT, __LINE__);

            check = Stack_Push(&(cpu->stack), sqrt(Stack_Pop(&(cpu->stack))));
            if (check != ALL_RIGHT) {
                CPU_DEBUG CLog_write(STACK, __LINE__);
                return ERR;
            }
        }
        else if (code[c_cmd] == END) {
            CPU_DEBUG CLog_write(END, __LINE__);
            break;
        }
        else if (code[c_cmd] == SIN) {
            CPU_DEBUG CLog_write(SIN, __LINE__);

            check = Stack_Pop(&(cpu->stack));
            if (check == ERR || check == EMPTY) {
                CPU_DEBUG CLog_write(STACK, __LINE__);
                return ERR;
            }
            check = Stack_Push(&(cpu->stack), sin(check));
            if (check != ALL_RIGHT) {
                CPU_DEBUG CLog_write(STACK, __LINE__);
                return ERR;
            }
        }
        else if (code[c_cmd] == COS) {
            CPU_DEBUG CLog_write(COS, __LINE__);

            check = Stack_Pop(&(cpu->stack));
            if (check == ERR || check == EMPTY) {
                CPU_DEBUG CLog_write(STACK, __LINE__);
                return ERR;
            }
            check = Stack_Push(&(cpu->stack), cos(check));
            if (check != ALL_RIGHT) {
                CPU_DEBUG CLog_write(STACK, __LINE__);
                return ERR;
            }
        }
        else if (code[c_cmd] == LOG) {
            CPU_DEBUG CLog_write(LOG, __LINE__);

            data_t basis = code[++c_cmd];
            check = Stack_Pop(&(cpu->stack));
            if (check == ERR || check == EMPTY) {
                CPU_DEBUG CLog_write(STACK, __LINE__);
                return ERR;
            }
            check = Stack_Push(&(cpu->stack), Log(check, basis));
            if (check != ALL_RIGHT) {
                CPU_DEBUG CLog_write(STACK, __LINE__);
                return ERR;
            }
        }
        else if (code[c_cmd] == POW) {
            CPU_DEBUG CLog_write(POW, __LINE__);

            check = Stack_Pop(&(cpu->stack));
            if (check == ERR || check == EMPTY) {
                CPU_DEBUG CLog_write(STACK, __LINE__);
                return ERR;
            }
            check = Stack_Push(&(cpu->stack), pow(check, code[++c_cmd]));
            if (check != ALL_RIGHT) {
                CPU_DEBUG CLog_write(STACK, __LINE__);
                return ERR;
            }
        }
        else if (code[c_cmd] == JMP) {
            CPU_DEBUG CLog_write(JMP, __LINE__);

            c_cmd = (int) code[c_cmd + 1];
            c_cmd--;
        }
        jump_do(JE, equal)
        jump_do(JNE, not_equal)
        jump_do(JA, great)
        jump_do(JAE, great_e)
        jump_do(JB, less)
        jump_do(JBE, less_e)
        else if (code[c_cmd] == CALL) {
            CPU_DEBUG CLog_write(CALL, __LINE__);
            c_cmd++;

            check = Stack_Push(&(cpu->Func_Stack), (data_t) (c_cmd + 1));

            if (check != ALL_RIGHT) {
                CPU_DEBUG CLog_write(STACK, __LINE__);
                return ERR;
            }
            c_cmd = (int) code[c_cmd];
            c_cmd--;
        }
        else if (code[c_cmd] == RET) {
            CPU_DEBUG CLog_write(RET, __LINE__);

            c_cmd = (int) Stack_Pop(&(cpu->Func_Stack));
            if (c_cmd == ERR || c_cmd == EMPTY) {
                CPU_DEBUG CLog_write(STACK, __LINE__);
                return ERR;
            }
            c_cmd--;
        }
        else if (code[c_cmd] == MEOW) {
            CPU_DEBUG CLog_write(RET, __LINE__);

            Draw_a_cat();
        }
        else {
            CPU_DEBUG CLog_write(INVALID_COMMAND, __LINE__);
            return INVALID_COMMAND;
        }
    }

    CPU_Destruct(&cpu);
    CPU_DEBUG CLog_write(CPU_STOP, __LINE__);

    return ALL_RIGHT;
}

void CLog_write (int err_code, size_t line) {
    FILE *logs;
    logs = fopen("CPU Log.txt", "a+");

    static int start = 0;
    if (start == 0) {
        time_t current_time;
        time(&current_time);

        fprintf(logs, "==========================================================\n");
        fprintf(logs, "Program started: %s", ctime(&current_time));
        start++;
    }

    switch(err_code) {
        case (CREATING_CPU):
            fprintf(logs, "Creating a cpu in %d line\n", line);
            break;
        case (NOT_ENOUGH_MEMORY):
            fprintf(logs, "Can't alloc memory in %d line :C\n", line);
            break;
        case (CPU_CREATED):
            fprintf(logs, "New cpu is created in %d line\n", line);
            break;
        case (CPU_KILLED):
            fprintf(logs, "You've killed him in %d line! He had two pretty children! T_T\n", line);
            break;
        case (STACK):
            fprintf(logs, "Stack's troubles in %d line\n", line);
            break;
        case (INVALID_COMMAND):
            fprintf(logs, "You put the wrong command in %d line\n", line);
            break;
        case (ERR):
            fprintf(logs, "Canaries are dead in %d line\n", line);
            break;
        case (KILLING_CPU):
            fprintf(logs, "Killer is called in %d line\n", line);
            break;
        case (NO_FILE):
            fprintf(logs, "Can not find file in %d line\n", line);
            break;
        case (START_READING):
            fprintf(logs, "Start reading from file in %d line\n", line);
            break;
        case (READ):
            fprintf(logs, "The file has been read in %d line\n", line);
            break;
        case (START_CPU):
            fprintf(logs, "CPU starts working in %d line\n", line);
            break;
        case (CPU_STOP):
            fprintf(logs, "CPU stopped in %d line\n", line);
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
        default: fprintf(logs, "Who knows, what's happening in %d line right now?)\n", line);
    }

    fclose(logs);
}

void Draw_a_cat () {
    printf("           .                .                    \n"
                   "            :\"-.          .-\";                    \n"
                   "            |:`.`.__..__.'.';|                    \n"
                   "            || :-\"      \"-; ||                    \n"
                   "            :;              :;                    \n"
                   "            /  .==.    .==.  \\                    \n"
                   "           :      _.--._      ;                   \n"
                   "           ; .--.' `--' `.--. :                   \n"
                   "          :   __;`      ':__   ;                  \n"
                   "          ;  '  '-._:;_.-'  '  :                  \n"
                   "          '.       `--'       .'                  \n"
                   "           .\"-._          _.-\".                   \n"
                   "         .'     \"\"------\"\"     `.                 \n"
                   "        /`-                    -'\\                \n"
                   "       /`-                      -'\\               \n"
                   "      :`-   .'              `.   -';              \n"
                   "      ;    /                  \\    :              \n"
                   "     :    :                    ;    ;             \n"
                   "     ;    ;                    :    :             \n"
                   "     ':_:.'                    '.;_;'             \n"
                   "        :_                      _;                \n"
                   "        ; \"-._                -\" :`-.     _.._    \n"
                   "        :_          ()          _;   \"--::__. `.  \n"
                   "         \\\"-                  -\"/`._           :  \n"
                   "        .-\"-.                 -\"-.  \"\"--..____.'  \n"
                   "       /         .__  __.         \\               \n"
                   "      : / ,       / \"\" \\       . \\ ; bug          \n"
                   "       \"-:___..--\"      \"--..___;-\"               \n"
                   "                                                 \n");
}