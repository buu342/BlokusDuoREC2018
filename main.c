/*------------------------------------
         Standard C Libraries
------------------------------------*/

#include <stdio.h>
#include <stdio_ext.h>
#include <string.h>


/*------------------------------------
            Custom headers
------------------------------------*/

#include "blocks.h"
#include "transform.h"
#include "debug.h"


/*------------------------------------
   Move validity checker and player
------------------------------------*/

int play_move(int move_x, int move_y, char piece, int rot, int board[14][14], int turn, char pieces_left[22], int *score, int play)
{
    int player = ((turn-1)%2)+1;

    // Convert the piece's name to lowercase for consistency.

    if (piece >= 'A' && piece <= 'U')
        piece = piece + 32;


    if ((move_x >= 1 && move_x <= 0xE) && (move_y >= 1 && move_y <= 0xE) && (piece >= 'a' && piece <= 'u'))
    {
        // Put the block definition in our temporary array

        int temp[5][5];
        for (int i=0;i<5;i++)
            for(int j=0;j<5;j++)
                switch(piece)
                {
                    case 'a': temp[i][j] = block_a[i][j]; break;
                    case 'b': temp[i][j] = block_b[i][j]; break;
                    case 'c': temp[i][j] = block_c[i][j]; break;
                    case 'd': temp[i][j] = block_d[i][j]; break;
                    case 'e': temp[i][j] = block_e[i][j]; break;
                    case 'f': temp[i][j] = block_f[i][j]; break;
                    case 'g': temp[i][j] = block_g[i][j]; break;
                    case 'h': temp[i][j] = block_h[i][j]; break;
                    case 'i': temp[i][j] = block_i[i][j]; break;
                    case 'j': temp[i][j] = block_j[i][j]; break;
                    case 'k': temp[i][j] = block_k[i][j]; break;
                    case 'l': temp[i][j] = block_l[i][j]; break;
                    case 'm': temp[i][j] = block_m[i][j]; break;
                    case 'n': temp[i][j] = block_n[i][j]; break;
                    case 'o': temp[i][j] = block_o[i][j]; break;
                    case 'p': temp[i][j] = block_p[i][j]; break;
                    case 'q': temp[i][j] = block_q[i][j]; break;
                    case 'r': temp[i][j] = block_r[i][j]; break;
                    case 's': temp[i][j] = block_s[i][j]; break;
                    case 't': temp[i][j] = block_t[i][j]; break;
                    case 'u': temp[i][j] = block_u[i][j]; break;
                }


        // Apply transformations to the temporary array

        transform_array(temp, rot);


        // Check for if the move is possible

        int check_start=0;
        int check_corner=0;

        if (strchr(pieces_left, piece) == NULL) // Move has been used up.
            return MOVE_IMPOSSIBLE_USED;

        for (int i=0;i<5;i++)
            for(int j=0;j<5;j++)
            {
                
                if (temp[i][j] == 1) // Only care about checking the 1's in our temporary array.
                {
                    if ((((move_x-2+j)>0xE || (move_y-2+i)>0xE) || ((move_x-3+j)<0 || (move_y-3+i)<0))) // Out of bounds.
                        return MOVE_IMPOSSIBLE_OOFB;
                    else if (board[move_y-3+i][move_x-3+j] != 0) // Occupying other block.
                        return MOVE_IMPOSSIBLE_OCUP;

                    for (int k=-1;k<2;k+=2) // Connecting edges with same color. The for loop is to cut down on the amount of if's.
                    {
                        if ((move_y-3+i+k >= 0 && move_y-3+i+k <= 0xE) && board[move_y-3+i+k][move_x-3+j] == player)
                            return MOVE_IMPOSSIBLE_EDGE;
                        if ((move_x-3+j+k >= 0 && move_x-3+j+k <= 0xE) && board[move_y-3+i][move_x-3+j+k] == player)
                            return MOVE_IMPOSSIBLE_EDGE;
                    }

                    if ((turn == 1 || turn == 2) && check_start == 0 && (move_y-2+i == move_x-2+j)) // Starting in the correct position
                    {
                        if (move_x-2+j == (turn==1?5:0xA))
                            check_start = 1;
                    }
                    else if (turn > 2 && check_corner == 0 ) // Corner is connecting
                        for (int k=-1;k<2;k+=2)
                            if (board[move_y-3+i+k][move_x-3+j-1] == player || board[move_y-3+i+k][move_x-3+j+1] == player)
                                check_corner = 1;
                }

            }

        if (((turn == 1 || turn == 2) && check_start == 0))
            return MOVE_IMPOSSIBLE_FRST;
        if (turn > 2 && check_corner == 0)
            return MOVE_IMPOSSIBLE_CORN;


        // Play the move
        if (play == 1)
        {
            for (int i=0;i<5;i++)
                for(int j=0;j<5;j++)
                    if (temp[i][j] != 0)
                    {
                        board[move_y-3+i][move_x-3+j] = player;
                        (*score)++;
                    }


            // If all pieces have been used, award 15 points. If the last piece was A, award 20 instead

            if (turn == 41 || turn == 42)
            {
                if (piece == 'a')
                    (*score)+=20;
                else
                    (*score)+=15;
            }


            // Take away the move

            for (int i=0;i<21;i++)
                if (pieces_left[i] == piece)
                    pieces_left[i] = ' ';
        }
        else // otherwise, just tell us how many points we'll get
            for (int i=0;i<5;i++)
                for(int j=0;j<5;j++)
                    if (temp[i][j] != 0)
                    {
                        if (turn == 41 || turn == 42)
                        {
                            if (piece == 'a')
                                (*score)+=20;
                            else
                                (*score)+=15;
                        }
                        else
                            (*score)++;
                    }
             
        return MOVE_POSSIBLE;
    }
    return MOVE_IMPOSSIBLE;
}


/*------------------------------------
       Boot and game execution
------------------------------------*/

int main()
{
    // Setup Variables

    int board[14][14];      // The board itself
    int move_x, move_y;     // X and Y
    char piece;             // The chosen piece
    int turn = 1;           // Turn number
    int rot = 1;            // Rotation, between 0 and 7
    char pieces_left1[21];  // Which pieces does player 1 have?
    char pieces_left2[21];  // Which pieces does player 1 have?
    int score1 = 0;         // Player 1's score
    int score2 = 0;         // Player 2's score


    // Clean up the board before starting

    for (int i=0;i<15;i++)
        for (int j=0;j<15;j++)
            board[i][j] = 0;


    // Populate the list of possible moves

    for (int i=0;i<21;i++)
    {
        pieces_left1[i] = 'a' + i;
        pieces_left2[i] = 'a' + i;
    }


    // Play the game

    while(1)
    {
        int player = ((turn-1)%2)+1;

        debug_draw_screen(board);

        debug_message("Turn = ", turn, 0, 0);
        debug_message("\n", 0, 0, 0);
        debug_message("Player 1's score = ", score1, 0, 0);
        debug_message("\n", 0, 0, 0);
        debug_message("Player 2's score = ", score2, 0, 0);
        debug_message("\n", 0, 0, 0);
        debug_message("\n", 0, 0, 0);
        debug_message("Possible moves = ", 0, 0, 0);
        for (int i=0;i<21;i++)
            if (player == 1)
                debug_message("", pieces_left1[i], 1, 0);
            else
                debug_message("", pieces_left2[i], 1, 0);

        if (turn == 1)
            debug_message("\nPlayer 1, your turn (you must start at 5,5): ",0,0, 0);
        else if (turn == 2)
            debug_message("\nPlayer 2, your turn (you must start at a,a): ",0,0, 0);
        else
        {
            debug_message("\n", 0, 0, 0);
            debug_message("Player ", player, 0, 0);
            debug_message(", your turn: ", 0, 0, 0);

        }

        scanf(" %1x%1x%1c%1d", &move_x, &move_y, &piece, &rot);
        int my_move=0;
        if (move_x == 0xF && move_y == 0xF)
        {
            int goodscore=0;
            for(int i=0;i<14;i++)
                for (int j=0;j<14;j++)
                    for (int k=0;k<7;k++)
                        if (play_move(i, j, piece, k, board, turn, (player == 1 ? pieces_left1 : pieces_left2), &goodscore, 0) == MOVE_POSSIBLE)
                        {
                            printf("%i %i %c %i is a valid move which will yield %d points.\n", i, j, piece, k, goodscore);
                            goodscore = 0;
                        }
        }
        else
            my_move = play_move(move_x, move_y, piece, rot, board, turn, (player == 1 ? pieces_left1 : pieces_left2), (player == 1 ? &score1 : &score2),1);

        switch (my_move)
        {
            case MOVE_POSSIBLE: turn++; break; // Increment turn if a valid move happened.
            case MOVE_IMPOSSIBLE: debug_message("Invalid move due to unknown reasons. Tell a programmer! D:\n",0,0,1); break; 
            case MOVE_IMPOSSIBLE_EDGE: debug_message("Invalid move due to edges connecting.\n",0,0,1); break; 
            case MOVE_IMPOSSIBLE_CORN: debug_message("Invalid move due to no corners connecting.\n",0,0,1); break; 
            case MOVE_IMPOSSIBLE_FRST: debug_message("Invalid move due to not starting on 'S'.\n",0,0,1); break; 
            case MOVE_IMPOSSIBLE_OCUP: debug_message("Invalid move due to position occupied.\n",0,0,1); break; 
            case MOVE_IMPOSSIBLE_OOFB: debug_message("Invalid move due to being out of bounds.\n",0,0,1); break; 
            case MOVE_IMPOSSIBLE_USED: debug_message("Invalid move due to piece being used up.\n",0,0,1); break; 
        }
    }
}