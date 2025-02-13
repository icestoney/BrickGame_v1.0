/**
 * @file tetris_backend.h
 * @author shericen
 * @brief A header file containing 4 standard libraries (stdbool.h, stdio.h,
 * stdlib.h, time.h), macros, structures, a three-dimensional array and the
 * declaration of all functions.
 * @date 2024-07-07
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef TETRIS
#define TETRIS
/**
 * @brief The width of the playing field.
 */
#define WINDOW_WIDTH 10

/**
 * @brief The height of the playing field.
 */
#define WINDOW_HEIGHT 21

/**
 * @brief X coordinate of the spawn block.
 */
#define SPAWN_POS_X 3

/**
 * @brief Y coordinate of the spawn block.
 */
#define SPAWN_POS_Y 0

/**
 * @brief The file where the highest score is recorded.
 */
#define FILE_SCORE "./game_info/highscore_list.txt"

/**
 * @brief Memory allocation error code.
 */
#define BAD_ALLOC 1

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * @brief Enum with possible user action.
 */
typedef enum UserAction_t {
  Start,     /**< Start action.*/
  Pause,     /**< Pause action.*/
  Terminate, /**< Terminate action.*/
  Left,      /**< Left move action.*/
  Right,     /**< Right move action.*/
  Up,        /**< Nothing.*/
  Down,      /**< Drop down action.*/
  Action     /**< Rotate action.*/
} UserAction_t;

/**
 * @brief Enum with all block types of tetris.
 */
typedef enum block_type {
  L_block,          /**< L type block.*/
  I_block,          /**< I type block.*/
  T_block,          /**< T type block.*/
  square,           /**< Square type block.*/
  Z_block,          /**< Z type block.*/
  RL_block,         /**< Right L type block.*/
  RZ_block,         /**< Right Z type block.*/
  Transparent_block /**< Transparent type block for start.*/
} block_type;

/**
 * @brief Enum with all types of game cell state.
 */
typedef enum cell_state {
  empty,       /**< Empty cell of field.*/
  block,       /**< Cell with static block.*/
  active_block /**< Cell with active block.*/
} cell_state;

/**
 * @brief Enum with all types of block positions.
 */
typedef enum position {
  top,    /**< Top position of block.*/
  left,   /**< Left position of block.*/
  bottom, /**< Bottom position of block.*/
  right   /**< Right position of block.*/
} position;

/**
 * @brief Structure with main game info (playing field, next block, score,
 * highest score, level, speed, pause).
 */
typedef struct GameInfo_t {
  int** field;    /**< Main tetris playing field.*/
  int** next;     /**< The field where the next block is specified.*/
  int score;      /**< Contains current score.*/
  int high_score; /**< Contains best score of all games.*/
  int level;      /**< Contains difficult of game.*/
  int speed;      /**< The time it takes for a block to drop by 1 unit.*/
  int pause;      /**< Status of pause game.*/
} GameInfo_t;

/**
 * @brief Structure which contains 2 point of rectangle shape and position of
 * block inside the rectangle.
 */
typedef struct Rectangle_t {
  int x1;       /**< X coordinate of the upper left corner of the rectangle.*/
  int x2;       /**< X coordinate of the lower right corner of the rectangle.*/
  int y1;       /**< Y coordinate of the upper left corner of the rectangle.*/
  int y2;       /**< Y coordinate of the lower right corner of the rectangle.*/
  position pos; /**< The position of the block inside the rectangle.*/
} Rectangle_t;

/**
 * @brief Structure with all info for game map.
 */
typedef struct GameState_t {
  GameInfo_t*
      info; /**< Contains game map, score, level, speed and highscore of game.*/

  /**Current active block.*/
  block_type block;

  /**Next spawn block, when active block get down.*/
  block_type next_block;

  /**Contains position of current active block.*/
  Rectangle_t rect;

  /**Just pressed down.*/
  bool is_downed;

  /**No block yet spawned.*/
  bool empty_active_block;
} GameState_t;

/**
 * @brief Make action from user input.
 * @param action Current player action.
 * @param hold Contain active user hold.
 */
void userInput(UserAction_t action, bool hold);

/**
 * @brief Update current game state.
 * @return Info about current game state.
 */
GameInfo_t updateCurrentState();

/**
 * @brief Initialisation tetris map.
 */
void init_tetris_map(GameState_t* state);

/**
 * @brief Moves active block in left if is no obstacle.
 * @param state Current game state.
 */
void try_left(GameState_t* state);

/**
 * @brief Moves active block in right if is no obstacle.
 * @param state Current game state.
 */
void try_right(GameState_t* state);

/**
 * @brief Moves active block down if is no obstacle.
 * @param state Current game state.
 * @return 0 if downward movement is possible, 1 if downward movement is
 * impossible.
 * @return
 */
int try_down(GameState_t* state);

/**
 * @brief Rotate active block on 90 degrees.
 * @param state Current game state.
 */
void rotate_block(GameState_t* state);

/**
 * @brief Delete all dynamic objects.
 * @param state Current game state.
 */
void clear_tetris(GameState_t* state);

/**
 * @brief Break full lines and update game score.
 * @param state Current game state.
 * @return 0 if the game is in progress, 1 if the game is over.
 */
int get_score(GameState_t* state);

/**
 * @brief Delete specified line.
 * @param state Current game state.
 * @param line Y coordinate of the line to be deleted.
 */
void delete_line(GameState_t* state, int line);

/**
 * @brief Turns all active blocks into static ones.
 * @param state Current game state
 */
void active_to_block(GameState_t* state);

/**
 * @brief Set new highscore, if score > highscore.
 * @param state Current game state.
 */
void set_new_highscore(GameState_t* state);

/**
 * @brief Set new level depending on points scored.
 * @param state Current game state.
 */
void set_new_level(GameState_t* state);

/**
 * @brief Set new game state or return current game state if *state == NULL.
 * @param state Current game state.
 * @return Current game state.
 */
GameState_t* get_set_current_map(GameState_t* state);

/**
 * @brief Get the random type of block.
 * @return Block type.
 */
block_type get_random_block();

/**
 * @brief Chooses block state.
 * @param buf Where to save new block state.
 * @param bt Block type.
 * @param pos Block position.
 * @param spawn_pos_x X coordinate for spawn position.
 */
void choose_block_state(int** buf, block_type bt, position pos,
                        int spawn_pos_x);

/**
 * @brief Spawns a new block.
 * @param state Current game state.
 * @param spawn_pos_x X coordinate for spawn position.
 */
void spawn_block(GameState_t* state, int spawn_pos_x);

/**
 * @brief Safe memory allocation.
 * @param number Number of memory blocks.
 * @param size Memory block size.
 * @return void pointer.
 */
void* s21_calloc(size_t number, const size_t size);

/**
 * @brief Safe matrix memory allocation.
 * @param y Number of rows.
 * @param x Number of columns.
 * @return int** pointer.
 */
int** s21_calloc_matrix(const size_t y, const size_t x);

/**
 * @brief Safe matrix memory release.
 * @param matrix Matrix pointer.
 * @param r_size Number of rows.
 */
void free_matrix(int** matrix, int r_size);

/**
 * @brief Contains shape of all blocks and their rotations. This file-scope
 * variable is used to initialize and block modifying in specified order.
 */
static const int block_state[8][4][16] = {
    /*L_block*/
    {{0, 0, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {2, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0},
     {2, 2, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {2, 0, 0, 0, 2, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0}},
    /*I_block*/
    {{0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0},
     {0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0}},
    /*T_block*/
    {{0, 2, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 2, 0, 0, 2, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0},
     {2, 2, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 2, 0, 0, 0, 2, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0}},
    /*square*/
    {{0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 2, 2, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    /*Z_block*/
    {{2, 2, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 2, 0, 0, 2, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0},
     {2, 2, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 2, 0, 0, 2, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0}},
    /*RL_block*/
    {{2, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 2, 0, 0, 0, 2, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0},
     {2, 2, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {2, 2, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0}},
    /*RZ_block*/
    {{0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {2, 0, 0, 0, 2, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0},
     {0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {2, 0, 0, 0, 2, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0}},
    /*Transparent_block*/
    {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}};

#endif