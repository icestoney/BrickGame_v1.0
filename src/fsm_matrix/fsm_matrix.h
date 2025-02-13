/**
 * @file fsm_matrix.h
 * @author shericen
 * @brief A header file combining backend and frontend into a finite state
 * machine. It contains function declarations.
 * @date 2024-07-07
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef FSM_MATRIX
#define FSM_MATRIX

#include "../brick_game/tetris/tetris_backend.h"
#include "../gui/cli/tetris_frontend.h"

/**
 * @brief Accepts the player's input from the keyboard and selects the
 * appropriate action.
 * @param input The value of the pressed key in the int type.
 * @return Current player action.
 */
UserAction_t player_input(int input);

/**
 * @brief Changes the game state to pause.
 */
void game_pause();

/**
 * @brief Accepts the current state of the game and performs an action or
 * changes the state of the game, depending on the key pressed by the player.
 * @param state Current game state.
 * @return The result of executing the function is an int number, which
 * indicates the state of the game.
 */
int game_input(GameState_t* state);

/**
 * @brief A gameplay feature that checks if a block needs to be lowered, spawn a
 * new one, or if the game needs to be stopped.
 * @param state Current game state.
 * @return The result is of the bool type, which means the continuation of the
 * gameplay or its termination.
 */
bool game_process(GameState_t* state);

/**
 * @brief The main game cycle with the condition of the end of the game.
 */
void game_loop();

/**
 * @brief Creating the first block and defining the next one.
 * @param state Current game state.
 */
void create_start_block(GameState_t* state);

#endif