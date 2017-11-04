//
// Created by dasch on 22.10.2017.
//

#ifndef ASSEMBLER_CONSTANTS_H
#define ASSEMBLER_CONSTANTS_H

#define POISON tan(M_PI/2)

typedef double data_t;
static const int one = 1;
static const int no_line = -1;
static const size_t LEN = 10;
static const data_t sense_of_life = 42;
static const data_t Ada = 5;
static const data_t Alice = 7;

static const size_t RAM_SIZE = 1024;                                //maximum size of array, RAM_SIZE/2 - max number of lines
static const size_t NUM_LABELS = 512;                               //number of labels is 100% less than RAM_SIZE/2
static const size_t COMMAND_LEN = 6;                                //max number of letters in a command
static const size_t LABEL_LEN = 10;                                 //max label len

enum ERR_AND_LOG_CODES {                                            //7 for errors and log
    ALL_RIGHT = 70,
    CREATING_A_STACK = 71,
    NOT_ENOUGH_MEMORY = 72,
    STACK_CREATED = 73,
    EMPTY = 70000004,
    ERR = 70000005,
    KILLING_STACK = 76,
    STACK_KILLED = 77,
    RESIZING_STACK = 78,
    STACK_RESIZED = 79,
    PUSHING_STACK = 710,
    STACK_PUSHED = 711,
    POPING_STACK = 712,
    STACK_POPED = 713,
    PEEKING_STACK = 714,
    BAD_PTR = 715,
    INVALID_LEN = 716,
    NO_FILE = 717,
    STOD = 718,
    START_READING = 719,
    INVALID_COMMAND = 720,
    WRONG_WORD = 721,
    STACK = 722,
    EOP = 700023,
    CREATING_CPU = 724,
    CPU_CREATED = 725,
    KILLING_CPU = 726,
    CPU_KILLED = 727,
    READ = 728,
    START_CPU = 729,
    CPU_STOP = 730,
    START_WRITING = 731
};

#endif //ASSEMBLER_CONSTANTS_H
