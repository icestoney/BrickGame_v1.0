/**
 * @file fsm_matrix.c
 * @author shericen
 * @brief A code file in the C programming language containing a description of
 * all the functions declared in the header file fsm_matrix.h.
 * @date 2024-07-07
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "fsm_matrix.h"

UserAction_t player_input(int input) {
  UserAction_t action = 0;
  switch (input) {
    case KEY_LEFT:
      action = Left;
      break;
    case KEY_RIGHT:
      action = Right;
      break;
    case KEY_DOWN:
      action = Down;
      break;
    case KEY_UP:
      action = Action;
      break;
    case 'p':
    case 'P':
      action = Pause;
      break;
    case 'q':
    case 'Q':
      action = Terminate;
      break;
    case 's':
    case 'S':
      action = Start;
      break;
    default:
      break;
  }
  return action;
}

void game_pause() {
  print_pause();
  char c = 0;
  while (c != 'p' && c != 's' && c != 'q') c = getch();
}

void game_loop() {
  bool is_game = true;
  GameState_t state = {0};
  init_tetris_map(&state);
  print_start_menu(&state);
  create_start_block(&state);
  clock_t timer_1 = clock();

  while (is_game) {
    set_new_level(&state);
    *(state.info) = updateCurrentState();
    print_game_window(state, state.next_block);
    refresh();
    if (clock() - timer_1 > state.info->speed ||
        (clock() <= state.info->speed && timer_1 == 0)) {
      is_game = game_process(&state);
      timer_1 = clock();
    }

    int input_result = game_input(&state);
    if (input_result == 1)
      timer_1 = 0;
    else if (input_result == 2)
      is_game = false;

    if (state.info->high_score < state.info->score) set_new_highscore(&state);
    if (!is_game) {
      is_game = print_end_menu(state.info->score);
      clear_tetris(&state);
      init_tetris_map(&state);
      timer_1 = clock();
      create_start_block(&state);
    }
  }
  clear_tetris(&state);
}

int game_input(GameState_t *state) {
  int result = 0;
  int input = 0;
  if (kbhit()) {
    input = getch();
    UserAction_t t = player_input(input);
    userInput(t, true);
    if (t == Down) result = 1;
    *(state->info) = updateCurrentState();
    print_game_window(*state, state->next_block);
    refresh();
    if (t == Terminate) result = 2;
    if (t == Pause) {
      game_pause();
    }
  }

  return result;
}

bool game_process(GameState_t *state) {
  bool result = true;
  if (try_down(state) || state->is_downed) {
    state->is_downed = false;
    if (get_score(state)) {
      result = false;
    } else {
      state->block = state->next_block;
      spawn_block(state, SPAWN_POS_X);
      state->next_block = get_random_block();
    }
  }
  *(state->info) = updateCurrentState();
  print_game_window(*state, state->next_block);
  refresh();
  return result;
}

void create_start_block(GameState_t *state) {
  state->block = get_random_block();
  spawn_block(state, SPAWN_POS_X);
  state->next_block = get_random_block();
}