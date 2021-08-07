#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
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

const char program[] = {
    PSH, 5,
    PSH, 6,
    ADD,
    POP,
    HLT
};

/*Prototypes*/
int fetch(void);
void eval(int instr);
void print_stack(int stack[]);
char *file_parse(char *file_name);


int main(int argc, char **argv) 
{
    char *file_name = malloc(sizeof(char) * FILE_SIZE);
    if(argc > 1)
    {
        memcpy(file_name, argv[1], FILE_SIZE);
        puts(file_name);
        
        FILE *fp = NULL;
        int s;
        fp = fopen(file_name, "r");

        if(fp == NULL)printf("can't open file");

        while((s = fgetc(fp)) != EOF) putchar(s);

        fclose(fp);
    }
    else
    {
        printf("Enter file name\n");
        exit(1);
    }


    while (running) {
        eval(fetch());
        ip++; // increment the ip every iteration
    }
    print_stack(stack);

    char *fpp = file_parse(file_name);
    size_t len = strlen(fpp);
    char temp[7][4];
    int j = 0, k = 0;

    for(size_t i = 0; i < len; i++)
    {
        if(fpp[i] != ' ' && fpp[i] != '\n')
        {
            temp[j][k] = fpp[i];
            putchar(temp[j][k]);
            printf("  j = %d. k = %d\n", j, k);
            k++;
        }
        else
        {
            j++;
            k = 0;
        }
    }
    puts(temp[0]);
}

int fetch() 
{
    return program[ip];
}


void eval(int instr) 
{
    switch (instr) {
        case HLT: {
            running = false;
            printf("done\n");
            print_stack(stack);
            break;
        }
        case PSH: {
    	    sp++;
	        stack[sp] = program[++ip];
            print_stack(stack);
	        break;
        }
        case POP: {
	        int val_popped = stack[sp--];
	        printf("popped %d\n", val_popped);
            stack[0] = stack[1];
            stack[1] = 0;
            print_stack(stack);
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
            print_stack(stack);
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
    char junk, ch, i = 0;
    char *return_array = NULL;
    
    fp = fopen(file_name, "r");

    while((junk = fgetc(fp))!=EOF && junk){
        file_size++;
        return_array = realloc(return_array, (sizeof(char) * file_size));        
        return_array[i] = junk;
        i++;
//            putchar(junk);
    }
    putchar('\n');

//    printf("File size = %d\n", file_size);

    fclose(fp);

    return return_array;
    
}
