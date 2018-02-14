#ifndef ARBLOK_H
#define ARBLOK_H

#define cr_red     "\x1b[31m"
#define cr_green   "\x1b[32m"
#define cr_yellow  "\x1b[33m"
#define cr_blue    "\x1b[34m"
#define cr_magenta "\x1b[35m"
#define cr_cyan    "\x1b[36m"
#define cr_reset   "\x1b[0m"

#define BOARD_LENGTH 0xE
#define BOARD_HEIGHT 0xE

#define MOVE_POSSIBLE   1
#define MOVE_IMPOSSIBLE 0
#define MOVE_IMPOSSIBLE_USED -1
#define MOVE_IMPOSSIBLE_OOFB -2
#define MOVE_IMPOSSIBLE_OCUP -3
#define MOVE_IMPOSSIBLE_EDGE -4
#define MOVE_IMPOSSIBLE_FRST -5
#define MOVE_IMPOSSIBLE_CORN -6

extern const int block_a[5][5];
extern const int block_b[5][5];
extern const int block_c[5][5];
extern const int block_d[5][5];
extern const int block_e[5][5];
extern const int block_f[5][5];
extern const int block_g[5][5];
extern const int block_h[5][5];
extern const int block_i[5][5];
extern const int block_j[5][5];
extern const int block_k[5][5];
extern const int block_l[5][5];
extern const int block_m[5][5];
extern const int block_n[5][5];
extern const int block_o[5][5];
extern const int block_p[5][5];
extern const int block_q[5][5];
extern const int block_r[5][5];
extern const int block_s[5][5];
extern const int block_t[5][5];
extern const int block_u[5][5];

#endif
