#include <stdio.h>
#include <stdlib.h>
#include "game.h"

int roll_die(int faces) {
    return rand() % faces + 1;
}

int simulate_game(Board* board, int max_steps, int exact_win, int* out_rolls, int* out_path, int* path_len) {
    int pos = 0;
    int rolls = 0;
    int step;

    *path_len = 0;

    while (rolls < max_steps) {
        step = roll_die(board->die_faces);
        out_path[*path_len] = step;
        (*path_len)++;

        if (pos + step > board->size) {
            // If exact_win is required, skip move if it overshoots
            if (exact_win) {
                rolls++;
                continue;
            } else {
                pos = board->size;
            }
        } else {
            pos += step;
            pos = apply_jumps(board, pos);
        }
        rolls++;
        if (pos == board->size) break;
    }

    *out_rolls = rolls;

    if (pos != board->size) {
        fprintf(stderr, "Error: Game did not finish after %d steps. Possible infinite loop or unsolvable board.\n", max_steps);
        return 0;
    }
    return 1;
}
