#include "check.h"
#include "blocks.h"
#include "transform.h"

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