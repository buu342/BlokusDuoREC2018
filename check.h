#ifndef ARCHCK_H
#define ARCHCK_H

int check_move(int move_x, int move_y, char piece, int rot, int board[14][14], int turn, int *score);

void play_move(int move_x, int move_y, char piece, int rot, int board[14][14], int turn, char pieces_left[22], int *score);

void check_corner(int move_x, int move_y, char piece, int rot, int board[14][14], int turn, int *corner_count);

#endif