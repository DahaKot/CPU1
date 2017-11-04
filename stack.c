//
// Created by dasch on 22.10.2017.
//
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <assert.h>
#include "stack.h"
#include "Constants.h"

double Hashing (const struct K_Stack *stack) {
    double result = stack->len*2 - Ada;
    int i = 0;
    for ( ; i < stack->len + one; i++) {
        result += (double) (stack->data[i]*2 - Alice*Alice);
    }

    return result;
}

int Stack_Ok (const struct K_Stack *stack) {
    if (stack != NULL && stack->canary_1 == Ada && stack->canary_2 == Alice &&
        stack->data != NULL && stack->len >= 0 && stack->len % 1 == 0   &&
        stack->data[0] == sense_of_life && stack->hash == Hashing(stack)) {
        return ALL_RIGHT;
    }
    else {
        return ERR;
    }
}

void Stack_Dump (const struct K_Stack *stack, int line) {
    printf("Stack on %p has a problem in %d line\n", stack, line);
    if (stack == NULL) {
        printf(" //NULL pointer?)\n");
        STACK_DEBUG Stack_Log_write(BAD_PTR, __LINE__);
        return ;
    }

    printf("Number of elements: %d\n", stack->len);
    if (stack->len < 0 || stack->len % 1 != 0) {
        printf(" //Weird length!\n");
        STACK_DEBUG Stack_Log_write(INVALID_LEN, __LINE__);
        return ;
    }

    printf("Data is on: %p\n", stack->data);
    if (stack->data == NULL) {
        printf(" //NULL pointer?)\n");
        STACK_DEBUG Stack_Log_write(BAD_PTR, __LINE__);
        return ;
    }
    printf("Main numbers: %lg, %lg, %lg\n", stack->canary_1, stack->canary_2, stack->data[0]);
    if (stack->canary_1 != Ada || stack->canary_2 != Alice || stack->data[0] != sense_of_life) {
        printf(" //Hm... seems smth is wrong here\n");
        STACK_DEBUG Stack_Log_write(ERR, __LINE__);
        return ;
    }

    printf("Size of data's array: %d\n", stack->current_size);
    printf("Elements:\n");
    int i = 0;
    while (i <= stack->len) {
        printf("%d. %lg\n", i, stack->data[i]);
        i++;
    }
    printf("===================================================================\n");
}

struct K_Stack *Stack_Construct () {
    STACK_DEBUG Stack_Log_write(CREATING_A_STACK, __LINE__);

    struct K_Stack *new_one = calloc(one, sizeof(struct K_Stack));
    assert(new_one != NULL);

    (new_one)->len = 0;
    (new_one)->data = calloc(LEN, sizeof(data_t));
    assert(new_one->data != NULL);

    (new_one)->data[0] = sense_of_life;                    //use data[0] element as a canary
    (new_one)->canary_1 = Ada;                             //initializing canaries
    (new_one)->canary_2 = Alice;
    (new_one)->current_size = LEN;

    double Hash = Hashing((new_one));

    (new_one)->hash = Hash;

    STACK_DEBUG Stack_Log_write(STACK_CREATED, __LINE__);
    return new_one;
}

void Stack_Destruct (struct K_Stack **old_one) {
    STACK_DEBUG Stack_Log_write(KILLING_STACK, __LINE__);

    if (*old_one != NULL) {
        free((*old_one)->data);
    }
    free(*old_one);
    *old_one = NULL;

    STACK_DEBUG Stack_Log_write(STACK_KILLED, __LINE__);
}

int Stack_Resize (struct K_Stack **stack, size_t Len) {
    STACK_DEBUG Stack_Log_write(RESIZING_STACK, __LINE__);

    if (Stack_Ok(*stack) != ALL_RIGHT) {
        Stack_Dump(*stack, __LINE__);
        return ERR;
    }

    data_t *new_data = NULL;
    if (Len >= (*stack)->current_size - one) {
        new_data = calloc((*stack)->current_size * 2, sizeof(data_t));
        assert(new_data != NULL);

        (*stack)->current_size *= 2;
    }
    else {
        new_data = calloc((*stack)->current_size, sizeof(data_t));
        assert(new_data != NULL);
    }

    int i = 0;
    while (i < (*stack)->len + one) {
        new_data[i] = (*stack)->data[i];
        i++;
    }
    (*stack)->data = new_data;
    (*stack)->len = Len;
    (*stack)->hash = Hashing(*stack);

    if (Stack_Ok(*stack) != ALL_RIGHT) {
        Stack_Dump(*stack, __LINE__);
        return ERR;
    }

    STACK_DEBUG Stack_Log_write(STACK_RESIZED, __LINE__);
    return ALL_RIGHT;
}

int Stack_Push (struct K_Stack **stack, data_t value) {
    STACK_DEBUG Stack_Log_write(PUSHING_STACK, __LINE__);

    if (Stack_Ok(*stack) != ALL_RIGHT) {
        Stack_Dump(*stack, __LINE__);
        return ERR;
    }

    if (Stack_Resize(stack, (*stack)->len + one) != ALL_RIGHT) {
        return ERR;
    }
    (*stack)->data[(*stack)->len] = value;                              //the last element = value
    (*stack)->hash = Hashing(*stack);

    if (Stack_Ok(*stack) != ALL_RIGHT) {
        Stack_Dump(*stack, __LINE__);
        return ERR;
    }

    STACK_DEBUG Stack_Log_write(STACK_PUSHED, __LINE__);
    return ALL_RIGHT;
}

data_t Stack_Pop (struct K_Stack **stack) {
    STACK_DEBUG Stack_Log_write(POPING_STACK, __LINE__);

    if (Stack_Ok(*stack) != ALL_RIGHT) {
        Stack_Dump(*stack, __LINE__);
        return ERR;
    }

    if ((*stack)->len == 0) {
        STACK_DEBUG Stack_Log_write(EMPTY, __LINE__);
        Stack_Dump(*stack, __LINE__);
        return (data_t) EMPTY;
    }

    data_t last_elem = (*stack)->data[(*stack)->len];                       //take the last element before we
    if (Stack_Resize(stack, (*stack)->len - one) != ALL_RIGHT) {
        return ERR;
    }
    (*stack)->hash = Hashing(*stack);

    if (Stack_Ok(*stack) != ALL_RIGHT) {
        Stack_Dump(*stack, __LINE__);
        return ERR;
    }

    STACK_DEBUG Stack_Log_write(STACK_POPED, __LINE__);
    return last_elem;
}

data_t Stack_Peek(struct K_Stack *stack) {
    STACK_DEBUG Stack_Log_write(PEEKING_STACK, __LINE__);
    if (Stack_Ok(stack) != ALL_RIGHT) {
        Stack_Dump(stack, __LINE__);
        return ERR;
    }

    if ((stack)->len == 0) {
        STACK_DEBUG Stack_Log_write(EMPTY, __LINE__);
        return EMPTY;
    }

    return (stack->data[stack->len]);
}

void Stack_Log_write (int err_code, int line) {
    FILE *logs;
    logs = fopen("Stack Log.txt", "a+");

    static int start = 0;
    if (start == 0) {
        time_t current_time;
        time(&current_time);

        fprintf(logs, "==========================================================\n");
        fprintf(logs, "Program started: %s", ctime(&current_time));
        start++;
    }

    switch(err_code) {
        case (CREATING_A_STACK):
            fprintf(logs, "Creating a stack in %d line\n", line);
            break;
        case (NOT_ENOUGH_MEMORY):
            fprintf(logs, "Can't alloc memory in %d line :C\n", line);
            break;
        case (STACK_CREATED):
            fprintf(logs, "New stack is created in %d line\n", line);
            break;
        case (STACK_KILLED):
            fprintf(logs, "You've killed him in %d line! He had two pretty children! T_T\n", line);
            break;
        case (STACK_POPED):
            fprintf(logs, "Stack is poped in %d line\n", line);
            break;
        case (STACK_PUSHED):
            fprintf(logs, "Stack is pushed in %d line\n", line);
            break;
        case (EMPTY):
            fprintf(logs, "Stack in %d line is empty like your mind, dude\n", line);
            break;
        case (ERR):
            fprintf(logs, "Canaries are dead in %d line\n", line);
            break;
        case (KILLING_STACK):
            fprintf(logs, "Killer is called in %d line\n", line);
            break;
        case (STACK_RESIZED):
            fprintf(logs, "Stack had been resized in %d line\n", line);
            break;
        case (PUSHING_STACK):
            fprintf(logs, "Pushing in stack in %d line\n", line);
            break;
        case (POPING_STACK):
            fprintf(logs, "Poping stack in %d line\n", line);
            break;
        case (PEEKING_STACK):
            fprintf(logs, "Taking last element in %d line\n", line);
            break;
        case (BAD_PTR):
            fprintf(logs, "You use invalid pointer in %d line\n", line);
            break;
        case (INVALID_LEN):
            fprintf(logs, "Pi-len in %d line\n", line);
            break;
        default: fprintf(logs, "Who knows, what's happening in %d line right now?)\n", line);
    }

    fclose(logs);
}