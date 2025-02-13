/**
 * @file tetris.c
 * @author shericen
 * @brief A code file in the C programming language containing an entry point of
 * the game. Contains the connected tetris_frontend.h and fsm_matrix.h.
 * @date 2024-07-07
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "fsm_matrix/fsm_matrix.h"
#include "gui/cli/tetris_frontend.h"

/**
 * @brief The entry point of the game.
 * Execution of the program starts here.
 */
int main() {
  init_gui();
  game_loop();
  close_gui();
  return 0;
}
