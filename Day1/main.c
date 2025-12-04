#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/**
 * Author: Kyle Sherman
 * Date: 12/02/2025
 * Details:
 * 
 * Advent of Code 2025 Day 1
 * 
 * We will want to parse a file to for instructions on movement
 * each line will be one command
 * first char will be a direction Left or Right
 * following chars make up the distance to rotate
 * 
 * There are a couple of important notes to make here
 * since our range is 0 - 99, that gives us a range of 100
 * anything outside of this must wrap back around.
 * The easiest way to handle this will be modulo and we can then add the range (100) to compensate
 * for negative values.
 * The number of times the resulting position after rotation hits zero is the combo
 * 
 * HARD MODE:
 * We will want to also cound the number of times the value wraps around striking zero
 * This value will be added to the previous hits giving us the final answer
 * before moving the position, you should be able to pre determine this by dividing the new postion by the range (100)
 * which returns the number of possible times this can be divided.
 * 
 * I will brute force this solution then try to clean it up a bit :)
 * 
 * Day 1: Secret Entrance
 * Dir[distance] options are L or R
 * 0 through 99, will loop back around from 0->99 and 99->0
 */

int zeroCount = 0;
#define LIMIT 100 // range size 100 (0-99)

// based on the quotient integral division algorithm
// just performs the division and ignores remainder
int floordiv(int a, int b) {
    int q = a / b;
    if((a % b != 0) && ((a < 0) != (b < 0))) {
        q--;
    }
    return q;
}

int rotate(int position, char dir, int dist) {
    int newPosition = 0;
    int clicks = 0;
    
    if(dir == 'L') {
        int movement = position - dist;
        clicks = floordiv(position - 1, LIMIT) - floordiv(movement - 1, LIMIT);
        newPosition = movement % LIMIT;
    } else {
        int movement = position + dist;
        clicks = floordiv(movement, LIMIT) - floordiv(position, LIMIT);
        newPosition = movement % LIMIT;
    }

    zeroCount += clicks;

    return newPosition;
}

int main(int argc, char *argv[]) {
    int position = 50;

    FILE *file_ptr;
    char buffer[256];

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
        // printf("%s", buffer);
        char dir = '\0';
        int dist = 0;
        char *endptr;

        dir = buffer[0];
        dist = strtol(buffer+1, &endptr, 10);

        printf("Start: %d ", position);

        position = rotate(position, dir, dist);

        printf("Dir: %c Dist: %d End: %d \n", dir, dist, position);
    }

    fclose(file_ptr);

    printf("\n\n\rKEY: %d\n\r", zeroCount);

     return 0;
}