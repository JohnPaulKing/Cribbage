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

int main() {
    char count = 0;
    char numbers[5] = {1,1,13,3,13};
    count += countTuples(numbers,0,0);
    count += countTuples(numbers,1,0);
    count +=  countTuples(numbers,2,0);
    count +=  countTuples(numbers,3,0);
    count += countTuples(numbers,4,0);
    printf("tuples: %d\n",count);
}

