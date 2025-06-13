#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"
#include "game.h"
#include "mcmc.h"

#define RED   "\033[31m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"

/**
 * Expected configuration file format:
 *
 * <rows> <cols> <die_faces>
 * <num_ladders>
 * <num_snakes>
 * <num_simulations>
 *
 * Example:
 * 10 10 6
 * 5
 * 4
 * 10000
 */

// Loads configuration from file and creates the board
Board* load_board_config(const char* filename, int* out_simulations) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        perror("Failed to open config file");
        return NULL;
    }

    int rows, cols, die_faces;
    int ladders, snakes;

    // Read base parameters
    fscanf(f, "%d %d %d", &rows, &cols, &die_faces);
    fscanf(f, "%d", &ladders);
    fscanf(f, "%d", &snakes);
    fscanf(f, "%d", out_simulations);

    fclose(f);

    // Create board
    Board* board = create_board(rows, cols, die_faces);

    // Generate random positions for snakes and ladders
    generate_random_jumps(board, ladders, snakes);

    return board;
}

void render_board(Board* board) {
    printf("\n\033[1m===== Game Board =====\033[0m\n");
    for (int r = board->rows - 1; r >= 0; r--) {
        for (int c = 0; c < board->cols; c++) {
            int i = r * board->cols + (r % 2 == 0 ? c : (board->cols - 1 - c)) + 1;
            int is_snake = 0, is_ladder = 0;
            for (int s = 0; s < board->snake_count; s++)
                if (board->snakes[s].start == i) is_snake = board->snakes[s].end;
            for (int l = 0; l < board->ladder_count; l++)
                if (board->ladders[l].start == i) is_ladder = board->ladders[l].end;
            if (is_snake)
                printf("%s[%2d→%2d]%s ", RED, i, is_snake, RESET);
            else if (is_ladder)
                printf("%s[%2d→%2d]%s ", YELLOW, i, is_ladder, RESET);
            else
                printf("[%5d] ", i);
        }
        printf("\n");
    }
    printf("\033[1m=======================\033[0m\n\n");
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <config_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    srand((unsigned)time(NULL)); // Only seed once, here!

    int num_simulations = 0; // Will be set by load_board_config

    // Read configuration and create board
    Board* board = load_board_config(argv[1], &num_simulations);
    if (!board) return EXIT_FAILURE;
    render_board(board);

    // Run simulation
    SimulationResult res = run_simulation(board, num_simulations, 1000, 1);

    // Print results
    print_simulation_result(&res, board);

    // Clean up resources
    free_simulation_result(&res);
    free_board(board);

    return EXIT_SUCCESS;
}
