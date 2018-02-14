#ifndef ARDEBG_H
#define ARDEBG_H

void debug_message(char str[100], int variable, int ischar, int wait);

void debug_draw_screen(int board[14][14]);

void debug_enter();

#endif