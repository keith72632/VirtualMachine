#ifndef _VM_H
#define _VM_H
typedef enum {
   PSH,
   ADD,
   POP,
   HLT
} InstructionSet;

typedef enum {
    A, B, C, D, E, F, PC, SP,
    NUM_OF_REGISTERS
}Registers;


#endif
