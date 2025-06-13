#include <stdio.h>
#include <stdlib.h>
#include "board.h"

Board* create_board(int rows, int cols, int die_faces) {
    Board* board = malloc(sizeof(Board));
    board->rows = rows;
    board->cols = cols;
    board->size = rows * cols; // Field 0 is start, size is last field
    board->die_faces = die_faces;
    board->snake_count = 0;
    board->ladder_count = 0;
    board->snakes = malloc(100 * sizeof(Jump));
    board->ladders = malloc(100 * sizeof(Jump));
    return board;
}

static int is_conflict(Board* board, int start, int end) {
    // No snake or ladder can start or end at the same field
    for (int i = 0; i < board->ladder_count; i++)
        if (board->ladders[i].start == start || board->ladders[i].end == end)
            return 1;
    for (int i = 0; i < board->snake_count; i++)
        if (board->snakes[i].start == start || board->snakes[i].end == end)
            return 1;
    return 0;
}

void add_snake(Board* board, int start, int end) {
    board->snakes[board->snake_count++] = (Jump){start, end};
}

void add_ladder(Board* board, int start, int end) {
    board->ladders[board->ladder_count++] = (Jump){start, end};
}

/**
 * @brief Checks if there are 6 consecutive snake starts including the given start.
 */
static int would_create_six_snakes(Board* board, int start) {
    int count = 1;
    // Check backwards
    for (int i = 1; i < 6; ++i) {
        int found = 0;
        for (int j = 0; j < board->snake_count; ++j) {
            if (board->snakes[j].start == start - i) {
                found = 1;
                break;
            }
        }
        if (found) count++;
        else break;
    }
    // Check forwards
    for (int i = 1; i < 6; ++i) {
        int found = 0;
        for (int j = 0; j < board->snake_count; ++j) {
            if (board->snakes[j].start == start + i) {
                found = 1;
                break;
            }
        }
        if (found) count++;
        else break;
    }
    return count >= 6;
}

void generate_random_jumps(Board* board, int num_ladders, int num_snakes) {
    int max_pos = board->size - 1;

    // Generate ladders: start < end, not on last field
    while (board->ladder_count < num_ladders) {
        int start = rand() % (max_pos - 1) + 1;
        int end = rand() % (max_pos - start) + start + 1;
        if (start >= end) continue;
        if (start == max_pos) continue; // No ladder starts on last field
        if (is_conflict(board, start, end)) continue;
        add_ladder(board, start, end);
    }

    // Generate snakes: start > end, not on last field, no 6 in a row
    while (board->snake_count < num_snakes) {
        int start = rand() % (max_pos - 1) + 2;
        int end = rand() % (start - 1) + 1;
        if (start <= end) continue;
        if (start == max_pos) continue; // No snake on last field
        if (is_conflict(board, start, end)) continue;
        if (would_create_six_snakes(board, start)) continue;
        add_snake(board, start, end);
    }
}

int apply_jumps(Board* board, int pos) {
    for (int i = 0; i < board->ladder_count; i++)
        if (board->ladders[i].start == pos) return board->ladders[i].end;
    for (int i = 0; i < board->snake_count; i++)
        if (board->snakes[i].start == pos) return board->snakes[i].end;
    return pos;
}

void free_board(Board* board) {
    free(board->snakes);
    free(board->ladders);
    free(board);
}
