#include "Arb.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    Arb a;
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

    /* Perform factorial */
    init(&a, 1);
    for (unsigned int i = 2; i <= (unsigned int) limit; ++i)
    {
        multiply(&a, i);
    }

    print_bin(&a);
    kill(&a);

    return 0;
}
