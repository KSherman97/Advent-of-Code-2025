#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * Author: Kyle Sherman
 * Date: 12/16/2025
 * Details:
 * 
 * Advent of Code 2025 Day 5
 */

typedef struct {
    long long start;
    long long end;
} Range;

Range fresh_id_ranges[200];
int range_count = 0;

int result_counter = 0;

void add_range(long long lower, long long upper) {
    fresh_id_ranges[range_count].start = lower;
    fresh_id_ranges[range_count].end = upper;
    range_count++;
}

void parse_fresh_id_range(char *range_string) {
    char lower_bound[50];
    char upper_bound[50];

    int status = 0;
    int pointer = 0;
    for(int i = 0; i < strlen(range_string); i++) {
        if(range_string[i] == '-') {
            status = 1;
            pointer = 0;
            continue;
        }

        if(status == 0) {
            lower_bound[i] = range_string[i];
        } else if(status == 1) {
            upper_bound[pointer] = range_string[i];
        }

        pointer++;
    }

    lower_bound[strlen(lower_bound)] = '\0';
    upper_bound[strlen(upper_bound)] = '\0';

    add_range(atoll(lower_bound), atoll(upper_bound));
}

int fresh_id_check(long long ingredient_id) {
    for(int i = 0; i < range_count; i++) {
        if(ingredient_id >= fresh_id_ranges[i].start &&
        ingredient_id <= fresh_id_ranges[i].end) {
            return 1;
        }
    }

    return 0;
}

int main(int argc, char *argv[]) {
    FILE *file_ptr;
    char line_buffer[256];

    // open the file in read mode ("r")
    file_ptr = fopen("simpleinput.txt", "r");

    // failsafe file buffer
    if(file_ptr == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // loop through the first half of the file (this is the range of good IDs)
    // here we will handle the logic for parsing the integer ranges
    // brute force method is to get the upper and lower bounds of each line then add it to a list using
    // a loop
    while(fgets(line_buffer, sizeof(line_buffer), file_ptr) != NULL && strcmp(line_buffer, "\n") != 0) {
        line_buffer[strcspn(line_buffer, "\n")] = '\0';
        parse_fresh_id_range(line_buffer);
    }

    // loop through the second half of the file (this is each of IDs we have)
    while(fgets(line_buffer, sizeof(line_buffer), file_ptr) != NULL) {
        line_buffer[strcspn(line_buffer, "\n")] = '\0';
        if(fresh_id_check(atoll(line_buffer)) == 1) {
            result_counter++;
        }   
    }

    fclose(file_ptr);

    printf("Total number of fresh ingredient IDs: %d\n", result_counter);

    return 0;
}