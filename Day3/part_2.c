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
 * 
 *  
 *  part 2 solution: 172601598658203
 */
long long total_joltage_output = 0;

long long largest_possible_joltage(char *joltage_line_input) {
    // we are going to want to just brute force this
    // simplest approach is to loop throuch the entire 
    // input and store the largest in an array of index positions
    
    char search_line[strlen(joltage_line_input)+1];
    char solution_array[13];
    
    strcpy(search_line, joltage_line_input);

    int search_times = strlen(search_line);

    int remaining_picks = 12;

    int current_position = 0;
    int max_search_index = (search_times - remaining_picks);

    int counter = 0;

    while(remaining_picks > 0) {
        char best_val = '0';
        int best_pos = current_position;

        for(int i = current_position; i <= max_search_index; i++) {
            if(search_line[i] > best_val ) {
                best_val = search_line[i];
                best_pos = i;
            }
        }

        current_position = best_pos + 1;
        remaining_picks--;
        max_search_index = (search_times - remaining_picks);
        
        solution_array[counter] = best_val;

        counter++;

        // printf("%d %c\n", best_pos, best_val);
    }

    solution_array[counter] = '\0';
    // printf("\n%s\n", solution_array);


    return atoll(solution_array);

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

    printf("\ntotal combined joltage: %lld \n", total_joltage_output);

     return 0;
}