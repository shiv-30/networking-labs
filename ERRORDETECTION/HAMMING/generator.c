#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
// Ignore the commented printf's they are for debugging during dev
// Reading Reference: https://www.geeksforgeeks.org/hamming-code-in-computer-network/
// Read above if you want to know about how Hamming is calculated
// Tried implementing the same...
// !THIS IS EVEN PARITY BASED

int main(int argc, char *argv[])
{
    char *inp;
    int *input;
    int *hamming;
    int *output;
    int i, j, k, r, il, pos, count;
    char c;
    inp = (char *)malloc(101 * sizeof(char));
    fgets(inp, 100, stdin);
    il = strlen(inp) - 1;
    inp[il] = '\0';
    r = 1;
    while (pow(2, r) < (il + r + 1))
    {
        // this is used to find the number of parity bits that we need to place
        // using the formula as seen in the link above.
        r++;
    }
    // DEBUG printf("r=%d", r);
    for (i = 0; i < il / 2; i++)
    {
        // Reversing the input so that we can get index 0 at the right side
        // Because binary indices are like [...3,2,1,0] for [...8,4,2,1], so, the "0"th index is on right
        // But on string, the 0th index is on left
        // Did this because I used the string index to do the calculations below
        c = inp[i];
        inp[i] = inp[il - i - 1];
        inp[il - i - 1] = c;
    }
    output = (int *)malloc((r + il) * sizeof(int));
    for (i = 0; i < r; i++)
    {
        // Marking the places where the parity bits will be placed.
        output[(int)(pow(2, i) - 1)] = -1;
    }
    //DEBUG printf("\nMID STAGE\n");
    // for (i = (r + il - 1); i >= 0; i--)
    //     printf("output[%d]=%d\n", i, output[i]);
    // printf("\n");
    for (i = 0, j = 0; i < (r + il); i++)
    {
        // Putting the input string in the output place
        // We calculate the parities in a later stage
        if (output[i] != -1)
        {
            output[i] = inp[j] - 48;
            j++;
        }
    }
    /* DEBUG
    printf("\nMID STAGE 2\n");
    for (i = (r + il - 1); i >= 0; i--)
        // printf("output[%d]=%d\n", i, output[i]);
        printf("%d", output[i]);
    printf("\n");
    */
    for (i = 0; i < r; i++)
    {
        // Getting the parities and putting them in that place.
        pos = (int)pow(2, i);

        if (pos < (il + r))
        {
            count = 0;

            for (j = pos; j <= il + r; j = pos + k)
            {
                // DEBUG printf("j=%d\n", j);
                for (k = j; k < pos + j; k++)
                {
                    if (k <= r + il)
                        if (output[(k - 1)] == 0 || output[(k - 1)] == 1)
                            count += output[(k - 1)];
                }
            }

            output[(pos - 1)] = count % 2; // EVEN Logic
            // DEBUG printf("Count = %d\nCount mod 2= %d\nPutting %d at Pos: %d\n", count, count % 2, count % 2, pos);
        }
    }
    // Printing the generated message with the hamming code
    printf("\n");
    for (i = (r + il - 1); i >= 0; i--)
        printf("%d", output[i]);
    printf("\n");
}
