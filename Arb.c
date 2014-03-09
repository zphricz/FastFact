#include "Arb.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

void init(Arb* a, unsigned int assign)
{
    a->num = malloc(sizeof(unsigned int));
    a->size = 1;
    a->num[0] = assign;
}

void multiply(Arb* a, unsigned int factor)
{
    u64 buffer_64 = 0;

    /* Reallocates a new buffer for arbitary values with every call - can be
     * easily improved, but I'm lazy :/ */
    unsigned int* result = malloc((a->size+1)*sizeof(unsigned int));

    /* Loop over every 32-bit element of a->num and multiply by factor, storing
     * the 64-bit result in buffer_64. Transfer from buffer_64 to result array */
    for (int i = 0; i < a->size; ++i)
    {
        buffer_64 += (u64) a->num[i] * (u64) factor;
        result[i] = buffer_64; /* Grabs the rightmost 32 bits of buffer_64 */
        buffer_64 >>= 32;
    }
    result[a->size] = buffer_64;

    /* If buffer_64 is non-zero at this point, it means that the result of
     * multiplication has created a number that needs a larger buffer size than
     * Arb a previously had. */
    if (buffer_64 != 0)
        a->size++;

    free(a->num);
    a->num = result;
}

void print_dec_dibble_dabble(Arb* a)
{
    char* str = malloc(a->size * 32 * sizeof(char));
    int curr = a->size * 32 - 2;
    int end = 0;
    memset(str, 0, a->size * 32);
    int num_shifts = (a->size-1) * 32;
    int j = 31;
    while (a->num[a->size - 1] & 1 << j == 0)
        j--;
    num_shifts += j + 1;

    for (int i = 0; i < num_shifts; ++i)
    {

        // perform dabbles
        for (int j = curr; j < a->size * 32 - 1; ++j)
        {
            if (str[j] >= 5)
            {
                str[j] += 3;
            }
        }

        // Shift over everything in BCD
        int begin = curr + 1;
        str[curr] <<= 1;
        if (str[curr] >= 16)
        {
            str[curr] -= 16;
            curr--;
            str[curr] = 1;
        }
        for (int j = begin; j < a->size * 32 - 1; ++j)
        {
            str[j] <<= 1;
            if (str[j] >= 16)
            {
                str[j] -= 16;
                str[j-1] += 1;
            }
        }

        // Shift over everything in Arb
        str[a->size * 32 - 2] += (a->num[a->size - 1] & 0x80000000) >> 31;
        a->num[a->size - 1] <<= 1;
        for (int j = a->size - 2; j >= end; --j)
        {
            a->num[j+1] += (a->num[j] & 0x80000000) >> 31;
            a->num[j] <<= 1;
        }
        while (a->num[end] == 0)
        {
            end++;
        }
    }
    for (int i = curr; i < a->size * 32 - 1; ++i)
    {
        str[i] += '0';
    }
    printf("%s\n", str + curr);
    free(str);
}

void print_dec_arb_bcd(Arb* a)
{
    char *str = malloc(a->size * 32 * sizeof(char)); // Eh, just allocate an array that I know will be big enough
    char *buf = malloc(a->size * 32 * sizeof(char));
    int lim = a->size * 32 - 2;
    int lowest = lim;
    memset(str, '0', a->size * 32 * sizeof(char));
    memset(buf, 0, a->size * 32 * sizeof(char));
    buf[lim] = 1;
    str[lim + 1] = 0;
    for (int i = 0; i < a->size; ++i)
    {
        for (int j = 0; j < 32; ++j)
        {
            if ((a->num[i] >> j) & 0x00000001)
            {
                for (int k = lim; k >= lowest; k--)
                {
                    str[k] += buf[k];
                    if (str[k] > '9')
                    {
                        str[k-1] += 1;
                        str[k] -= 10;
                    }
                }
            }
            for (int k = lim; k >= lowest; k--)
            {
                buf[k] *= 2;
            }
            for (int k = lim; k >= lowest; k--)
            {
                if (buf[k] > 9)
                {
                    buf[k-1] += 1;
                    buf[k] -= 10;
                    if (k == lowest)
                    {
                        lowest--;
                        break;
                    }
                }
            }
        }
    }
    int k = 0;
    while (str[k] == '0')
        k++;
    printf("%s\n", str + k);
    free(buf);
    free(str);
}

void print_bin(Arb* a)
{
    /* Don't print until  first '1' is found */
    bool print = false;

    /* Loop over every bit of every 32-bit number in a->num, print bit */
    for(int i = a->size-1; i >= 0; i--)
    {
        for(int j = 31; j >= 0; j--)
        {
            char c = '0' + ((a->num[i] >> j) & 0x00000001);
            if (print)
            {
                putchar(c);
            }
            else if (c == '1')
            {
                print = true;
                putchar(c);
            }
        }
    }
    putchar('\n');
}


void kill(Arb* a)
{
    free(a->num);
}

