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
    puts("");
    rem = (char *)malloc(polylen * sizeof(char));
    div = (char *)malloc(binarylen * sizeof(char));
    for (i = binarylen; i < (binarylen + polylen - 1); i++)
        binary[i] = '0';
    binary[i] = '\0';
    binarylen = strlen(binary);
    strcpy(div, binary);

    for (i = 0; i <= (binarylen - polylen); i++)
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
    for (i = 1; i < polylen; i++)
    {
        binary[binarylen - polylen + i] = rem[i];
    }
    puts(binary);
    free(rem);
    free(div);
    free(poly);
    free(binary);
    return 0;
}