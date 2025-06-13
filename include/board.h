#ifndef BOARD_H
#define BOARD_H

/**
 * @file board.h
 * @brief Board structure and functions for Snakes and Ladders game.
 */

/**
 * @brief Represents a jump (snake or ladder) on the board.
 */
typedef struct {
    int start; /**< Start position of the jump */
    int end;   /**< End position of the jump */
} Jump;

/**
 * @brief Represents the game board.
 */
typedef struct {
    int size;        /**< Total number of fields (rows * cols) */
    int rows;        /**< Number of rows */
    int cols;        /**< Number of columns */
    int die_faces;   /**< Number of faces on the die */
    Jump* snakes;    /**< List of snakes */
    int snake_count; /**< Number of snakes */
    Jump* ladders;   /**< List of ladders */
    int ladder_count;/**< Number of ladders */
} Board;

/**
 * @brief Create a new board.
 * @param rows Number of rows
 * @param cols Number of columns
 * @param die_faces Number of die faces
 * @return Pointer to the created Board
 */
Board* create_board(int rows, int cols, int die_faces);

/**
 * @brief Add a snake to the board.
 * @param board Pointer to the board
 * @param start Start position of the snake
 * @param end End position of the snake
 */
void add_snake(Board* board, int start, int end);

/**
 * @brief Add a ladder to the board.
 * @param board Pointer to the board
 * @param start Start position of the ladder
 * @param end End position of the ladder
 */
void add_ladder(Board* board, int start, int end);

/**
 * @brief Generate random snakes and ladders.
 * @param board Pointer to the board
 * @param num_ladders Number of ladders to generate
 * @param num_snakes Number of snakes to generate
 */
void generate_random_jumps(Board* board, int num_ladders, int num_snakes);

/**
 * @brief Apply jumps (snakes or ladders) to a position.
 * @param board Pointer to the board
 * @param pos Current position
 * @return New position after applying jump
 */
int apply_jumps(Board* board, int pos);

/**
 * @brief Free all resources used by the board.
 * @param board Pointer to the board
 */
void free_board(Board* board);

#endif
