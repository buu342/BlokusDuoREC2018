/*------------------------------------
     Global variables and macros
------------------------------------*/

#define DEBUG 0
#define MAX_CHECK 32
#define MAX_WAIT_CHECK 800000
#define MAX_WAIT_BEST  900000

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

int board[14][14];
int turn = 1;
char mypieces_left[21];

int setup_variables = 1;
char inByte = 0;


/*------------------------------------
         block definitions
------------------------------------*/

const int  block_a[5][5] = {
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
  {0, 0, 1, 0, 0},
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0}
};

const int  block_b[5][5] = {
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
  {0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0},
  {0, 0, 0, 0, 0}
};

const int  block_c[5][5] = {
  {0, 0, 0, 0, 0},
  {0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0},
  {0, 0, 0, 0, 0}
};

const int  block_d[5][5] = {
  {0, 0, 0, 0, 0},
  {0, 0, 1, 0, 0},
  {0, 0, 1, 1, 0},
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0}
};

const int  block_e[5][5] = {
  {0, 0, 0, 0, 0},
  {0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0}
};

const int  block_f[5][5] = {
  {0, 0, 0, 0, 0},
  {0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0},
  {0, 1, 1, 0, 0},
  {0, 0, 0, 0, 0}
};

const int  block_g[5][5] = {
  {0, 0, 0, 0, 0},
  {0, 0, 1, 0, 0},
  {0, 0, 1, 1, 0},
  {0, 0, 1, 0, 0},
  {0, 0, 0, 0, 0}
};

const int  block_h[5][5] = {
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
  {0, 0, 1, 1, 0},
  {0, 0, 1, 1, 0},
  {0, 0, 0, 0, 0}
};

const int  block_i[5][5] = {
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
  {0, 1, 1, 0, 0},
  {0, 0, 1, 1, 0},
  {0, 0, 0, 0, 0}
};

const int  block_j[5][5] = {
  {0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0}
};

const int  block_k[5][5] = {
  {0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0},
  {0, 1, 1, 0, 0},
  {0, 0, 0, 0, 0}
};

const int  block_l[5][5] = {
  {0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0},
  {0, 1, 1, 0, 0},
  {0, 1, 0, 0, 0},
  {0, 0, 0, 0, 0}
};

const int  block_m[5][5] = {
  {0, 0, 0, 0, 0},
  {0, 0, 1, 0, 0},
  {0, 1, 1, 0, 0},
  {0, 1, 1, 0, 0},
  {0, 0, 0, 0, 0}
};

const int  block_n[5][5] = {
  {0, 0, 0, 0, 0},
  {0, 1, 1, 0, 0},
  {0, 0, 1, 0, 0},
  {0, 1, 1, 0, 0},
  {0, 0, 0, 0, 0}
};

const int  block_o[5][5] = {
  {0, 0, 0, 0, 0},
  {0, 0, 1, 0, 0},
  {0, 0, 1, 1, 0},
  {0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0}
};

const int  block_p[5][5] = {
  {0, 0, 0, 0, 0},
  {0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0},
  {0, 1, 1, 1, 0},
  {0, 0, 0, 0, 0}
};

const int  block_q[5][5] = {
  {0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0},
  {0, 0, 1, 1, 1},
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0}
};

const int  block_r[5][5] = {
  {0, 0, 0, 0, 0},
  {0, 1, 1, 0, 0},
  {0, 0, 1, 1, 0},
  {0, 0, 0, 1, 0},
  {0, 0, 0, 0, 0}
};

const int  block_s[5][5] = {
  {0, 0, 0, 0, 0},
  {0, 1, 0, 0, 0},
  {0, 1, 1, 1, 0},
  {0, 0, 0, 1, 0},
  {0, 0, 0, 0, 0}
};

const int  block_t[5][5] = {
  {0, 0, 0, 0, 0},
  {0, 1, 0, 0, 0},
  {0, 1, 1, 1, 0},
  {0, 0, 1, 0, 0},
  {0, 0, 0, 0, 0}
};

const int  block_u[5][5] = {
  {0, 0, 0, 0, 0},
  {0, 0, 1, 0, 0},
  {0, 1, 1, 1, 0},
  {0, 0, 1, 0, 0},
  {0, 0, 0, 0, 0}
};


/*------------------------------------
           Transform array
------------------------------------*/

void transform_array(int piece[5][5], int rot)
{
  int temp[5][5];

  // Rotate by 90º if rot is a number that can be divided by 2

  for (int k = rot; k / 2 > 0; k -= 2)
  {
    for (int i = 0; i < 5; ++i)
      for (int j = 0; j < 5; ++j)
        temp[i][j] = piece[5 - j - 1][i];

    for (int i = 0; i < 5; ++i)
      for (int j = 0; j < 5; ++j)
        piece[i][j] = temp[i][j];
  }

  // If rot is an odd number, mirror the piece horizontally

  if (rot % 2 != 0)
  {
    for (int i = 0; i < 5; i++)
      for (int j = 0; j < 5; j++)
        temp[i][j] = piece[i][5 - j - 1];

    for (int i = 0; i < 5; ++i)
      for (int j = 0; j < 5; ++j)
        piece[i][j] = temp[i][j];
  }

}


/*------------------------------------
        Move validity checker
------------------------------------*/

int check_move(int move_x, int move_y, char piece, int rot, int board[14][14], int turn, int *score)
{
  int player = ((turn - 1) % 2) + 1;
  int temp_check[5][5];

  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 5; j++)
      switch (piece)
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

  int check_start = 0;
  int check_corner = 0;

  for (int j = 0; j < 5; j++)
  {
    for (int i = 0; i < 5; i++)
    {
      if (temp_check[j][i] == 1)
      {
        if ((((move_x - 2 + i) > 0xE || (move_y - 2 + j) > 0xE) || ((move_x - 3 + i) < 0 || (move_y - 3 + j) < 0))) // Out of bounds.
          return MOVE_IMPOSSIBLE_OOFB;
        else if (board[move_y - 3 + j][move_x - 3 + i] != 0) // Occupying other block.
          return MOVE_IMPOSSIBLE_OCUP;
        else if ((move_y - 3 + j + 1 <= 13 && board[move_y - 3 + j + 1][move_x - 3 + i] == player) ||
                 (move_y - 3 + j - 1 >= 0  && board[move_y - 3 + j - 1][move_x - 3 + i] == player) ||
                 (move_x - 3 + i + 1 <= 13 && board[move_y - 3 + j][move_x - 3 + i + 1] == player) ||
                 (move_x - 3 + i - 1 >= 0  && board[move_y - 3 + j][move_x - 3 + i - 1] == player))
          return MOVE_IMPOSSIBLE_EDGE;
        else if ((turn == 1 || turn == 2) && check_start == 0 && (move_y - 2 + j == move_x - 2 + i) && move_x - 2 + i == (turn == 1 ? 5 : 0xA)) // Starting in the correct position
          check_start = 1;
        else if (turn > 2 && check_corner == 0 && // Corner is connecting
                 ((move_y - 3 + j - 1 >= 0  && move_x - 3 + i - 1 >= 0  && board[move_y - 3 + j - 1][move_x - 3 + i - 1] == player) ||
                  (move_y - 3 + j + 1 <= 13 && move_x - 3 + i - 1 >= 0  && board[move_y - 3 + j + 1][move_x - 3 + i - 1] == player) ||
                  (move_y - 3 + j - 1 >= 0  && move_x - 3 + i + 1 <= 13 && board[move_y - 3 + j - 1][move_x - 3 + i + 1] == player) ||
                  (move_y - 3 + j + 1 <= 13 && move_x - 3 + i + 1 <= 13 && board[move_y - 3 + j + 1][move_x - 3 + i + 1] == player)))
          check_corner = 1;
      }
    }
  }

  if (((turn == 1 || turn == 2) && check_start == 0))
    return MOVE_IMPOSSIBLE_FRST;
  if (turn > 2 && check_corner == 0)
    return MOVE_IMPOSSIBLE_CORN;


  // Tell us how many points we'll get

  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 5; j++)
      if (temp_check[i][j] != 0)
      {
        if (turn == 41 || turn == 42)
        {
          if (piece == 'a')
            (*score) += 20;
          else
            (*score) += 15;
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
  int player = ((turn - 1) % 2) + 1;
  int temp[5][5];
  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 5; j++)
      switch (piece)
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

  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 5; j++)
      if (temp[i][j] != 0)
      {
        board[move_y - 3 + i][move_x - 3 + j] = player;
        (*score)++;
      }


  // If all pieces have been used, award 15 points. If the last piece was A, award 20 instead

  if (turn == 41 || turn == 42)
  {
    if (piece == 'a')
      (*score) += 20;
    else
      (*score) += 15;
  }


  // Take away the move

  for (int i = 0; i < 21; i++)
    if (pieces_left[i] == piece)
      pieces_left[i] = ' ';
}


/*------------------------------------
        Count amount of corners
------------------------------------*/

void check_corner(int move_x, int move_y, char piece, int rot, int board[14][14], int turn, int *corner_count)
{
  int player = ((turn - 1) % 2) + 1;
  int temp_check[5][5];

  int temp_board[14][14];
  for (int j = 0; j < BOARD_HEIGHT; j++)
    for (int i = 0; i < BOARD_LENGTH; i++)
      temp_board[j][i] = board[j][i];

  char a[21] = {'a'};
  int ss = 0;

  play_move(move_x, move_y, piece, rot, temp_board, turn, a, &ss );

  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 5; j++)
      temp_check[i][j] = block_a[i][j];

  for (move_y = 1; move_y < 15; move_y++)
    for (move_x = 1; move_x < 15; move_x++)
    {
      int check_corner = 0;
      for (int j = 0; j < 5; j++)
      {
        for (int i = 0; i < 5; i++)
        {
          if (temp_check[j][i] == 1)
          {
            if ((((move_x - 2 + i) > 0xE || (move_y - 2 + j) > 0xE) || ((move_x - 3 + i) < 0 || (move_y - 3 + j) < 0))) // Out of bounds.
              continue;
            else if (temp_board[move_y - 3 + j][move_x - 3 + i] != 0) // Occupying other block.
              continue;
            else if ((move_y - 3 + j + 1 <= 13 && temp_board[move_y - 3 + j + 1][move_x - 3 + i] == player) ||
                     (move_y - 3 + j - 1 >= 0  && temp_board[move_y - 3 + j - 1][move_x - 3 + i] == player) ||
                     (move_x - 3 + i + 1 <= 13 && temp_board[move_y - 3 + j][move_x - 3 + i + 1] == player) ||
                     (move_x - 3 + i - 1 >= 0  && temp_board[move_y - 3 + j][move_x - 3 + i - 1] == player))
              continue;
            else if (check_corner == 0 && // Corner is connecting
                     ((move_y - 3 + j - 1 >= 0  && move_x - 3 + i - 1 >= 0  && temp_board[move_y - 3 + j - 1][move_x - 3 + i - 1] == player) ||
                      (move_y - 3 + j + 1 <= 13 && move_x - 3 + i - 1 >= 0  && temp_board[move_y - 3 + j + 1][move_x - 3 + i - 1] == player) ||
                      (move_y - 3 + j - 1 >= 0  && move_x - 3 + i + 1 <= 13 && temp_board[move_y - 3 + j - 1][move_x - 3 + i + 1] == player) ||
                      (move_y - 3 + j + 1 <= 13 && move_x - 3 + i + 1 <= 13 && temp_board[move_y - 3 + j + 1][move_x - 3 + i + 1] == player)))
              check_corner = 1;
          }
        }
      }

      if (check_corner == 0)
        continue;


      // Tell us how many points we'll get

      for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
          if (temp_check[i][j] != 0)
            (*corner_count)++;
    }
}


/*------------------------------------
         Check available moves
------------------------------------*/

char *strchr_ar(char *str, int ch)
{
  do
  {
    if (*str == ch)
      return str;
  }
  while (*str++);
  return NULL;
}


/*------------------------------------
            Setup and loop
------------------------------------*/

void setup()
{
  // start serial port at 115200 bps and wait for port to open:
  Serial.begin(115200);
  while (!Serial)
    ; // wait for serial port to connect. Needed for native USB port only
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop()
{

  // Setup Variables

  if (setup_variables == 1)
  {
    setup_variables = 0;

    // Clean up the variables before starting

    for (int i = 0; i < 14; i++)
      for (int j = 0; j < 14; j++)
        board[i][j] = 0;

    // Populate the list of pieces left

    for (int i = 0; i < 21; i++)
    {
      mypieces_left[i] = 'a' + i;
    }
  }

  int player = ((turn - 1) % 2) + 1;


  // Play the game

  if (Serial.available() > 0)
  {
    // read the incoming byte:
    inByte = Serial.read();
    if (inByte == '0')
    {
      Serial.print("1N2");
    }
    else if (inByte == '2')
    {
      delay(1);
      inByte = Serial.read();
      if (inByte == '5')
      {
        int i = 0;
        play_move(5, 6, 'u', 0, board, turn, mypieces_left, &i);
        turn++;
        Serial.print("56u0");
      }
      else if (inByte == 'a' || inByte == 'A')
      {
        int i = 0;
        play_move(0xa, 0xb, 'u', 0, board, turn, mypieces_left, &i);
        turn++;
        Serial.print("abu0");
      }
    }
    else if (inByte == '3')
    {
      delay(1);
      char second_byte = Serial.read();
      delay(1);
      int byte_x = Serial.read();
      delay(1);
      int byte_y = Serial.read();
      delay(1);
      char byte_p = Serial.read();
      delay(1);
      int byte_r = Serial.read();

      if (byte_x >= '0' && byte_x <= '9') byte_x = byte_x - '0'; else if (byte_x >= 'a' && byte_x <= 'e') byte_x = byte_x - 'a' + 10;
      if (byte_y >= '0' && byte_y <= '9') byte_y = byte_y - '0'; else if (byte_y >= 'a' && byte_y <= 'e') byte_y = byte_y - 'a' + 10;
      if (byte_p >= 'A' && byte_p <= 'U') byte_p = byte_p + 32;
      if (byte_r >= '0' && byte_r <= '9') byte_r = byte_r - '0';

      int j = 0;
      char pp[21] = {'a'};
      play_move(byte_x, byte_y, byte_p, byte_r, board, turn, pp, &j);
      turn++;

      if (second_byte == '5') {
        int i = 0;
        play_move(5, 6, 'u', 0, board, turn, mypieces_left, &i);
        turn++;
        Serial.print("56u0");
      }
      else if (second_byte == 'a' || second_byte == 'A') {
        int i = 0;
        play_move(0xa, 0xb, 'u', 0, board, turn, mypieces_left, &i);
        turn++;
        Serial.print("abu0");
      }

    }
    else if (inByte == '9')
    {
      Serial.print("");              //acabou o jogo
      return;
    }
    else if (inByte == '4')
    {
      unsigned long start_time = micros();
      /////////////////////////////////// Their move ///////////////////////////////////
      delay(1);
      int byte_x = Serial.read();
      delay(1);
      int byte_y = Serial.read();
      delay(1);
      char byte_p = Serial.read();
      delay(1);
      int byte_r = Serial.read();

      if (byte_p != '0')
      {
        if (byte_x >= '0' && byte_x <= '9') byte_x = byte_x - '0'; else if (byte_x >= 'a' && byte_x <= 'e') byte_x = byte_x - 'a' + 10;
        if (byte_y >= '0' && byte_y <= '9') byte_y = byte_y - '0'; else if (byte_y >= 'a' && byte_y <= 'e') byte_y = byte_y - 'a' + 10;
        if (byte_p >= 'A' && byte_p <= 'U') byte_p = byte_p + 32;
        if (byte_r >= '0' && byte_r <= '9') byte_r = byte_r - '0';
        int m = 0;
        char pp[21]={'a'};
        play_move(byte_x, byte_y, byte_p, byte_r, board, turn, pp, &m);
      }
      turn++;

      /////////////////////////////////// Our move ///////////////////////////////////
      player = ((turn - 1) % 2) + 1;
      // Check all valid moves and store them in the possible array.
      int possible[MAX_CHECK][5];
      for (int i = 0; i < MAX_CHECK; i++)
        for (int j = 0; j < 5; j++)
          possible[i][j] = 0;

      int t = 0, score = 0, corners_left = 0;
      for (int l = 'u'; l >= 'a'; l--)
      {
        if (strchr_ar(mypieces_left, l) == NULL) // check if move has been used up.
          continue;
        for (int j = 1; j <= 14; j++)
        {
          for (int i = 1; i <= 14; i++)
          {
            if (board[j - 1][i - 1] == 0)
            {
              for (int k = 0; k < 8; k++)
              {
                int test = check_move(i, j, l, k, board, turn, &score);
                if (test == MOVE_POSSIBLE)
                {
                  check_corner(i, j, l, k, board, turn, &corners_left);
                  possible[t][0] = score + corners_left;
                  possible[t][1] = i;
                  possible[t][2] = j;
                  possible[t][3] = l;
                  possible[t][4] = k;
                  score = corners_left = 0;
                  t++;
                  unsigned long end_time = micros();
                  if (DEBUG == 1)
                  {
                    Serial.print("    "); 
                    Serial.print(end_time-start_time); 
                    Serial.print("    ");
                  }
                  if (end_time-start_time >= MAX_WAIT_CHECK)
                    t = MAX_CHECK;
                }
                unsigned long end_time = micros();
                if (end_time-start_time >= MAX_WAIT_CHECK)
                    t = MAX_CHECK;
                if (t >= MAX_CHECK)
                  break;
              }
            }
            unsigned long end_time = micros();
            if (end_time-start_time >= MAX_WAIT_CHECK)
                t = MAX_CHECK;
            if (t >= MAX_CHECK)
              break;
          }
          unsigned long end_time = micros();
          if (end_time-start_time >= MAX_WAIT_CHECK)
              t = MAX_CHECK;
          if (t >= MAX_CHECK)
            break;
        }
        unsigned long end_time = micros();
        if (end_time-start_time >= MAX_WAIT_CHECK)
            t = MAX_CHECK;
        if (t >= MAX_CHECK)
          break;
      }
      int skip_turn = 0;
      if (possible[0][0] == 0)
      {
        Serial.print("0000");
        turn++;
        skip_turn = 1;
      }

      // Find the best move
      if (skip_turn == 0)
      {
        int best[2] = {0, 0};
        for (int i = 0; i < MAX_CHECK; i++)
          if (possible[i][0] > best[1])
          {
            best[0] = i;
            best[1] = possible[i][0];
            unsigned long end_time = micros();
            if (end_time-start_time >= MAX_WAIT_BEST)
              break;
          }
          else if (possible[i][0] == 0)
            break;


        // Play that move

        t = best[0];
        int m;
        play_move(possible[t][1], possible[t][2], possible[t][3], possible[t][4], board, turn, mypieces_left, m);
          
        char final_move[5];
        final_move[0] = ((possible[t][1] >= 0 && possible[t][1] <= 9) ? possible[t][1] + '0' : possible[t][1] + 'a' - 10);
        final_move[1] = ((possible[t][2] >= 0 && possible[t][2] <= 9) ? possible[t][2] + '0' : possible[t][2] + 'a' - 10);
        final_move[2] = possible[t][3];
        final_move[3] = possible[t][4] + '0';
        final_move[4] = '\0';

        Serial.print(final_move);

        turn++;
      }
      if (DEBUG == 1)
      {
        unsigned long end_time = micros();
        Serial.print("     Total time of: ");
        Serial.print(end_time-start_time);
        Serial.print(" miliseconds.");
        Serial.println("");
      }
    }
    else if (inByte == '7' && DEBUG == 1)
    {
      for (int j = 0; j < 14; j++)
      {
        Serial.println("");
        for (int i = 0; i < 14; i++)
          if (board[j][i] == 0)
            Serial.print(" _ ");
          else if (board[j][i] == 1)
            Serial.print(" 1 ");
          else if (board[j][i] == 2)
            Serial.print(" 2 ");
      }
      Serial.println("");
      for (int i = 0; i < 21; i++)
        Serial.print(mypieces_left[i]);
    }
  }
}
