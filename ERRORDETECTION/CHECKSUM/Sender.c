#include <stdio.h>
#include <stdlib.h>
// SENDER ALTERNATIVE
int main(int argc, char *argv[])
{
    int framesNo, bits, i, j, k, carry, z;
    int **frames;
    int *sum;
    char *temp;
    int a, b, c, carrybit;
    scanf("%d", &framesNo);
    scanf("%d", &bits);
    frames = (int **)malloc(framesNo * sizeof(int *));
    sum = (int *)calloc(bits, sizeof(int));
    carrybit = 0;
    carry = 0;
    for (i = 0; i < framesNo; i++)
    {
        temp = (char *)malloc(bits * sizeof(char));
        fflush(stdin);
        frames[i] = (int *)malloc(bits * sizeof(int));
        fgets(temp, 100, stdin);
        temp[bits] = '\0';
        for (j = 0; j < bits; j++)
        {
            frames[i][j] = temp[j] - 48;
        }
        for (j = bits - 1; j >= 0; j--)
        {
            if (frames[i][j] == 0 && sum[j] == 0 && carry == 0)
            {
                sum[j] = 0;
                carry = 0;
            }
            else if (frames[i][j] == 0 && sum[j] == 0 && carry == 1)
            {
                sum[j] = 1;
                carry = 0;
            }
            else if (frames[i][j] == 0 && sum[j] == 1 && carry == 0)
            {
                sum[j] = 1;
                carry = 0;
            }
            else if (frames[i][j] == 0 && sum[j] == 1 && carry == 1)
            {
                sum[j] = 0;
                carry = 1;
            }
            else if (frames[i][j] == 1 && sum[j] == 0 && carry == 0)
            {
                sum[j] = 1;
                carry = 0;
            }
            else if (frames[i][j] == 1 && sum[j] == 0 && carry == 1)
            {
                sum[j] = 0;
                carry = 1;
            }
            else if (frames[i][j] == 1 && sum[j] == 1 && carry == 0)
            {
                sum[j] = 0;
                carry = 1;
            }
            else if (frames[i][j] == 1 && sum[j] == 1 && carry == 1)
            {
                sum[j] = 1;
                carry = 1;
            }
            else
                break;
        }
        free(temp);
    }
    while (carry != 0)
    {
        for (j = bits - 1; j >= 0; j--)
        {
            if (sum[j] == 0 && carry == 0)
            {
                sum[j] = 0;
                carry = 0;
            }
            else if (sum[j] == 0 && carry == 1)
            {
                sum[j] = 1;
                carry = 0;
            }
            else if (sum[j] == 1 && carry == 0)
            {
                sum[j] = 1;
                carry = 0;
            }
            else if (sum[j] == 1 && carry == 1)
            {
                sum[j] = 0;
                carry = 1;
            }
            else
                break;
        }
    }
    for (i = 0; i < bits; i++)
        sum[i] = sum[i] == 1 ? 0 : 1;
    printf("Checksum:");
    for (i = 0; i < bits; i++)
        printf("%d", sum[i]);
    return 0;
}