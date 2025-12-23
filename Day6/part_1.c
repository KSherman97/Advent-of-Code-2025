#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * Author: Kyle Sherman
 * Date: 12/23/2025
 * Details:
 * 
 * Advent of Code 2025 Day 6 part 1
 * correct answer: 7,098,065,460,541
 */

int main(int argc, char *argv[]) {
    FILE *file_ptr = fopen("simplefailure.txt", "r");
    
    // failsafe file buffer
    if(file_ptr == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char line_buffer[8192];

    int col_dim = 0;
    int row_dim = 0;

    // loop through the first half of the file (this is the range of good IDs)
    // here we will handle the logic for parsing the integer ranges
    // brute force method is to get the upper and lower bounds of each line then add it to a list using
    // a loop
    while(fgets(line_buffer, sizeof(line_buffer), file_ptr) != NULL) {
        line_buffer[strcspn(line_buffer, "\n")] = '\0';
        
        char *token = strtok(line_buffer, " ");
        while(token != NULL) {
            col_dim++;
            token = strtok(NULL, " ");
        }

        row_dim++;
    }
    col_dim = col_dim / row_dim;
    rewind(file_ptr);

    long long ** math_array = calloc(row_dim, sizeof(long long *));
    math_array[0] = calloc(row_dim * col_dim, sizeof(long long));
    for(int i = 1; i < row_dim; i++) {
        math_array[i] = math_array[0] + i * col_dim; 
    }

    char **operands = calloc(col_dim, sizeof(char *));

    int index = 0;
    while(fgets(line_buffer, sizeof(line_buffer), file_ptr) != NULL) {
        line_buffer[strcspn(line_buffer, "\n")] = '\0';
        
        int column = 0;
        char *token = strtok(line_buffer, " ");
        while(token != NULL) {
            if(strcmp(token, "*") == 0 || strcmp(token, "+") == 0) {
                operands[column] = calloc(2, sizeof(char));
                strcpy(operands[column], token);
            }
            math_array[index][column] = atoll(token);
            column++;
            token = strtok(NULL, " ");
        }

        index++;
    }

    long long grand_total = 0;
    for(int column = 0; column < col_dim; column++) {
        if(operands[column] == NULL) {
            continue;
        }
        long long result = math_array[0][column];
        for(int row = 1; row < row_dim-1; row++) {
            if(strcmp(operands[column], "+") == 0) {
                result = result + math_array[row][column];
            } else {
                result = result * math_array[row][column];
            }
        }
        grand_total += result;
    }

    free(math_array[0]);
    free(math_array);
    for(int i = 0; i < col_dim; i++) {
        free(operands[i]);
    }
    free(operands);

    printf("Grand Total: %lld\n", grand_total);
    printf("Cols: %d, rows: %d\n", col_dim, row_dim);

    fclose(file_ptr);

    return 0;
}