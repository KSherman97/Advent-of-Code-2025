#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * Author: Kyle Sherman
 * Date: 12/04/2025
 * Details:
 * 
 * Advent of Code 2025 Day 4
 * In this problem we are going to be searching through a grid. Within this grid we will check each position that contains an @ to see if it is accessible
 * Accessibility is determined by the diagonal and orthoganal positions (up, down, left, right, diagonal)
 * of the 8 adjacent positions, no more than 4 can have an @.
 * 
 * 
 * 
 * Neighboring coordinates algorithm:
 * A cell in row (r) AND column (c) has the eight neighboring coords represented by:
 * 
 * Base cell: (r, c)
 * (r-1, c-1), (r-1, c), (r-1, c+1), (r, c-1), (r, c+1), (r+1, c-1), (r+1, c), (r+1, c+1)
 * 
 * Should also check bounds to ensure coordinates remain in the grid dimmensions
 * for each position we can have a counter to determine the number of blocked paths, and if the space is clear then we can append a global counter
 * note: neighbor_count < 4.
 * 
 * Therefore, for any (r, c) in the grid, a roll of paper at this point is accessible if and only if the number of neighboring rolls (@) is less than four.
 *
 * PART 1 solution: Accessible rolls of paper: 1493
 * 
 */

#define BLOCKED_LIMIT 4

int is_neighbor_blocked(char **grid, int r, int c, int rows, int cols) {
    // check bounds first(left side), then check for @ char
    return (r >= 0 && r < rows && c >= 0 && c < cols && grid[r][c] == '@');
}

void free_grid_memory(char **grid, int row_count) {
    if(grid == NULL) {
        return;
    }

    for(int i = 0; i < row_count; i++) {
        if(grid[i] != NULL) {
            free(grid[i]);
        }
    }

    free(grid);
}

int main(int argc, char *argv[]) {
    FILE *file_ptr;
    char line_buffer[256];

    int row_count = 0;
    int col_count = 0;

    int accessible_total = 0;

    char **grid;

    // open the file in read mode ("r")
    file_ptr = fopen("simpleinput.txt", "r");

    // failsafe file buffer
    if(file_ptr == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // read file buffer and then loop through storing the result in an array
    while(fgets(line_buffer, sizeof(line_buffer), file_ptr) != NULL) {
        line_buffer[strcspn(line_buffer, "\n")] = '\0';
        col_count = strlen(line_buffer);
        row_count++;
    }

    grid = (char **)malloc(row_count * sizeof(char *));

    if(grid == NULL) {
        printf("memory allocation failed for rows\n");
        free(grid);
        return 1;
    }

    for (int i = 0; i < row_count; i++) {
        grid[i] = (char *)malloc((col_count+1) * sizeof(char));

        if(grid[i] == NULL) {
            printf("Memory allocation failed for cols at row %d", i);

            free_grid_memory(grid, i);

            return 1;
        }
    }

    rewind(file_ptr);

    int row_index = 0;
    while(fgets(line_buffer, sizeof(line_buffer), file_ptr) != NULL) {
        strncpy(grid[row_index], line_buffer, col_count);
        grid[row_index][col_count] = '\0'; 

        row_index++;
    }

    // this is our grid checker
    /**
     * Base cell: (r, c)
     * (r-1, c-1), (r-1, c), (r-1, c+1), (r, c-1), (r, c+1), (r+1, c-1), (r+1, c), (r+1, c+1)
     */
    for(int r = 0; r < row_count; r++) {
        for(int c = 0; c < col_count; c++) {
            int blocker_count = 0;

            for(int row_offset = -1; row_offset <= 1; row_offset++) {
                for(int col_offset = -1; col_offset <= 1; col_offset++) {
                    //skip our base cell
                    if(row_offset == 0 && col_offset == 0) {
                        continue;
                    }

                    int neighbor_row = r + row_offset; // neighbor row index
                    int neighbor_col = c + col_offset; // neighbor column index

                    if(is_neighbor_blocked(grid, neighbor_row, neighbor_col, row_count, col_count)) {
                        blocker_count++;
                    }
                }
            }

            if(grid[r][c] == '@' && blocker_count < BLOCKED_LIMIT) {
                accessible_total++;
            }
        }
    }

    printf("Accessible rolls of paper: %d\n", accessible_total);

    fclose(file_ptr);

    free_grid_memory(grid, row_count);

    grid = NULL;

     return 0;
}