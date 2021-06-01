#include "scoring.h"

char scorePegging() {
char score = 0; //the amount of points that this card "scored"
/*
We want to account for the following scenerios when scoring pegging
the pegging score. Firstly, that the player hit 15
secondly, that the player hit 31 on the pegging count
Thirdly, that the card matched the prior card before it (or even the cards before that)
Fourthly, that this card and the cards immediately before it form a run
All of these situations must be evaluated individually, and then scored
*/
//this checks the first and second criteria
if (peggingCount == FIFTEEN || peggingCount == PEGGING_RESET) {
    score += FIFTEEN_SCORE; //add points
}

//we want to keep track of the last card played
Card* lastPlayed = pegging[peggingCardsPlayed-1].card;
//now check if it is a tuple
//first make sure a card before this has been played

/*
lets say the cards played are as follows:
cardsPlayed = 6
cardsSinceReset = 3         (The reset would happen after the third q)
0  1  2  3  4  5
Q, Q, Q, Q, 5, 6

so the scorer should start at slot 5, and stop at slot 3 when searching
*/
char tupleCount = 0; //as in there is a match of only 1 card 
for (char i = peggingCardsPlayed-1; i >= (peggingCardsPlayed-peggingCardsSinceReset); i--) {
    if (pegging[i].card->type == lastPlayed->type) {
        tupleCount++; 
    } else {
        break; //can't continue match
    }
}
score+= TUPLE_SCORES[tupleCount];

/*now we do the same thing runs
this is slightly more complicated, but its core functionality is the same
We will go through all of the cards, and add them to dynamically alloc'ed memory
Then we will use the same "run" algorithm that we'll for scoring a hand
this time the "order" doesn't matter as much (a run can be 6-4-5)
*/
char* numbers = malloc(8); //allocate space for 8 numbers
char numbersInRun = 0;
char runOf = 0; //keeps track of the run size
/*
At several points I have done conditionals on RUN_LENGTH
if there have not been 3 cards played since reset, don't even run any of this
if there have been, don't test the run until you're comparing 3 cards

*/
if (peggingCardsSinceReset > RUN_LENGTH-1) { //can only be a run with 3 or more cards
    for (char i = peggingCardsPlayed-1; i >= (peggingCardsPlayed-peggingCardsSinceReset); i--) {
        //put the numbers in opposite order (easier for sorting)
        numbers[numbersInRun++] = pegging[i].card->type;
        if (numbersInRun > RUN_LENGTH-1 && isRun(numbers,numbersInRun)) {
            runOf = numbersInRun; //the run size so far
        } 
    } 
    score += (runOf > RUN_LENGTH-1) ? runOf : 0 ; //add the size of the run to the score, if less than 3, no run
    //free them
    free(numbers);
}

//console(scoringMessage);

return score;
}

bool isRun(char numbers[], char quantity) {
    //sort them
    char temp; //for temporarily storing variables
    char low; //lowest number
    char lowIndex; //index of lowest card
    //for each number
    for (char x = 0; x < quantity; x++) {
        low = numbers[x]; //keep track of the lowest number ( so far)
        lowIndex = x;
        //for each number after
        for (char y = x+1; y < quantity; y++) { //only move if its lower
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

    //Now run through sorted array 
    for (char x = 0; x < quantity-1; x++) {
        if (numbers[x] != numbers[x+1]-1) {
            return false; //not a run of <quantity>
        }
    }
    //if there is an unbroken chain, return true
    return true;
}