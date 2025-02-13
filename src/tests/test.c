#include "test.h"

void test_spawn_block(GameState_t *state, int y, int x, cell_state bl_state,
                      block_type bl_type, position pos) {
  int strnum = 2 + (pos % 2 * 2);
  for (int i = 0; i < strnum; ++i)
    for (int j = 0; j < 4; ++j)
      state->info->field[i + y][j + x] =
          (block_state[bl_type][pos][i * 4 + j] == active_block)
              ? bl_state
              : (cell_state)state->info->field[i + y][j + x];
  if (bl_state == active_block) {
    state->rect.x1 = x;
    state->rect.x2 = x + 3;
    state->rect.y1 = y;
    state->rect.y2 = (y + 3) > 20 ? ((y + 3) - ((y + 3) % 20)) : (y + 3);
    state->rect.pos = pos;
    state->block = bl_type;
  }
}

int main() {
  int failed = 0;
  int total = 0;
  Suite *s21_tetris_test[] = {tetris_test_suite(), NULL};

  for (int i = 0; s21_tetris_test[i] != NULL; ++i) {
    SRunner *sr = srunner_create(s21_tetris_test[i]);
    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);
    failed += srunner_ntests_failed(sr);
    total += srunner_ntests_run(sr);
    srunner_free(sr);
    ++total;
  }
  --total;
  printf("========== TOTAL TESTS : %3d ==========\n", total);
  printf("========== \033[32mTEST SUCCESS: %3d\033[0m ==========\n",
         total - failed);
  printf("========== \033[31mTESTS FAILED: %3d\033[0m ==========\n", failed);
  return 0;
}
