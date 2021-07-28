#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// ! THIS IS SENDER END
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
    char *op;
    int i, counter = 0;
    inp = (char *)malloc(100 * sizeof(char));
    fgets(inp, 100, stdin);
    int point = 0;
    int length = strlen(inp);
    op = (char *)malloc((length + 2) * sizeof(char));
    while (inp[point] != '\n')
    {
        op[point] = inp[point];
        if (inp[point] == '1')
            counter++;
        point++;
    }
    if (counter % 2 == 0)
    { // even 1s
        if (strcmp(argv[1], "2") == 0)
        {
            op[point++] = '1';
        }
        else
        {
            op[point++] = '0';
        }
    }
    else
    { // odd 1s
        if (strcmp(argv[1], "1") == 0)
        {
            op[point++] = '1';
        }
        else
        {
            op[point++] = '0';
        }
    }
    op[point] == '\0';
    puts(op);
}