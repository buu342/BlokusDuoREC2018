#include <stdio.h>
#include "transform.h"
#include "debug.h"


/*------------------------------------
       Rotate/flip the array
------------------------------------*/

void transform_array(int piece[5][5], int rot)
{

    int temp[5][5];
    for (int k = rot; k/2 > 0; k-=2)
    {
        for (int i = 0; i < 5; ++i)
            for (int j = 0; j < 5; ++j)
                temp[i][j] = piece[5 - j - 1][i];

        for (int i = 0; i < 5; ++i)
            for (int j = 0; j < 5; ++j)
                piece[i][j] = temp[i][j];
    }

    if (rot%2 != 0)
    {
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++)
                temp[i][j] = piece[i][5 - j - 1];

        for (int i = 0; i < 5; ++i)
            for (int j = 0; j < 5; ++j)
                piece[i][j] = temp[i][j];
    }

}