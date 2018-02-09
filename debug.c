#include <stdio.h>
#include <stdlib.h>

#include "blocks.h"
#include "debug.h"

/*------------------------------------
  Debug functions - Remove when final
------------------------------------*/

void debug_message(char str[100])
{
    printf("%s",str);
    char c = getchar();
    c=getchar();
    c++; // Stop -wall from complaining
}

void debug_draw_screen(int board[14][14])
{
    int i,j;
    system("clear");
    
    printf("   |");
    for (i=1;i<0xF;i++)
        printf(" %x |", i);
    printf("\n");
    
    for (i=0;i<0xE;i++)
    {
        for (j=0;j<60;j++)
            printf("-");
        printf("\n");

        printf(" %x ", i+1);
        for (j=0;j<0xE;j++)
            if (board[i][j] == 1)
                printf("| "cr_red"\u2588"cr_reset" ");
            else if (board[i][j] == 2)
                printf("| "cr_green"\u2588"cr_reset" ");
            else if (i == j && (i+1 == 5 || i+1 == 0xA) && board[i][j] == 0)
                printf("| S ");
            else
                printf("|   ");
                
        printf("|\n");
        
        if (i == 0xD)
        {
            for (j=0;j<60;j++)
                printf("-");
            printf("\n\n");
        }
    }
}