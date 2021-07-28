#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// ! THIS IS RECEIVER END
int main(int argc, char *argv[])
{
    /*
        USER INPUT:
        argv: 1=even, 2=odd
    */
    if (argc < 2)
    {
        printf("ERROR \nformat: %s <1 for even, 2 for odd>", argv[0]);
        return 1;
    }
    char *inp;
    int counter = 0;
    inp = (char *)malloc(100 * sizeof(char));
    fgets(inp, 100, stdin);
    int point = 0;
    while (inp[point] != '\n')
    {
        if (inp[point] == '1')
            counter++;
        point++;
    }
    if (counter % 2 == 0)
    { // even 1s
        if (strcmp(argv[1], "1") == 0)
        {
            printf("OK 200");
            return 0;
        }
        else
        {
            printf("NOT OK ___");
            return 1;
        }
    }
    else
    { // odd 1s
        if (strcmp(argv[1], "2") == 0)
        {
            printf("OK 200");
            return 0;
        }
        else
        {
            printf("NOT OK ___");
            return 1;
        }
    }
}