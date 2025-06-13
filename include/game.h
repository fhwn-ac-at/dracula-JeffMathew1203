#ifndef GAME_H
#define GAME_H

#include "board.h"

/**
 * @file game.h
 * @brief Game simulation functions for Snakes and Ladders.
 */

/**
 * @brief Simulate a die roll (1 to faces).
 * @param faces Number of die faces
 * @return Result of the die roll
 */
int roll_die(int faces);

/**
 * @brief Simulate a single game.
 * @param board Pointer to the board
 * @param max_steps Maximum number of steps allowed
 * @param exact_win Require exact landing on last field
 * @param out_rolls Output: number of rolls used
 * @param out_path Output: sequence of rolls
 * @param path_len Output: length of the path
 * @return 1 if the game was won, 0 otherwise
 */
int simulate_game(Board* board, int max_steps, int exact_win, int* out_rolls, int* out_path, int* path_len);

#endif
