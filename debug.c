#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>

#include "blocks.h"
#include "debug.h"

/*------------------------------------
  Debug functions        FINAL = NO
------------------------------------*/

void debug_message(char str[100], int variable, int ischar, int wait)
{
    printf("%s",str);
    if (variable!=0)
    {
        if (ischar!=0)
            printf("%c ",variable);
        else
            printf("%d",variable);
    }
    if (wait == 1)
    {
        char c = getchar();
        c=getchar();
        c++; // Stop -wall from complaining
    }
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

void debug_enter()
{
    __fpurge(stdin);
    char c = getchar();
    c++;
}

void debug_yield(int num, int move_x, int move_y, char piece, int rot, int score, int corners_left)
{
    printf("%4i) %1x %1x %c %i is a valid move which will yield %d points and %d corners.\n", num, move_x, move_y, piece, rot, score, corners_left);
}

void debug_choice(int move_x, int move_y, char piece, int rot)
{
    printf("Playing %1x %1x %c %i .\n", move_x, move_y, piece, rot);
}