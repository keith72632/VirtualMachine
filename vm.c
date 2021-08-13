#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "vm.h"


#define STACK_SIZE 256
#define FILE_SIZE 256
#define FILE_NAME "test.txt"

char file_size = 0;

bool running = true;
int ip = 0;
int sp = -1;

int stack[STACK_SIZE];
int registers[NUM_OF_REGISTERS];

//test program without parsing file
/*
const char program[] = {
    PSH, 5,
    PSH, 6,
    ADD,
    POP,
    HLT
};
*/

/*Prototypes*/
int fetch(int *program);
void eval(int instr, int *);
void print_stack(int stack[]);
char *file_parse(char *file_name);
int swap_for_int(char *instr);
int *construct_program(char **prog);


int main(int argc, char **argv) 
{
    char *file_name = malloc(sizeof(char) * FILE_SIZE);
    if(argc > 1)
    {
        memcpy(file_name, argv[1], FILE_SIZE);
        printf("File name: %s\n", file_name);
        
        //Doesn't actually use this file. Just for tests
        FILE *fp = NULL;
        fp = fopen(file_name, "r");

        if(fp == NULL)printf("can't open file");

        fclose(fp);
    }



    //convert file to array of strings
    char *fpp = file_parse(FILE_NAME);
    puts(fpp);
    size_t len = strlen(fpp);
//    char temp[7][4];
    bool status = true;
    int k = 0, row = 8, col = 4;
    char **matrix = (char **)malloc(row * sizeof(char*));

    for(size_t i = 0; i < row; i++)
    {
        matrix[i] = (char *)malloc(col * sizeof(char));
        for(size_t j = 0; j < col; j++)
        {
            printf("J before count %ld\n", j);
            //TODO move the if digit inside of else if fpp[k] != ' ' branch
            if(fpp[k] != ' ' && fpp[k] != '\n')
            {
                if(isdigit(fpp[k]))
                {
                    matrix[i][j] = fpp[k];
                    printf("fpp[%d] = %c\n", k, fpp[k]);
                    printf("matrix[%ld][%ld] = %c\n", i, j, matrix[i][j]);
                    k++; 
                }
                else
                {
                    matrix[i][j] = fpp[k];
                    printf("fpp[%d] = %c\n", k, fpp[k]);
                    printf("matrix[%ld][%ld] = %c\n", i, j, matrix[i][j]);
                    k++;
                }
            }
            else
            {
                k++;
            }
        }
        strncpy(matrix[i], matrix[i], 3);
        printf("matrix[%ld] = %s\n", i, matrix[i]);
    }

    
    //just a visual of array of strings
    for(size_t i = 0; i < 7; i++)
    {
        printf("Instruction %ld = %s with enum: %d\n", i, matrix[i], swap_for_int(matrix[i]));
    }


    //converts array of strings to array of ints, which can be be run
    int *prog = malloc(file_size * sizeof(int));

    for(size_t i = 0; i < 7; i++)
    {
        prog[i] = swap_for_int(matrix[i]);
    }
    
    //visual for array on program ints
    for(size_t i = 0; i < 6; i++)
    {
        printf("Actual program instruction i: %d\n", prog[i]);
    }

    //program runs
    while (running) {
        eval(fetch(prog), prog);
        ip++; // increment the ip every iteration
    }
    printf("done\n");

}

int fetch(int *prog) 
{
    return prog[ip];
}


void eval(int instr, int *prog) 
{
    switch (instr) {
        case HLT: {
            running = false;
            printf("done\n");
//            print_stack(stack);
            break;
        }
        case PSH: {
    	    sp++;
	        stack[sp] = prog[++ip];
//            print_stack(stack);
	        break;
        }
        case POP: {
	        int val_popped = stack[sp--];
	        printf("popped %d\n", val_popped);
            stack[0] = stack[1];
            stack[1] = 0;
//            print_stack(stack);
	        break;
	    }
	    case ADD: {
            //shitty comments are shitty
	        int value1 = stack[sp--];
	        int value2 = stack[sp--];

	        // we then add the result and push it to the stack
	        int result = value1 + value2;
	        sp++; // increment stack pointer **before**
	        stack[sp] = result; // set the value to the top of the stack
            
            //This removes the second number added from the stack 
            for(size_t i = 1; i < SP; i++)
            {
                stack[i] = stack[i + 1];
            }
//            print_stack(stack);
	        // all done!
	        break;
	    }
    }
}

void print_stack(int stack[])
{
    for(int i = 0; i < SP; i++)
    {
        printf("%d: 0x%04d\n", (i + 1), stack[i]);
    }
    if(SP != 0) printf("\n");
}

char *file_parse(char *file_name)
{
    FILE *fp = NULL;
    char junk;
    int i = 0;
    char *return_array = NULL;
    
    fp = fopen(file_name, "r");

    while((junk = fgetc(fp))!=EOF && junk){
        file_size++;
        return_array = realloc(return_array, (sizeof(char) * file_size));        
        return_array[i] = junk;
        i++;
    }


    fclose(fp);

    return return_array;
    
}

int swap_for_int(char *instr)
{
    if(strncmp(instr, "PSH", 3) == 0)
    {
        return PSH;
    }
    else if(strncmp(instr, "ADD", 3) == 0)
    {
        return ADD;
    }
    else if(strncmp(instr, "POP", 3) == 0)
    {
        return POP;
    }
    else if(strncmp(instr, "HLT", 3) == 0)
    {
        return HLT;
    }
    else if(isdigit(instr[0]))
    {
        int x = atoi(instr);
        return x;
    }
    else
    {
        return -1;
    }
}

int *construct_program(char **prog)
{
    int *program = malloc(file_size * sizeof(int));

    for(size_t i = 0; i < 7; i++)
    {
        program[i] = swap_for_int(prog[i]);
    }
    return program;
}
