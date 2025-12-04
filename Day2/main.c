#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

/**
 * Author: Kyle Sherman
 * Date: 12/02/2025
 * Details:
 * 
 * Advent of Code 2025 Day 2
 * 
 * We are given a series of product ID ranges in a CSV format
 * NOTE: all on one line, so no checking for newline char
 * 
 * we should be able to check just the first 4 characters (part 1 at least)
 * problem says that any ID where character 1&2 are matches with 2&3 then we have an invalid ID
 * 
 * there are a few cases:
 * the value in the range must be an even length in order to be invalid
 * we can split each item in the range in half and compare each one to determine if it is invalid
 * we can then store each invalid number into an array to add at the end
 * 
 * for part two it is important to check every possible pattern length from l = 1 to l = 1/2 length
 * this yields a complexity of O(N*L^2)
 * the solution grows linearly with respect to the number of items we are searching but then
 * quadratic with respect to the length of each search
 *  
 */
long long rolling_total = 0;

void search_range(char *low, char *high) {
    long long low_val = atoll(low);
    long long high_val = atoll(high);

    char value_string[100];

    for(long long i = low_val; i <= high_val; i++) {
        sprintf(value_string, "%lld", i);

        int length = strlen(value_string);
        // int mid_point = length / 2;

        // for all other cases
        // possible pattern lengths are 1 through len / 2
        for(int j = 1; j <= length / 2; j++) {
            if((length % j) == 0) {
                // int number_of_parts = length / j;
                // printf("parts: %d\n", number_of_parts);
                char base_pattern[100];
                strncpy(base_pattern, value_string, j);
                base_pattern[j] = '\0';

                int match_found = 1;

                for(int k = j; k < length; k+= j) {
                    if(strncmp(value_string + k, base_pattern, j) != 0) {
                        match_found = 0;
                        break;
                    }
                }

                if(match_found) {
                    rolling_total += i;
                    break;
                }
            }
        }
    }
}

int main(int argc, char *argv[]) {
    FILE *file_ptr;
    char buffer[2048];
    char *token;
    char *outer_ptr = NULL;
    char *inner_ptr = NULL;

    char *low = 0;
    char *high = 0;

    int count = 0;

    // open the file in read mode ("r")
    // file_ptr = fopen("simpleinput.txt", "r");
    file_ptr = fopen("input.txt", "r");

    // failsafe file buffer
    if(file_ptr == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // read file buffer and then loop through storing the result in an array
    while(fgets(buffer, sizeof(buffer), file_ptr) != NULL) {
        // strip trailing newline char if it is present
        buffer[strcspn(buffer, "\n")] = 0;

        // get the first token
        token = strtok_r(buffer, ",", &outer_ptr);

        // loop through every token until returns null
        while(token != NULL) { 
            char *range_token = strtok_r(token, "-", &inner_ptr);

            while(range_token != NULL) {
                // printf("%s", range_token);
                if(count == 0) {
                    low = range_token;
                    count++;
                } else if(count == 1) {
                    high = range_token;
                    count = 0;
                } else {
                    count = 0;
                }
                range_token = strtok_r(NULL, "-", &inner_ptr);
            }
            search_range(low, high);
            low = "\0";
            high = "\0";
            count = 0;

            token = strtok_r(NULL, ",", &outer_ptr);
        }
    }

    fclose(file_ptr);

    printf("Value of invalid Ids: %lld \n\r", rolling_total);

     return 0;
}