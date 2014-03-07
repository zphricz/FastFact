#ifndef ARB_H
#define ARB_H

/* long long for 32-bit computer support */
typedef unsigned long long u64;

/* Buffer that holds the arbitrary number's value is comprised of 32-bit numbers*/
typedef struct
{
    unsigned int* num;
    unsigned int size;
} Arb;

/* Initialize Arb to hold value of assign */
void init(Arb* a, unsigned int assign);

/* Multiply Arb by factor mult */
void multiply(Arb* a, unsigned int factor);

/* Buggy and shitty */
void print_dec_dibble_dabble(Arb* a);

/* Not buggy, just shitty */
void print_dec_arb_bcd(Arb* a);

/* Print out Arb in binary */
void print_bin(Arb* a);

/* Deallocate buffer in Arb */
void kill(Arb* a);

#endif
