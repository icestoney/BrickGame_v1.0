/**
 * @file tetris_frontend.h
 * @author shericen
 * @brief A header file containing 4 standard libraries (stdbool.h, stdio.h,
 * stdlib.h, time.h), macros, structures, a three-dimensional array and the
 * declaration of all functions.
 * @date 2024-07-07
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef TETRIS_FRONTEND
#define TETRIS_FRONTEND
/**
 * @brief X coordinate of the start of printing.
 */
#define START_PRINT_POS_X 2

/**
 * @brief Y coordinate of the start of printing.
 */
#define START_PRINT_POS_Y 0

/**
 * @brief X coordinate of the start of printing score board.
 */
#define START_SCORE_X START_PRINT_POS_X + 21

/**
 * @brief Y coordinate of the start of printing score board.
 */
#define START_SCORE_Y START_PRINT_POS_Y

/**
 * @brief Width for boards (score, next, highscore, level).
 */
#define WINDOW_BLOCK_WIDTH 14

/**
 * @brief Height for boards (score, next, highscore, level).
 */
#define WINDOW_BLOCK_HEIGHT 4

#include <ncurses.h>

#include "../../brick_game/tetris/tetris_backend.h"

/**
 * @brief Keyboard hit.
 * @return 0 if the key was not pressed, 1 if the key was pressed != -1.
 */
int kbhit();

/**
 * @brief Printing a rectangle.
 * @param x1 X coordinate of the upper left corner of the rectangle.
 * @param y1 Y coordinate of the upper left corner of the rectangle.
 * @param x2 X coordinate of the lower right corner of the rectangle.
 * @param y2 Y coordinate of the lower right corner of the rectangle.
 */
void print_rectangle(int x1, int y1, int x2, int y2);

/**
 * @brief Printing the game window.
 * @param state Current game state.
 * @param next Block type.
 */
void print_game_window(GameState_t state, block_type next);

/**
 * @brief Printing the score board.
 * @param score The value of points in the int type.
 */
void print_score_window(int score);

/**
 * @brief Printing the highscore board.
 * @param highscore The maximum value of score in the int type.
 */
void print_highscore(int highscore);

/**
 * @brief Printing a board containing the next block.
 * @param block Block type.
 */
void print_next_block(block_type block);

/**
 * @brief Printing the level board.
 * @param level The value of level in the int type.
 */
void print_level(int level);

/**
 * @brief Printing the pause status.
 */
void print_pause();

/**
 * @brief Printing the start menu.
 * @param state Current game state.
 */
void print_start_menu(GameState_t* state);

/**
 * @brief Printing the end menu.
 * @param score The value of points in the int type.
 */
bool print_end_menu(int score);

/**
 * @brief Printing the label.
 */
void print_lable();

/**
 * @brief Initializing the graphical user interface.
 */
void init_gui();

/**
 * @brief Closing the graphical user interface.
 */
void close_gui();

/**
 * @brief Closing the graphical user interface.
 * @param block_type Block type.
 * @param start_x X coordinate of the upper left corner of the rectangle.
 * @param end_x X coordinate of the lower right corner of the rectangle.
 * @param start_y Y coordinate of the upper left corner of the rectangle.
 * @param end_y Y coordinate of the lower right corner of the rectangle.
 */
void print_block(block_type block_type, int start_x, int end_x, int start_y,
                 int end_y);

#endif