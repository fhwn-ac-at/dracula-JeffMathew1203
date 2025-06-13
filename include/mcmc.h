#ifndef MCMC_H
#define MCMC_H

#include "board.h"

/**
 * @file mcmc.h
 * @brief Monte Carlo simulation for Snakes and Ladders.
 */

/**
 * @brief Stores the result of a simulation.
 */
typedef struct {
    double avg_rolls;         /**< Average rolls to win */
    int min_rolls;            /**< Minimum rolls needed to win */
    int min_sequence[1024];   /**< Shortest winning roll sequence */
    int* snake_freq;          /**< Frequency of each snake used */
    int* ladder_freq;         /**< Frequency of each ladder used */
    int games_won;            /**< Number of games won */
    int games_failed;         /**< Number of games failed */
} SimulationResult;

/**
 * @brief Run a Monte Carlo simulation.
 * @param board Pointer to the board
 * @param runs Number of simulation runs
 * @param max_steps Maximum steps per game
 * @param exact_win Require exact landing on last field
 * @return SimulationResult structure with statistics
 */
SimulationResult run_simulation(Board* board, int runs, int max_steps, int exact_win);

/**
 * @brief Print the simulation result.
 * @param res Pointer to the SimulationResult
 * @param board Pointer to the board
 */
void print_simulation_result(SimulationResult* res, Board* board);

/**
 * @brief Free resources used by the simulation result.
 * @param res Pointer to the SimulationResult
 */
void free_simulation_result(SimulationResult* res);

#endif
