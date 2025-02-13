#include "test.h"

START_TEST(init_test) {
  GameState_t state = {0};
  init_tetris_map(&state);

  ck_assert_int_eq(state.info->score, 0);
  ck_assert_int_eq(state.info->level, 1);
  ck_assert_int_eq(state.info->speed, 2000000);
  ck_assert_ptr_nonnull(state.info->field);
  clear_tetris(&state);
}
END_TEST

START_TEST(spawn_block_L) {
  GameState_t state = {0};
  init_tetris_map(&state);
  state.block = L_block;
  spawn_block(&state, SPAWN_POS_X);
  int arr[] = {0, 0, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
      ck_assert_int_eq(state.info->field[i + SPAWN_POS_Y][j + SPAWN_POS_X],
                       arr[i * 4 + j]);
  clear_tetris(&state);
}
END_TEST

START_TEST(spawn_block_RL) {
  GameState_t state = {0};
  init_tetris_map(&state);
  state.block = RL_block;
  spawn_block(&state, SPAWN_POS_X);
  int arr[] = {2, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
      ck_assert_int_eq(state.info->field[i + SPAWN_POS_Y][j + SPAWN_POS_X],
                       arr[i * 4 + j]);
  clear_tetris(&state);
}
END_TEST

START_TEST(spawn_block_Z) {
  GameState_t state = {0};
  init_tetris_map(&state);
  state.block = Z_block;
  spawn_block(&state, SPAWN_POS_X);
  int arr[] = {2, 2, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
      ck_assert_int_eq(state.info->field[i + SPAWN_POS_Y][j + SPAWN_POS_X],
                       arr[i * 4 + j]);
  clear_tetris(&state);
}
END_TEST

START_TEST(spawn_block_RZ) {
  GameState_t state = {0};
  init_tetris_map(&state);
  state.block = RZ_block;
  spawn_block(&state, SPAWN_POS_X);
  int arr[] = {0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
      ck_assert_int_eq(state.info->field[i + SPAWN_POS_Y][j + SPAWN_POS_X],
                       arr[i * 4 + j]);
  clear_tetris(&state);
}
END_TEST

START_TEST(spawn_block_T) {
  GameState_t state = {0};
  init_tetris_map(&state);
  state.block = T_block;
  spawn_block(&state, SPAWN_POS_X);
  int arr[] = {0, 2, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
      ck_assert_int_eq(state.info->field[i + SPAWN_POS_Y][j + SPAWN_POS_X],
                       arr[i * 4 + j]);
  clear_tetris(&state);
}
END_TEST

START_TEST(spawn_block_I) {
  GameState_t state = {0};
  init_tetris_map(&state);
  state.block = I_block;
  spawn_block(&state, SPAWN_POS_X);
  int arr[] = {0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0};
  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
      ck_assert_int_eq(state.info->field[i + SPAWN_POS_Y][j + SPAWN_POS_X],
                       arr[i * 4 + j]);
  clear_tetris(&state);
}
END_TEST

START_TEST(spawn_block_SQR) {
  GameState_t state = {0};
  init_tetris_map(&state);
  state.block = square;
  spawn_block(&state, SPAWN_POS_X);
  int arr[] = {0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
      ck_assert_int_eq(state.info->field[i + SPAWN_POS_Y][j + SPAWN_POS_X],
                       arr[i * 4 + j]);
  clear_tetris(&state);
}
END_TEST

START_TEST(left_move_true) {
  GameState_t state = {0};
  init_tetris_map(&state);
  spawn_block(&state, SPAWN_POS_X);
  try_left(&state);
  int arr[] = {0, 0, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
      ck_assert_int_eq(state.info->field[i + SPAWN_POS_Y][j + SPAWN_POS_X - 1],
                       arr[i * 4 + j]);
  clear_tetris(&state);
}
END_TEST

START_TEST(left_move_false) {
  GameState_t state = {0};
  init_tetris_map(&state);
  spawn_block(&state, SPAWN_POS_X);
  try_left(&state);
  try_left(&state);
  try_left(&state);
  int arr[] = {0, 0, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
      ck_assert_int_eq(state.info->field[i + SPAWN_POS_Y][j], arr[i * 4 + j]);
  try_left(&state);
  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
      ck_assert_int_eq(state.info->field[i + SPAWN_POS_Y][j], arr[i * 4 + j]);
  clear_tetris(&state);
}
END_TEST

START_TEST(left_move_block_false) {
  GameState_t state = {0};
  init_tetris_map(&state);
  test_spawn_block(&state, 18, 3, block, L_block, top);
  test_spawn_block(&state, 18, 6, active_block, L_block, top);
  try_left(&state);
  try_left(&state);
  try_left(&state);
  int arr[] = {0, 0, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  for (int i = 0; i < 2; ++i)
    for (int j = 0; j < 4; ++j)
      ck_assert_int_eq(state.info->field[i + 18][j + 6], arr[i * 4 + j]);
  try_left(&state);
  for (int i = 0; i < 2; ++i)
    for (int j = 0; j < 4; ++j)
      ck_assert_int_eq(state.info->field[i + 18][j + 6], arr[i * 4 + j]);
  clear_tetris(&state);
}
END_TEST

START_TEST(left_move_dop) {
  GameState_t state = {0};
  init_tetris_map(&state);
  state.block = I_block;
  spawn_block(&state, SPAWN_POS_X);
  rotate_block(&state);
  for (int i = 0; i < 6; ++i) try_left(&state);
  for (int i = 0; i < 4; ++i) ck_assert_int_eq(state.info->field[i][0], 2);
  clear_tetris(&state);
}
END_TEST

START_TEST(right_move_true) {
  GameState_t state = {0};
  init_tetris_map(&state);
  state.block = T_block;
  spawn_block(&state, SPAWN_POS_X);
  try_right(&state);
  int arr[] = {0, 2, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
      ck_assert_int_eq(state.info->field[i + SPAWN_POS_Y][j + SPAWN_POS_X + 1],
                       arr[i * 4 + j]);
  clear_tetris(&state);
}
END_TEST

START_TEST(right_move_false) {
  GameState_t state = {0};
  init_tetris_map(&state);
  state.block = T_block;
  spawn_block(&state, SPAWN_POS_X);
  try_right(&state);
  try_right(&state);
  try_right(&state);
  try_right(&state);
  int arr[] = {0, 2, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
      ck_assert_int_eq(state.info->field[i + SPAWN_POS_Y][j + SPAWN_POS_X + 4],
                       arr[i * 4 + j]);
  try_right(&state);
  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
      ck_assert_int_eq(state.info->field[i + SPAWN_POS_Y][j + SPAWN_POS_X + 4],
                       arr[i * 4 + j]);
  clear_tetris(&state);
}
END_TEST

START_TEST(right_move_block_false) {
  GameState_t state = {0};
  init_tetris_map(&state);
  state.block = T_block;
  test_spawn_block(&state, 18, 6, block, T_block, top);
  test_spawn_block(&state, 18, SPAWN_POS_X, active_block, T_block, top);
  try_right(&state);
  try_right(&state);
  try_right(&state);
  try_right(&state);
  int arr[] = {0, 2, 0, 0, 2, 2, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0};
  for (int i = 0; i < 2; ++i)
    for (int j = 0; j < 4; ++j) {
      ck_assert_int_eq(state.info->field[i + 18][j + SPAWN_POS_X],
                       arr[i * 4 + j]);
    }
  try_right(&state);
  for (int i = 0; i < 2; ++i)
    for (int j = 0; j < 4; ++j)
      ck_assert_int_eq(state.info->field[i + 18][j + SPAWN_POS_X],
                       arr[i * 4 + j]);
  clear_tetris(&state);
}
END_TEST

START_TEST(right_move_dop) {
  GameState_t state = {0};
  init_tetris_map(&state);
  state.block = I_block;
  spawn_block(&state, SPAWN_POS_X);
  rotate_block(&state);
  for (int i = 0; i < 6; ++i) try_right(&state);
  for (int i = 0; i < 4; ++i)
    ck_assert_int_eq(state.info->field[i][WINDOW_WIDTH - 1], 2);
  clear_tetris(&state);
}
END_TEST

START_TEST(down_move) {
  GameState_t state = {0};
  init_tetris_map(&state);
  spawn_block(&state, SPAWN_POS_X);
  int check = try_down(&state);
  ck_assert_int_eq(check, 0);
  clear_tetris(&state);
}
END_TEST

START_TEST(down_move_block_false) {
  GameState_t state = {0};
  init_tetris_map(&state);
  test_spawn_block(&state, 18, 3, block, L_block, top);
  test_spawn_block(&state, 16, 3, active_block, L_block, top);
  int check = try_down(&state);
  ck_assert_int_eq(check, 1);
  clear_tetris(&state);
}
END_TEST

START_TEST(down_move_and_nonactive) {
  GameState_t state = {0};
  init_tetris_map(&state);
  spawn_block(&state, SPAWN_POS_X);
  int check = 0;
  while (!check) check = try_down(&state);
  active_to_block(&state);
  ck_assert_int_eq(check, 1);
  clear_tetris(&state);
}
END_TEST

START_TEST(rotate_block_false) {
  GameState_t state = {0};
  init_tetris_map(&state);
  state.block = T_block;
  test_spawn_block(&state, 18, 3, block, T_block, top);
  test_spawn_block(&state, 16, 3, active_block, T_block, top);
  rotate_block(&state);
  int arr[] = {0, 2, 0, 0, 2, 2, 2, 0, 0, 1, 0, 0, 1, 1, 1, 0};
  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
      ck_assert_int_eq(state.info->field[i + 16][j + SPAWN_POS_X],
                       arr[i * 4 + j]);
  clear_tetris(&state);
}
END_TEST

START_TEST(rotate_down_false) {
  GameState_t state = {0};
  init_tetris_map(&state);
  state.block = T_block;
  test_spawn_block(&state, 19, 3, active_block, T_block, top);
  rotate_block(&state);
  int arr[] = {0, 2, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  for (int i = 0; i < 2; ++i)
    for (int j = 0; j < 4; ++j)
      ck_assert_int_eq(state.info->field[i + 19][j + SPAWN_POS_X],
                       arr[i * 4 + j]);
  clear_tetris(&state);
}
END_TEST

START_TEST(rotate_right_false) {
  GameState_t state = {0};
  init_tetris_map(&state);
  state.block = I_block;
  test_spawn_block(&state, 16, 8, active_block, I_block, left);
  rotate_block(&state);
  int arr[] = {0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0};
  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
      ck_assert_int_eq(state.info->field[i + 16][j + 8], arr[i * 4 + j]);
  clear_tetris(&state);
}
END_TEST

START_TEST(get_score_100) {
  GameState_t state = {0};
  init_tetris_map(&state);
  for (int i = WINDOW_HEIGHT - 1; i > WINDOW_HEIGHT - 2; --i)
    for (int j = 0; j < WINDOW_WIDTH; ++j) state.info->field[i][j] = 1;
  int check = get_score(&state);
  ck_assert_int_eq(check, 0);
  ck_assert_int_eq(state.info->score, 100);
  clear_tetris(&state);
}
END_TEST

START_TEST(get_score_300) {
  GameState_t state = {0};
  init_tetris_map(&state);
  for (int i = WINDOW_HEIGHT - 1; i > WINDOW_HEIGHT - 3; --i)
    for (int j = 0; j < WINDOW_WIDTH; ++j) state.info->field[i][j] = 1;
  int check = get_score(&state);
  ck_assert_int_eq(check, 0);
  ck_assert_int_eq(state.info->score, 300);
  clear_tetris(&state);
}
END_TEST

START_TEST(get_score_700) {
  GameState_t state = {0};
  init_tetris_map(&state);
  for (int i = WINDOW_HEIGHT - 1; i > WINDOW_HEIGHT - 4; --i)
    for (int j = 0; j < WINDOW_WIDTH; ++j) state.info->field[i][j] = 1;
  int check = get_score(&state);
  ck_assert_int_eq(check, 0);
  ck_assert_int_eq(state.info->score, 700);
  clear_tetris(&state);
}
END_TEST

START_TEST(get_score_1500) {
  GameState_t state = {0};
  init_tetris_map(&state);
  for (int i = WINDOW_HEIGHT - 1; i > WINDOW_HEIGHT - 5; --i)
    for (int j = 0; j < WINDOW_WIDTH; ++j) state.info->field[i][j] = 1;
  int check = get_score(&state);
  ck_assert_int_eq(check, 0);
  ck_assert_int_eq(state.info->score, 1500);
  clear_tetris(&state);
}
END_TEST

START_TEST(get_score_0) {
  GameState_t state = {0};
  init_tetris_map(&state);
  int check = get_score(&state);
  ck_assert_int_eq(check, 0);
  ck_assert_int_eq(state.info->score, 0);
  clear_tetris(&state);
}
END_TEST

START_TEST(get_gameover) {
  GameState_t state = {0};
  init_tetris_map(&state);
  state.info->field[1][1] = 1;
  int check = get_score(&state);
  ck_assert_int_eq(check, 1);
  ck_assert_int_eq(state.info->score, 0);
  clear_tetris(&state);
}
END_TEST

START_TEST(user_input_test_left) {
  GameState_t state = {0};
  init_tetris_map(&state);
  spawn_block(&state, SPAWN_POS_X);
  userInput(Left, true);
  int arr[] = {0, 0, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
      ck_assert_int_eq(state.info->field[i + SPAWN_POS_Y][j + SPAWN_POS_X - 1],
                       arr[i * 4 + j]);
  clear_tetris(&state);
}
END_TEST

START_TEST(user_input_test_right) {
  GameState_t state = {0};
  init_tetris_map(&state);
  spawn_block(&state, SPAWN_POS_X);
  userInput(Right, true);
  int arr[] = {0, 0, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
      ck_assert_int_eq(state.info->field[i + SPAWN_POS_Y][j + SPAWN_POS_X + 1],
                       arr[i * 4 + j]);
  clear_tetris(&state);
}
END_TEST

START_TEST(user_input_test_down) {
  GameState_t state = {0};
  init_tetris_map(&state);
  spawn_block(&state, SPAWN_POS_X);
  userInput(Down, true);
  int arr[] = {0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  for (int i = 0; i < 2; ++i)
    for (int j = 0; j < 4; ++j)
      ck_assert_int_eq(
          state.info->field[WINDOW_HEIGHT - 2 + i][j + SPAWN_POS_X],
          arr[i * 4 + j]);
  clear_tetris(&state);
}
END_TEST

START_TEST(user_input_test_rotate) {
  GameState_t state = {0};
  init_tetris_map(&state);
  spawn_block(&state, SPAWN_POS_X);
  userInput(Action, true);
  int arr[] = {2, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0};
  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
      ck_assert_int_eq(state.info->field[SPAWN_POS_Y + i][j + SPAWN_POS_X],
                       arr[i * 4 + j]);
  clear_tetris(&state);
}
END_TEST

START_TEST(user_input_test_default) {
  GameState_t state = {0};
  init_tetris_map(&state);
  spawn_block(&state, SPAWN_POS_X);
  userInput(8, true);
  clear_tetris(&state);
}
END_TEST

START_TEST(user_input_test_terminate) {
  GameState_t state = {0};
  init_tetris_map(&state);
  spawn_block(&state, SPAWN_POS_X);
  userInput(Terminate, true);
  clear_tetris(&state);
}
END_TEST

START_TEST(user_input_test_up) {
  GameState_t state = {0};
  init_tetris_map(&state);
  spawn_block(&state, SPAWN_POS_X);
  userInput(Up, true);
  clear_tetris(&state);
}
END_TEST

START_TEST(user_input_test_pause) {
  GameState_t state = {0};
  init_tetris_map(&state);
  spawn_block(&state, SPAWN_POS_X);
  userInput(Pause, true);
  clear_tetris(&state);
}
END_TEST

START_TEST(user_input_test_start) {
  GameState_t state = {0};
  init_tetris_map(&state);
  spawn_block(&state, SPAWN_POS_X);
  userInput(Start, true);
  clear_tetris(&state);
}
END_TEST

START_TEST(set_highscore) {
  GameState_t state = {0};
  init_tetris_map(&state);
  state.info->score = 2100;
  set_new_highscore(&state);
  ck_assert_int_eq(state.info->high_score, 2100);
  clear_tetris(&state);
}
END_TEST

START_TEST(set_level_1) {
  GameState_t state = {0};
  init_tetris_map(&state);
  state.info->score = 500;
  set_new_level(&state);
  ck_assert_int_eq(state.info->level, 1);
  clear_tetris(&state);
}
END_TEST

START_TEST(set_level_2) {
  GameState_t state = {0};
  init_tetris_map(&state);
  state.info->score = 700;
  set_new_level(&state);
  ck_assert_int_eq(state.info->level, 2);
  clear_tetris(&state);
}
END_TEST

START_TEST(set_level_3) {
  GameState_t state = {0};
  init_tetris_map(&state);
  state.info->score = 1700;
  set_new_level(&state);
  ck_assert_int_eq(state.info->level, 3);
  clear_tetris(&state);
}
END_TEST

START_TEST(set_level_4) {
  GameState_t state = {0};
  init_tetris_map(&state);
  state.info->score = 1800;
  set_new_level(&state);
  ck_assert_int_eq(state.info->level, 4);
  clear_tetris(&state);
}
END_TEST

START_TEST(set_level_5) {
  GameState_t state = {0};
  init_tetris_map(&state);
  state.info->score = 2500;
  set_new_level(&state);
  ck_assert_int_eq(state.info->level, 5);
  clear_tetris(&state);
}
END_TEST

START_TEST(set_level_6) {
  GameState_t state = {0};
  init_tetris_map(&state);
  state.info->score = 3500;
  set_new_level(&state);
  ck_assert_int_eq(state.info->level, 6);
  clear_tetris(&state);
}
END_TEST

START_TEST(set_level_7) {
  GameState_t state = {0};
  init_tetris_map(&state);
  state.info->score = 3600;
  set_new_level(&state);
  ck_assert_int_eq(state.info->level, 7);
  clear_tetris(&state);
}
END_TEST

START_TEST(set_level_8) {
  GameState_t state = {0};
  init_tetris_map(&state);
  state.info->score = 4300;
  set_new_level(&state);
  ck_assert_int_eq(state.info->level, 8);
  clear_tetris(&state);
}
END_TEST

START_TEST(set_level_9) {
  GameState_t state = {0};
  init_tetris_map(&state);
  state.info->score = 5399;
  set_new_level(&state);
  ck_assert_int_eq(state.info->level, 9);
  clear_tetris(&state);
}
END_TEST

START_TEST(set_level_10) {
  GameState_t state = {0};
  init_tetris_map(&state);
  state.info->score = 5400;
  set_new_level(&state);
  ck_assert_int_eq(state.info->level, 10);
  clear_tetris(&state);
}
END_TEST

START_TEST(dop_1) {
  GameState_t *state = calloc(1, sizeof(GameState_t));
  init_tetris_map(state);
  spawn_block(state, 0);
  GameInfo_t check = updateCurrentState();
  ck_assert_int_eq(state->info->high_score, check.high_score);
  ck_assert_int_eq(state->info->score, check.score);
  ck_assert_int_eq(state->info->level, check.level);
  ck_assert_int_eq(state->info->speed, check.speed);
  ck_assert_int_eq(state->info->pause, check.pause);
  ck_assert_ptr_eq(state->info->field, check.field);
  ck_assert_ptr_eq(state->info->next, check.next);
  clear_tetris(state);
  free(state);
}
END_TEST

START_TEST(dop_2) {
  block_type check = 0;
  for (int i = 0; i < 100; ++i) {
    check = get_random_block();
    ck_assert_int_le(check, 6);
    ck_assert_int_ge(check, 0);
  }
}
END_TEST

Suite *tetris_test_suite() {
  Suite *s = suite_create("\033[33mS21_TETRIS_TESTS\033[0m");
  TCase *tc = tcase_create("tetris_tc");
  tcase_add_test(tc, init_test);
  tcase_add_test(tc, spawn_block_L);
  tcase_add_test(tc, spawn_block_RL);
  tcase_add_test(tc, spawn_block_Z);
  tcase_add_test(tc, spawn_block_RZ);
  tcase_add_test(tc, spawn_block_T);
  tcase_add_test(tc, spawn_block_I);
  tcase_add_test(tc, spawn_block_SQR);
  tcase_add_test(tc, left_move_true);
  tcase_add_test(tc, left_move_false);
  tcase_add_test(tc, left_move_block_false);
  tcase_add_test(tc, left_move_dop);
  tcase_add_test(tc, right_move_true);
  tcase_add_test(tc, right_move_false);
  tcase_add_test(tc, right_move_block_false);
  tcase_add_test(tc, right_move_dop);
  tcase_add_test(tc, down_move);
  tcase_add_test(tc, down_move_block_false);
  tcase_add_test(tc, down_move_and_nonactive);
  tcase_add_test(tc, rotate_block_false);
  tcase_add_test(tc, rotate_down_false);
  tcase_add_test(tc, rotate_right_false);
  tcase_add_test(tc, get_score_100);
  tcase_add_test(tc, get_score_300);
  tcase_add_test(tc, get_score_700);
  tcase_add_test(tc, get_score_1500);
  tcase_add_test(tc, get_score_0);
  tcase_add_test(tc, get_gameover);
  tcase_add_test(tc, user_input_test_left);
  tcase_add_test(tc, user_input_test_right);
  tcase_add_test(tc, user_input_test_down);
  tcase_add_test(tc, user_input_test_rotate);
  tcase_add_test(tc, user_input_test_terminate);
  tcase_add_test(tc, user_input_test_default);
  tcase_add_test(tc, user_input_test_up);
  tcase_add_test(tc, user_input_test_pause);
  tcase_add_test(tc, user_input_test_start);
  tcase_add_test(tc, set_highscore);
  tcase_add_test(tc, set_level_1);
  tcase_add_test(tc, set_level_2);
  tcase_add_test(tc, set_level_3);
  tcase_add_test(tc, set_level_4);
  tcase_add_test(tc, set_level_5);
  tcase_add_test(tc, set_level_6);
  tcase_add_test(tc, set_level_7);
  tcase_add_test(tc, set_level_8);
  tcase_add_test(tc, set_level_9);
  tcase_add_test(tc, set_level_10);
  tcase_add_test(tc, dop_1);
  tcase_add_test(tc, dop_2);
  suite_add_tcase(s, tc);

  return s;
}