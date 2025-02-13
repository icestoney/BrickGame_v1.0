#ifndef TEST_TETRIS
#define TEST_TETRIS

#include <check.h>

#include "../brick_game/tetris/tetris_backend.h"

Suite* tetris_test_suite();
void test_spawn_block(GameState_t* state, int y, int x, cell_state bl_state,
                      block_type bl_type, position pos);

#endif