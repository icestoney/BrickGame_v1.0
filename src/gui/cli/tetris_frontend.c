/**
 * @file tetris_frontend.c
 * @author shericen
 * @brief A code file in the C programming language containing a description of
 * all the functions declared in the header file tetris_frontend.h.
 * @date 2024-07-07
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "tetris_frontend.h"

int kbhit() {
  int c = getch();
  if (c != ERR) {
    ungetch(c);
    return 1;
  }
  return 0;
}

void print_rectangle(int top_y, int bottom_y, int left_x, int right_x) {
  mvaddch(top_y, left_x, ACS_ULCORNER);
  mvaddch(top_y, right_x, ACS_URCORNER);
  for (int i = left_x + 1; i < right_x; i++) {
    mvaddch(top_y, i, ACS_HLINE);
    mvaddch(bottom_y, i, ACS_HLINE);
  }
  for (int i = top_y + 1; i < bottom_y; i++) {
    mvaddch(i, left_x, ACS_VLINE);
    mvaddch(i, right_x, ACS_VLINE);
  }
  mvaddch(bottom_y, left_x, ACS_LLCORNER);
  mvaddch(bottom_y, right_x, ACS_LRCORNER);
}

void print_game_window(GameState_t state, block_type next) {
  int x = START_PRINT_POS_X, y = START_PRINT_POS_Y;
  for (int i = 0; i < WINDOW_HEIGHT; ++i) {
    x = START_PRINT_POS_X;
    move(y, x);
    for (int j = 0; j < WINDOW_WIDTH; ++j) {
      if (state.info->field[i][j] == active_block) {
        attron(COLOR_PAIR(state.block + 1));
        printw("  ");
        attroff(COLOR_PAIR(state.block + 1));
      } else if (state.info->field[i][j] == block) {
        if (y != 0) {
          attron(COLOR_PAIR(9));
          printw("  ");
          attroff(COLOR_PAIR(9));
        } else
          printw("  ");
      } else {
        if (y != 0) attron(COLOR_PAIR(8));
        printw("  ");
        attroff(COLOR_PAIR(8));
      }
      x += 2;
      move(y, x);
    }
    ++y;
  }

  print_rectangle(START_PRINT_POS_Y, START_PRINT_POS_Y + 21,
                  START_PRINT_POS_X - 1, START_PRINT_POS_X + 20);
  print_score_window(state.info->score);
  print_next_block(next);
  print_highscore(state.info->high_score);
  print_level(state.info->level);
  print_lable();
}

void print_score_window(int score) {
  move(START_PRINT_POS_Y + 1, START_PRINT_POS_X + 26);
  printw("SCORE");
  move(START_PRINT_POS_Y + 3, START_PRINT_POS_X + 25);
  printw("%4.7d", score);
  print_rectangle(START_PRINT_POS_Y, START_PRINT_POS_Y + WINDOW_BLOCK_HEIGHT,
                  START_SCORE_X, START_SCORE_X + WINDOW_BLOCK_WIDTH);
}

void print_highscore(int highscore) {
  move(START_PRINT_POS_Y + WINDOW_BLOCK_HEIGHT * 2 + 3, START_SCORE_X + 3);
  printw("HIGHSCORE");
  move(START_PRINT_POS_Y + WINDOW_BLOCK_HEIGHT * 2 + 5, START_SCORE_X + 4);
  printw("%4.7d", highscore);
  print_rectangle(START_PRINT_POS_Y + WINDOW_BLOCK_HEIGHT * 2 + 2,
                  START_PRINT_POS_Y + 2 + WINDOW_BLOCK_HEIGHT * 3,
                  START_SCORE_X, START_SCORE_X + WINDOW_BLOCK_WIDTH);
}

void print_block(block_type block_type, int start_x, int end_x, int start_y,
                 int end_y) {
  int x = start_x, y = start_y;
  int** buf = s21_calloc_matrix(2, 4);
  choose_block_state(buf, block_type, 0, 0);
  for (int i = 0; i <= end_y - start_y; ++i) {
    x = start_x;
    move(y, x);
    for (int j = 0; j <= end_x - start_x; ++j) {
      if (buf[i][j] == active_block) {
        attron(COLOR_PAIR(block_type + 1));
        printw("  ");
        attroff(COLOR_PAIR(block_type + 1));
      } else {
        attron(COLOR_PAIR(8));
        printw("  ");
        attroff(COLOR_PAIR(8));
      }
      x += 2;
      move(y, x);
    }
    ++y;
  }
  free_matrix(buf, 2);
}

void print_next_block(block_type block) {
  move(START_PRINT_POS_Y + WINDOW_BLOCK_HEIGHT + 3, START_SCORE_X + 3);
  print_block(block, START_SCORE_X + 3, START_SCORE_X + 6,
              START_PRINT_POS_Y + WINDOW_BLOCK_HEIGHT + 3,
              START_PRINT_POS_Y + WINDOW_BLOCK_HEIGHT + 4);
  move(START_PRINT_POS_Y + WINDOW_BLOCK_HEIGHT + 2, START_PRINT_POS_X + 26);
  printw("NEXT");
  move(START_PRINT_POS_Y + 3, START_PRINT_POS_X + 25);

  print_rectangle(START_PRINT_POS_Y + WINDOW_BLOCK_HEIGHT + 1,
                  START_PRINT_POS_Y + 1 + WINDOW_BLOCK_HEIGHT * 2,
                  START_SCORE_X, START_SCORE_X + WINDOW_BLOCK_WIDTH);
}

void print_level(int level) {
  int pos_y = START_PRINT_POS_Y + 3 + WINDOW_BLOCK_HEIGHT * 3;
  move(pos_y + 1, START_SCORE_X + 5);
  printw("LEVEL");
  move(pos_y + 3, START_SCORE_X + 2);
  printw("%6d", level);
  print_rectangle(pos_y, pos_y + WINDOW_BLOCK_HEIGHT, START_SCORE_X,
                  START_SCORE_X + WINDOW_BLOCK_WIDTH);
}

void print_pause() {
  attron(COLOR_PAIR(10));
  move(START_PRINT_POS_Y + 10, START_PRINT_POS_X + 8);
  printw("PAUSE");
  attroff(COLOR_PAIR(10));
}

void print_start_menu(GameState_t* state) {
  print_game_window(*state, Transparent_block);
  move(START_PRINT_POS_Y + 10, START_PRINT_POS_X + 2);
  printw("PRESS S TO START");
  int c = 0;
  while (c != 's') c = getch();
  clear();
}

bool print_end_menu(int score) {
  for (int i = 6; i < 15; ++i) {
    move(i, START_PRINT_POS_X + 1);
    printw("                  ");
  }
  move(START_PRINT_POS_Y + 7, START_PRINT_POS_X + 5);
  printw("GAME OVER");
  move(START_PRINT_POS_Y + 9, START_PRINT_POS_X + 2);
  printw("   SCORE %d", score);
  move(START_PRINT_POS_Y + 11, START_PRINT_POS_X + 2);
  printw("PRESS Q TO EXIT");
  move(START_PRINT_POS_Y + 13, START_PRINT_POS_X + 2);
  printw("OR S TO RESTART");
  int c = 0;
  while (c != 'q' && c != 's') c = getch();
  clear();
  return c == 's' ? true : false;
}

void print_lable() {
  int pos_y = START_PRINT_POS_Y + 4 + WINDOW_BLOCK_HEIGHT * 4;
  move(pos_y, START_SCORE_X);
  printw(" S21_TETRIS");
}

void init_gui() {
  initscr();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  start_color();
  init_pair(L_block + 1, COLOR_WHITE, COLOR_RED);
  init_pair(I_block + 1, COLOR_WHITE, COLOR_YELLOW);
  init_pair(T_block + 1, COLOR_WHITE, COLOR_MAGENTA);
  init_pair(square + 1, COLOR_WHITE, 10);
  init_pair(Z_block + 1, COLOR_WHITE, 11);
  init_pair(RL_block + 1, COLOR_WHITE, 12);
  init_pair(RZ_block + 1, COLOR_WHITE, 13);
  init_pair(Transparent_block + 1, COLOR_WHITE, 8);
  init_pair(9, COLOR_BLACK, COLOR_WHITE);
  init_pair(10, COLOR_WHITE, COLOR_BLACK);
}

void close_gui() { endwin(); }