#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

/**
 *  Author: Kyle Sherman
 *  Date: 12/03/2025
 *  Details:
 * 
 *  Advent of Code 2025 Day 3
 */
long long total_joltage_output = 0;

int largest_possible_joltage(char *joltage_line_input) {
    int line_length = strlen(joltage_line_input);
    
    int first_index = 0;

    // loop number one finds the largest overall position
    for(int i = 0; i < line_length-1; i++) {
        if(joltage_line_input[i] > joltage_line_input[first_index]) {
            first_index = i;
        }
    }

    int second_index = first_index + 1;
    // loop to find the second largest overall position
    for(int j = second_index; j < line_length; j++) {
        if(j != first_index && joltage_line_input[j] > joltage_line_input[second_index]) {
            second_index = j;
        }
    }

    int result = (joltage_line_input[first_index] - '0') * 10 + (joltage_line_input[second_index] - '0');

    /// printf("result: %d \n", result);

    return result;
}

int main(int argc, char *argv[]) {
    FILE *input_file_ptr;
    char line_buffer[2048];
    char *line_token;

    // input_file_ptr = fopen("simpleinput.txt", "r");
    input_file_ptr = fopen("input.txt", "r");

    if(input_file_ptr == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // read file buffer and then loop through storing the result in an array
    while(fgets(line_buffer, sizeof(line_buffer), input_file_ptr) != NULL) {
        // strip trailing newline char if it is present
        line_buffer[strcspn(line_buffer, "\n")] = 0;

        // get the first token
        line_token = strtok(line_buffer, "\0");
        line_token[strlen(line_token)] = '\0';

        // loop through every token until returns null
        while(line_token != NULL) { 

            total_joltage_output += largest_possible_joltage(line_token);
            
            line_token = strtok(NULL, "\n");
        }
    }

    fclose(input_file_ptr);

    printf("\n\ntotal combined joltage: %lld \n", total_joltage_output);

     return 0;
}