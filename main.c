#include "Arb.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    int i;
    Arb num;
    int limit; 
    if (argc != 2)
    {
        printf("Please input a number\n");
        return 1;
    }
    limit = atoi(argv[1]);
    if (limit < 0)
    {
        printf("Please input a non-negative number\n");
        return 1;
    }
    init(&num, 1);
    for (i = 2; i <= limit; ++i)
    {
        multiply(&num, i);
    }
    print_bin(&num);
    kill(&num);
    return 0;
}
