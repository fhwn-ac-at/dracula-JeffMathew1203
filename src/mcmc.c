#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "mcmc.h"
#include "game.h"

// Runs multiple simulations and collects statistics about wins, losses, and usage of snakes/ladders
SimulationResult run_simulation(Board* board, int runs, int max_steps, int exact_win) {
    SimulationResult result = {0};
    result.snake_freq = calloc(board->size + 1, sizeof(int));   // Track snake usage
    result.ladder_freq = calloc(board->size + 1, sizeof(int));  // Track ladder usage
    result.games_won = 0;
    result.games_failed = 0;

    int total_rolls = 0;
    result.min_rolls = INT_MAX;

    int rolls, path[1024], len;

    for (int i = 0; i < runs; i++) {
        // Simulate a single game
        int won = simulate_game(board, max_steps, exact_win, &rolls, path, &len);
        if (won) {
            result.games_won++;
            total_rolls += rolls;
            // Store shortest win sequence
            if (rolls < result.min_rolls) {
                result.min_rolls = rolls;
                memcpy(result.min_sequence, path, len * sizeof(int));
            }
        } else {
            result.games_failed++;
        }

        // Count how often each snake and ladder is used
        for (int j = 0, pos = 0; j < len; j++) {
            pos += path[j];
            for (int s = 0; s < board->snake_count; s++) {
                if (board->snakes[s].start == pos)
                    result.snake_freq[pos]++;
            }
            for (int l = 0; l < board->ladder_count; l++) {
                if (board->ladders[l].start == pos)
                    result.ladder_freq[pos]++;
            }
            pos = apply_jumps(board, pos);
        }
    }

    // Calculate average rolls for wins
    result.avg_rolls = result.games_won > 0 ? (double)total_rolls / result.games_won : 0.0;
    return result;
}

// Prints the collected simulation statistics
void print_simulation_result(SimulationResult* res, Board* board) {
    printf("===== Simulation Result =====\n");
    printf("Games won: %d\n", res->games_won);
    printf("Games failed: %d\n", res->games_failed);
    if (res->games_won > 0) {
        printf("Average rolls to win: %.2f\n", res->avg_rolls);
        printf("Shortest win in %d rolls: ", res->min_rolls);
        for (int i = 0; i < res->min_rolls; i++) {
            printf("%d ", res->min_sequence[i]);
        }
        printf("\n");
    } else {
        printf("No games were won. The board may be unsolvable.\n");
    }

    // Print snake usage statistics
    printf("\n-- Snake Usage --\n");
    for (int i = 0; i <= board->size; i++) {
        if (res->snake_freq[i] > 0)
            printf("Snake at %d used %d times\n", i, res->snake_freq[i]);
    }

    // Print ladder usage statistics
    printf("\n-- Ladder Usage --\n");
    for (int i = 0; i <= board->size; i++) {
        if (res->ladder_freq[i] > 0)
            printf("Ladder at %d used %d times\n", i, res->ladder_freq[i]);
    }
}

// Frees memory allocated for simulation results
void free_simulation_result(SimulationResult* res) {
    free(res->snake_freq);
    free(res->ladder_freq);
}
