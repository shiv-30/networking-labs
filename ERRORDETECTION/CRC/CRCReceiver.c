//@param BinaryInput - Input Stream
//@param Polynomial - Generator polynomial

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char *binary;
    char *poly;
    char *rem;
    char *div;
    int binarylen, polylen, i, j;
    binary = (char *)malloc(100 * sizeof(char));
    poly = (char *)malloc(100 * sizeof(char));
    fgets(binary, 100, stdin);
    fgets(poly, 100, stdin);
    binarylen = strlen(binary) - 1;
    polylen = strlen(poly) - 1;
    binarylen = binarylen - (polylen - 1);
    puts("");
    rem = (char *)malloc(polylen * sizeof(char));
    div = (char *)malloc(binarylen * sizeof(char));
    strcpy(div, binary);

    for (i = 0; i <= (binarylen); i++)
    {
        if (div[i] != '0')
        {
            for (j = 0; j < polylen; j++)
            {
                if (div[i + j] == poly[j])
                    rem[j] = '0';
                else
                    rem[j] = '1';
            }
            for (j = 0; j < polylen; j++)
                div[i + j] = rem[j];
        }
        // puts(rem);
    }
    for (i = 0; i < polylen; i++)
    {
        if (rem[i] == '1')
        {
            printf("CRC Check Failed\n");
            return 1;
        }
    }
    printf("CRC Check Passed\n");
    // free(rem);
    // free(div);
    // free(poly);
    // free(binary);
    return 0;
}