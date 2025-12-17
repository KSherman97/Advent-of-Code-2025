#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * Author: Kyle Sherman
 * Date: 12/04/2025
 * Details:
 * 
 * Advent of Code 2025 Day 4
 * 
 * Neighboring coordinates algorithm:
 * A cell in row (r) AND column (c) has the eight neighboring coords represented by:
 * 
 * Base cell: (r, c)
 * (r-1, c-1), (r-1, c), (r-1, c+1), (r, c-1), (r, c+1), (r+1, c-1), (r+1, c), (r+1, c+1)

 * PART 2 solution: 9194
 */

#define BLOCKED_LIMIT 4
#define ROLL_CHAR '@'
#define SWAP_CHAR 'x'

typedef struct {
    int x;
    int y;
} Swap_Point;

void print_grid(char **grid, int rows, int cols) {
    for(int r = 0; r < rows; r++) {
        for(int c = 0; c < cols; c++) {
            printf("%c", grid[r][c]);
        }
        printf("\n");
    }
}

int is_neighbor_blocked(char **grid, int r, int c, int rows, int cols) {
    // check bounds first(left side), then check for @ char
    return (r >= 0 && r < rows && c >= 0 && c < cols && grid[r][c] == ROLL_CHAR);
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

char **allocate_grid(int rows, int cols) {
    char **grid = malloc(rows * sizeof(char *));
    if(!grid) {
        return NULL;
    }

    for(int i = 0; i < rows; i++) {
        grid[i] = malloc(cols + 1);
        if(!grid[i]) {
            free_grid_memory(grid, i);
            return NULL;
        }
    }

    return grid;
}

/**
 * right now this is O(N^2 * iterations)
 * This could be improved by tracking only the cells that change
 * by using BFS or queue
 * generally avoiding repeated neighbor scans for unchanged cells
 * 
 * I did not have time to implement these however.
 * I estimate this could be improved to O(N^2)
 */
int search_grid(char **grid, int row_count, int col_count) { 
    int accessible_total = 0;
    int max_points = row_count * col_count;

    Swap_Point *swap_points = malloc(max_points * sizeof(Swap_Point));
    if(!swap_points) {
        perror("unable to allocate memory for swap points");
        exit(1);
    }

    int removable_roll_count = 0;

    // these nested loops could probably be replaced using a static offset table
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

            if(grid[r][c] == ROLL_CHAR && blocker_count < BLOCKED_LIMIT) {
                swap_points[removable_roll_count].y = r;
                swap_points[removable_roll_count].x = c;
                removable_roll_count++;
                accessible_total++;
            }
        }
    }

    for(int i = 0; i < removable_roll_count; i++) {
        int grid_row_point = swap_points[i].y;
        int grid_col_point = swap_points[i].x;

        grid[grid_row_point][grid_col_point] = SWAP_CHAR;
    }

    free(swap_points);

    if(accessible_total == 0) {
        return -1;
    } else {
        return accessible_total;
    }
}

int main(int argc, char *argv[]) {
    FILE *file_ptr;
    file_ptr = fopen("simpleinput.txt", "r");
    if(file_ptr == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char **grid;
    int row_count = 0;
    int col_count = 0;

    char line_buffer[256];

    // read file buffer and then loop through storing the result in an array
    while(fgets(line_buffer, sizeof(line_buffer), file_ptr) != NULL) {
        line_buffer[strcspn(line_buffer, "\n")] = '\0';
        int line_len = strcspn(line_buffer, "\n");

        if(line_len > col_count) {
            col_count = line_len;
        }

        row_count++;
    }

    grid = allocate_grid(row_count, col_count);

    rewind(file_ptr);

    int row_index = 0;
    while(fgets(line_buffer, sizeof(line_buffer), file_ptr) != NULL) {
        strncpy(grid[row_index], line_buffer, col_count);
        grid[row_index][col_count] = '\0'; 

        row_index++;
    }

    int total_removed = 0;
    int accessible = 0;
    while(accessible >= 0) {
        accessible = search_grid(grid, row_count, col_count);
        if(accessible > 0) {
            total_removed += accessible;
        }
        print_grid(grid, row_count, col_count);
        printf("\nremoved: %d\n\n", accessible);
    }

    printf("Accessible rolls of paper: %d\n", total_removed);

    fclose(file_ptr);
    free_grid_memory(grid, row_count);
    grid = NULL;

    return 0;
}
