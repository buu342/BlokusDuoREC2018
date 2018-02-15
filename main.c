/*------------------------------------
               Libraries
------------------------------------*/

#include "blocks.h"
#include "transform.h"
#include "debug.h"
#include "check.h"
#include "str_ar.h"


/*------------------------------------
       Boot and game execution
------------------------------------*/

int main()
{
    // Setup Variables

    int board[14][14];          // The board itself
    //int move_x, move_y;         // X and Y
    //char piece;                 // The chosen piece
    int turn = 1;               // Turn number
    //int rot = 1;                // Rotation, between 0 and 7
    char pieces_left1[21];      // Which pieces does player 1 have?
    char pieces_left2[21];      // Which pieces does player 1 have?
    int score1 = 0;             // Player 1's score
    int score2 = 0;             // Player 2's score

    // Clean up the variables before starting

    for (int i=0;i<15;i++)
        for (int j=0;j<15;j++)
            board[i][j] = 0;

    // Populate the list of pieces left

    for (int i=0;i<21;i++)
    {
        pieces_left1[i] = 'a' + i;
        pieces_left2[i] = 'a' + i;
    }


    // Play the game

    while(1)
    {
        int player = ((turn-1)%2)+1;
        
        int possible[2000][5];      // List of possible moves and their score
        for (int i=0;i<2000;i++)
            for (int j=0;j<5;j++)
                possible[i][j] = 0;

        // Do some output and request input

        debug_draw_screen(board);

        debug_message("Turn = ", turn, 0, 0);
        debug_message("\n\n", 0, 0, 0);
        debug_message("Player 1's score = ", score1, 0, 0);
        debug_message("\n", 0, 0, 0);
        debug_message("Player 2's score = ", score2, 0, 0);
        debug_message("\n", 0, 0, 0);
        debug_message("\n", 0, 0, 0);

        debug_message("Possible moves1 = ", 0, 0, 0);
        for (int i=0;i<21;i++)
            debug_message("", pieces_left1[i], 1, 0);

        debug_message("\nPossible moves2 = ", 0, 0, 0);
        for (int i=0;i<21;i++)
            debug_message("", pieces_left2[i], 1, 0);

        if (turn == 1)
            debug_message("\n\nPlayer 1, your turn (you must start at 5,5): ",0,0, 0);
        else if (turn == 2)
            debug_message("\n\nPlayer 2, your turn (you must start at a,a): ",0,0, 0);
        else
        {
            debug_message("\n\n", 0, 0, 0);
            debug_message("Player ", player, 0, 0);
            debug_message(", your turn: ", 0, 0, 0);

        }

        debug_enter();

        //scanf(" %1x%1x%1c%1d", &move_x, &move_y, &piece, &rot);

        // Clean up dumb moves to save up on if checks.
        
        /*if (piece >= 'A' && piece <= 'U') piece = piece + 32;
        if (move_x < 1) move_x = 1;
        if (move_x > 0xE) move_x = 0xE;
        if (move_y < 1) move_y = 1;
        if (move_y > 0xE) move_y = 0xE;
        if (piece < 'a') piece = 'a';
        if (piece > 'u') piece = 'u';
        rot = rot%8;*/


        // Check all valid moves and store them in the possible array.

        int t=0, score=0, corners_left=0;
        for (int l='a';l<='u';l++)
        {
            if (strchr_ar(player == 1 ? pieces_left1 : pieces_left2, l) == 0) // check if move has been used up.
                continue;
            for (int j=1;j<=0xE;j++)
            {
                for (int i=1;i<=0xE;i++)
                {
                    if (board[j-1][i-1] == 0)
                    {
                        for (int k=0;k<8;k++)
                        {
                            int test = check_move(i, j, l, k, board, turn, &score);
                            if (test == MOVE_POSSIBLE)
                            {
                                check_corner(i, j, l, k, board, turn, &corners_left);
                                debug_yield(t, i, j, l, k, score, corners_left);
                                possible[t][0] = score + corners_left;
                                possible[t][1] = i;
                                possible[t][2] = j;
                                possible[t][3] = l;
                                possible[t][4] = k;
                                score = corners_left = 0;
                                t++;
                            }
                        }
                    }
                }
            }
        }

        if (possible[0][0] == 0)
        {
            turn++;
            continue;
        }

        // Find the best move

        int best[2] = {0,0};
        for(int i=0;i<2000;i++)
            if (possible[i][0] >= best[1])
            {
                best[0] = i;
                best[1] = possible[i][0];
            }
            else if (possible[i][0] == 0)
                break;


        // Play that move

        t = best[0];
        debug_choice(possible[t][1], possible[t][2], possible[t][3], possible[t][4]);
        play_move(possible[t][1], possible[t][2], possible[t][3], possible[t][4], board, turn, (player == 1 ? pieces_left1 : pieces_left2), (player == 1 ? &score1 : &score2));

        for (int i=0;i<2000;i++)
            for (int j=0;j<5;j++)
                possible[i][j] = 0;
        
        turn++;
    }
}
