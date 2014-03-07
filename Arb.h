#ifndef ARB_H
#define ARB_H

typedef unsigned long long u64;
typedef char bool;
enum {false = 0, true = 1};

typedef struct
{
    unsigned int* num;
    int size;
} Arb;

void init(Arb* a, int assign);

void multiply(Arb* a, int mult);

void print(Arb* a);

void print_bin(Arb* a);

void kill(Arb* a);

#endif
