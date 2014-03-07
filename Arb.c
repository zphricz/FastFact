#include "Arb.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void init(Arb* a, int assign)
{
    a->num = malloc(1*sizeof(unsigned int));
    a->size = 1;
    *(a->num) = assign;
}

void multiply(Arb* a, int mult)
{
   int i;
   int size = a->size;
   unsigned int* num = a->num;
   u64 buffer;
   unsigned int* result = malloc((size+1)*sizeof(unsigned int));
   result[0] = 0;
   for (i = 0; i < size; ++i)
   {
       buffer = (u64) num[i] * (u64) mult + (u64) result[i];
       result[i] = buffer;
       result[i+1] = buffer >> 32;
   }
   if (result[size] != 0)
       size++;
   free(a->num);
   a->num = result;
   a->size = size;
}

void print_dec_dibble_dabble(Arb* a)
{
    int size = a->size;
    unsigned int* num = a->num;
    char* str = malloc(size * 32 * sizeof(char));
    int curr = size * 32 - 2;
    int i;
    int j;
    int end = 0;
    memset(str, 0, size * 32);
    int num_shifts = (size-1) * 32;
    j = 31;
    while (num[size - 1] & 1 << j == 0)
        j--;
    num_shifts += j + 1;
    
    for (i = 0; i < num_shifts; ++i)
    {

        // perform dabbles
        for (j = curr; j < size * 32 - 1; ++j)
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
        for (j = begin; j < size * 32 - 1; ++j)
        {
            str[j] <<= 1;
            if (str[j] >= 16)
            {
                str[j] -= 16;
                str[j-1] += 1;
            }
        }
      
        // Shift over everything in Arb
        str[size * 32 - 2] += (num[size - 1] & 0x80000000) >> 31;
        num[size - 1] <<= 1;
        for (j = size - 2; j >= end; --j)
        {
            num[j+1] += (num[j] & 0x80000000) >> 31;
            num[j] <<= 1;
        }
        while (num[end] == 0)
        {
            end++;
        }
    }
    for (i = curr; i < size * 32 - 1; ++i)
    {
        str[i] += '0';
    }
    printf("%s\n", str + curr);
    free(str);
}

void print_dec_arb_bcd(Arb* a)
{
    int size = a->size;
    unsigned int* num = a->num;
    char *str = malloc(size * 32 * sizeof(char)); // Eh, just allocate an array that I know will be big enough
    char *buf = malloc(size * 32 * sizeof(char));
    int i;
    int j;
    int k;
    int lim = size * 32 - 2;
    int lowest = lim;
    memset(str, '0', size*32*sizeof(char));
    memset(buf, 0, size*32*sizeof(char));
    buf[lim] = 1;
    str[lim + 1] = 0;
    for (i = 0; i < size; ++i)
    {
        for (j = 0; j < 32; ++j)
        {
            if ((num[i] >> j) & 0x00000001)
            {
                for (k = lim; k >= lowest; k--)
                {
                    str[k] += buf[k];
                    if (str[k] > '9')
                    {
                        str[k-1] += 1;
                        str[k] -= 10;
                    }
                }
            }
            for (k = lim; k >= lowest; k--)
            {
                buf[k] *= 2;
            }
            for (k = lim; k >= lowest; k--)
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
    k = 0;
    while (str[k] == '0')
        k++;
    printf("%s\n", str + k);
    free(buf);
    free(str);
}

void print_bin(Arb* a)
{
    int size = a->size;
    unsigned int* num = a->num;
    int i;
    int j;
    char c;
    bool print = false;
    for(i = size-1; i >= 0; i--)
    {
        for(j = 31; j >= 0; j--)
        {
            c = '0' + ((num[i] >> j) & 0x00000001);
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
