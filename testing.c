#include <stdio.h> //io
#include "board.h"
//#include <curses.h>
int x = 1;

char count15s(char numbers[], char index, char amount) {
    amount+=numbers[index]; //initial value
    //printf("comparing %d with all indices after %d\n",amount,index);
    char count = 0;
    for (char i = index+1; i < 5; i++) {
        printf("scoring combinations for %d + %d\n",amount,numbers[i]);
        if (amount + numbers[i] == 15 ) {
            count++;
        } else if (amount + numbers[i] < 15) {
            count += count15s(numbers,i, (amount) );
        } 
    }
    return count;
}


char countTuples(char numbers[], char index, char amount) {
    char count = 0;
    for (char i = index+1; i < 5; i++) {
        if (numbers[index] == numbers[i] ) {
            count++;
        } 
    }
    return count;
}

char scoreRuns(char numbers[]) {
 //sort them
    char temp; //for temporarily storing variables
    char low; //lowest number
    char lowIndex; //index of lowest card
    //for each number
    for (char x = 0; x < 5; x++) {
        low = numbers[x]; //keep track of the lowest number ( so far)
        lowIndex = x;
        //for each number after
        for (char y = x+1; y < 5; y++) { //only move if its lower
            if (numbers[y] < low) {
                lowIndex = y; //new lowest
                low = numbers[lowIndex];
            }
        }
        //now a standard swap using temp
        temp = numbers[x];
        numbers[x] = numbers[lowIndex];
        numbers[lowIndex] = temp;
    }

    char runLength = 1;
    char runMultiplier = 1;
    char runNotation[5] = {1,0,0,0,0};
    //Now run through sorted array 
    for (char x = 1; x < 5; x++) {
        if (numbers[x] == numbers[x-1]) {
            runNotation[runLength-1]++;
            //if next number 1 higher
        } else if (numbers[x] == numbers[x-1] + 1) {
            runNotation[runLength++]++;
        } else {
            if (runLength < 3) {
                runLength = 1;
                runMultiplier = 1;
                runNotation[0] = 1; //run starting here
                for (char i = 1; i < 5; i++) {
                    runNotation[i] = 0;
                }
            } else {
                break;
            }
        }
    }

    //calculate run modifier
    //this is a little complicated, but the idea is only return a number if its greater than 3
    if (runLength > 2) {
        for (char i = 0; i < 5; i++) {
            if (runNotation[i] > 2) {
                runMultiplier = 3;
            } else if (runNotation[i] > 1) {
                runMultiplier = runMultiplier * 2;
            }
        }
    } else {
        runMultiplier = 0; //as in, there is no run of 3 here
    }

    //return the run amount times the multiplier (single, double, triple) if over 3
    return runLength * runMultiplier;
    
}

int main() {
    char count = 0;
    char numbers[5] = {5,7,7,5,8};
    count = scoreRuns(numbers);
    printf("runs: %d\n",count);
}

