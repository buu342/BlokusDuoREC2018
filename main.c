/*------------------------------------
         Standard C Libraries
------------------------------------*/

#include <stdio.h>
#include <string.h>


/*------------------------------------
            Custom headers
------------------------------------*/

#include "blocks.h"
#include "transform.h"
#include "debug.h"

#define cpu_play 1


/*------------------------------------
        Move validity checker
------------------------------------*/

int check_move(int move_x, int move_y, char piece, int rot, int board[14][14], int turn, int *score)
{
    int player = ((turn-1)%2)+1;
    int temp_check[5][5];

    /*int temp_board[14][14];
    for (int j=0; j<BOARD_HEIGHT; j++)
        for (int i=0; i<BOARD_LENGTH; i++)
            temp_board[j][i] = board[j][i];*/

    for (int i=0;i<5;i++)
        for(int j=0;j<5;j++)
            switch(piece)
            {
                case 'a': temp_check[i][j] = block_a[i][j]; break;
                case 'b': temp_check[i][j] = block_b[i][j]; break;
                case 'c': temp_check[i][j] = block_c[i][j]; break;
                case 'd': temp_check[i][j] = block_d[i][j]; break;
                case 'e': temp_check[i][j] = block_e[i][j]; break;
                case 'f': temp_check[i][j] = block_f[i][j]; break;
                case 'g': temp_check[i][j] = block_g[i][j]; break;
                case 'h': temp_check[i][j] = block_h[i][j]; break;
                case 'i': temp_check[i][j] = block_i[i][j]; break;
                case 'j': temp_check[i][j] = block_j[i][j]; break;
                case 'k': temp_check[i][j] = block_k[i][j]; break;
                case 'l': temp_check[i][j] = block_l[i][j]; break;
                case 'm': temp_check[i][j] = block_m[i][j]; break;
                case 'n': temp_check[i][j] = block_n[i][j]; break;
                case 'o': temp_check[i][j] = block_o[i][j]; break;
                case 'p': temp_check[i][j] = block_p[i][j]; break;
                case 'q': temp_check[i][j] = block_q[i][j]; break;
                case 'r': temp_check[i][j] = block_r[i][j]; break;
                case 's': temp_check[i][j] = block_s[i][j]; break;
                case 't': temp_check[i][j] = block_t[i][j]; break;
                case 'u': temp_check[i][j] = block_u[i][j]; break;
            }

    // Apply transformations to the temporary array
    if (piece != 'a' && piece != 'u') 
        transform_array(temp_check, rot);


    // Check for if the move is possible

    int check_start=0;
    int check_corner=0;

    for (int j=0;j<5;j++)
    {
        for (int i=0;i<5;i++)
        {
            if (temp_check[j][i] == 1)
            {
                if ((((move_x-2+i)>0xE || (move_y-2+j)>0xE) || ((move_x-3+i)<0 || (move_y-3+j)<0))) // Out of bounds.
                    return MOVE_IMPOSSIBLE_OOFB;
                else if (board[move_y-3+j][move_x-3+i] != 0) // Occupying other block.
                    return MOVE_IMPOSSIBLE_OCUP;
                else if ((move_y-3+j+1 <= 13 && board[move_y-3+j+1][move_x-3+i] == player) || 
                         (move_y-3+j-1 >= 0  && board[move_y-3+j-1][move_x-3+i] == player) || 
                         (move_x-3+i+1 <= 13 && board[move_y-3+j][move_x-3+i+1] == player) || 
                         (move_x-3+i-1 >= 0  && board[move_y-3+j][move_x-3+i-1] == player))
                    return MOVE_IMPOSSIBLE_EDGE;
                else if ((turn == 1 || turn == 2) && check_start == 0 && (move_y-2+j == move_x-2+i) && move_x-2+i == (turn==1?5:0xA)) // Starting in the correct position
                        check_start = 1;
                else if (turn > 2 && check_corner == 0 && // Corner is connecting
                        ((move_y-3+j-1 >= 0  && move_x-3+i-1 >= 0  && board[move_y-3+j-1][move_x-3+i-1] == player) || 
                         (move_y-3+j+1 <= 13 && move_x-3+i-1 >= 0  && board[move_y-3+j+1][move_x-3+i-1] == player) || 
                         (move_y-3+j-1 >= 0  && move_x-3+i+1 <= 13 && board[move_y-3+j-1][move_x-3+i+1] == player) || 
                         (move_y-3+j+1 <= 13 && move_x-3+i+1 <= 13 && board[move_y-3+j+1][move_x-3+i+1] == player)))
                        check_corner = 1;
            }
        }
    }

    if (((turn == 1 || turn == 2) && check_start == 0))
        return MOVE_IMPOSSIBLE_FRST;
    if (turn > 2 && check_corner == 0)
          return MOVE_IMPOSSIBLE_CORN;


    // Tell us how many points we'll get

    for (int i=0;i<5;i++)
        for(int j=0;j<5;j++)
            if (temp_check[i][j] != 0)
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


/*------------------------------------
        insert move to a board
------------------------------------*/

void play_move(int move_x, int move_y, char piece, int rot, int board[14][14], int turn, char pieces_left[22], int *score)
{
    int player = ((turn-1)%2)+1;
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


/*------------------------------------
        Count amount of corners
------------------------------------*/

void check_corner(int move_x, int move_y, char piece, int rot, int board[14][14], int turn, int *corner_count)
{
    int player = ((turn-1)%2)+1;
    int temp_check[5][5];

    int temp_board[14][14];
    for (int j=0; j<BOARD_HEIGHT; j++)
        for (int i=0; i<BOARD_LENGTH; i++)
            temp_board[j][i] = board[j][i];

    char a[21] = {'a'};
    int ss=0;

    play_move(move_x, move_y, piece, rot, temp_board, turn, a, &ss );

    for (int i=0;i<5;i++)
        for(int j=0;j<5;j++)
            temp_check[i][j] = block_a[i][j];

    for (move_y=1;move_y<15;move_y++)
        for (move_x=1;move_x<15;move_x++)
        {
            int check_corner=0;
            for (int j=0;j<5;j++)
            {
                for (int i=0;i<5;i++)
                {
                    if (temp_check[j][i] == 1)
                    {
                        if ((((move_x-2+i)>0xE || (move_y-2+j)>0xE) || ((move_x-3+i)<0 || (move_y-3+j)<0))) // Out of bounds.
                            continue;
                        else if (temp_board[move_y-3+j][move_x-3+i] != 0) // Occupying other block.
                            continue;
                        else if ((move_y-3+j+1 <= 13 && temp_board[move_y-3+j+1][move_x-3+i] == player) || 
                                 (move_y-3+j-1 >= 0  && temp_board[move_y-3+j-1][move_x-3+i] == player) || 
                                 (move_x-3+i+1 <= 13 && temp_board[move_y-3+j][move_x-3+i+1] == player) || 
                                 (move_x-3+i-1 >= 0  && temp_board[move_y-3+j][move_x-3+i-1] == player))
                            continue;
                        else if (check_corner == 0 && // Corner is connecting
                                ((move_y-3+j-1 >= 0  && move_x-3+i-1 >= 0  && temp_board[move_y-3+j-1][move_x-3+i-1] == player) || 
                                 (move_y-3+j+1 <= 13 && move_x-3+i-1 >= 0  && temp_board[move_y-3+j+1][move_x-3+i-1] == player) || 
                                 (move_y-3+j-1 >= 0  && move_x-3+i+1 <= 13 && temp_board[move_y-3+j-1][move_x-3+i+1] == player) || 
                                 (move_y-3+j+1 <= 13 && move_x-3+i+1 <= 13 && temp_board[move_y-3+j+1][move_x-3+i+1] == player)))
                                check_corner = 1;
                    }
                }
            }

            if (check_corner == 0)
                continue;


            // Tell us how many points we'll get

            for (int i=0;i<5;i++)
                for(int j=0;j<5;j++)
                    if (temp_check[i][j] != 0)
                        (*corner_count)++;
        }
}

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
    int possible[10000][5];      // List of possible moves and their score


    // Clean up the variables before starting

    for (int i=0;i<15;i++)
        for (int j=0;j<15;j++)
            board[i][j] = 0;

    for (int i=0;i<2000;i++)
        for (int j=0;j<5;j++)
            possible[i][j] = 0;


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
            if (strchr(player == 1 ? pieces_left1 : pieces_left2, l) == NULL) // check if move has been used up.
                continue;
            for (int j=1;j<=0xE;j++)
            {
                for (int i=1;i<=0xE;i++)
                {
                    //if (board[j][i] == 0)
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
    printf("\ngame over");
}