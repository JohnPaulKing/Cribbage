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

/*
This function goes through hand and calculates all points
when a hand is passed in, the top card is added as a temporary 5th card
*/
char scoreHand(Hand* hand) {
    char temp; //hold a value before added to hand
    char score = 0; //score for hand
    //first add the top card
    //also increment the number of cards in hand
    hand->cards[hand->cardsInHand++] = topCard;

    //now calculate each type of points (and print them)
    temp = score15(hand);
    score += temp;
    if (temp) {
        sprintf(messsageBuffer,"Fifteens: %d, ",temp);
        console(messsageBuffer);
    }

    temp = scoreNobs(hand) * NOB_SCORE;
    score += temp;
    if (temp) {
        sprintf(messsageBuffer,"Nobs: %d, ",temp);
        console(messsageBuffer);
    }
    temp = scoreRuns(hand);
    score += temp;
    if (temp) {
        sprintf(messsageBuffer,"Runs: %d, ",temp);
        console(messsageBuffer);
    }
    temp = scoreTuples(hand);
    score += temp;
    if (temp) {
        sprintf(messsageBuffer,"Pairs: %d, ",temp);
        console(messsageBuffer);
    }
    temp = scoreFlush(hand);
    score += temp;
    if (temp) {
        sprintf(messsageBuffer,"Flush: %d, ",temp);
        console(messsageBuffer);
    }
    //now print the total
    sprintf(messsageBuffer,"Total: %d, ",score);
    console(messsageBuffer);

    //reverse what we did earlier
    //decrease cards in hand, set 5th to NULL
    hand->cards[--hand->cardsInHand] = NULL;
    hand->points += score; //mark points scored in hand
    draw();
    getc(stdin);
    
    return score;
}

char score15(Hand* hand) {
    char score = 0; //amount of points
    for (int i = 0; i < hand->cardsInHand; i++) {
        //recursive function, so we'll call it it with the third argument 0
        score += count15(hand,i,0); //number of 15s
    }
    return score * FIFTEEN_SCORE; //multiply score by the points by 2, so each fifteen is 2 points
}

char count15(Hand* hand, char index, char amount) {
    amount+=hand->cards[index]->value; //initial value
    //printf("comparing %d with all indices after %d\n",amount,index);
    char count = 0;
    for (char i = index+1; i < hand->cardsInHand; i++) {
        if (amount + hand->cards[i]->value == 15 ) {
            count++;
        } else if (amount + hand->cards[i]->value < 15) {
            count += count15(hand,i,amount );
        } 
    }
    return count;
}

/*
Checks hand to see if it has a jack that matches the top card (cut card)
if so, a point is added for nobs
*/
bool scoreNobs(Hand* hand) {
    //make sure we don't check the last card, in case its a jack
    for (char i = 0;i < hand->cardsInHand-1; i++ ) {
        if (hand->cards[i]->type == JACK && hand->cards[i]->suit == topCard->suit) {
            return 1; //can only ever be one point for nobs
        }
    } return 0; //no nobs
}

/*
Checks hand to get scores from doubles, triples, etc
*/
char scoreTuples(Hand* hand) {
    char score = 0; //amount of points
    for (int i = 0; i < hand->cardsInHand; i++) {
        score += countTuples(hand,i);
    }
    return score * TUPLE_SCORE; //multiply score by the tuple multiplyer
}

char countTuples(Hand* hand, char index) {
    char count = 0; //nunber of tuples
    //for each card after the card in the hand, see if there is a duplicate
    //this way pairs don't get "double counted"
    for (char i = index+1; i < hand->cardsInHand; i++) { 
        if (hand->cards[i]->type == hand->cards[index]->type ) {
            count++;
        } 
    }
    return count;
}

/*
A flush can either be all four cards in the hand (cards 0-3 by index)
or those four, plus the top card
this algorithm is simple: mark how many cards after the first match the first
optionally this can include the top (last) card, for an extra point
*/
char scoreFlush(Hand* hand) {
    char run = 0; //how many consecutive cards are of suit s
    //mark the first suit
    Suit suit = hand->cards[0]->suit; 
    // go through each card in hand
    for (char i = 0; i < hand->cardsInHand-1; i++) {
        if ( hand->cards[i]->suit == suit) {
            run++;
        } else {
            //as soon as one doesn't match, run is over
            return 0; 
        }
    }
    //now check for the last card
    //if it matches the suit, add a point
    if (hand->cards[hand->cardsInHand-1]->suit == suit) {
        run++;
    }
    return run;
}

char scoreRuns(Hand* hand) {
    //create a temporary array of numbers
    char numbers[hand->cardsInHand];
    for (char i = 0; i < hand->cardsInHand; i++) {
        numbers[i] = hand->cards[i]->type;
    }
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
                for (char i = 1; i < hand->cardsInHand; i++) {
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

/*
each hand is scored
returns true if the game will continue
returns false upon a player win
*/
bool scoringPhase() {
    clrConsole();
    console("Non-dealer hand: ");
    players[!dealer].score += scoreHand(&players[!dealer].hand);
    //check if this gave this player enough points to win
    if (gameWon() > -1) {
        printf("game won during scoring human\n"); sleep(5);
        return 0;
    }
    clrConsole();
    console("Dealer hand: ");
    players[dealer].score += scoreHand(&players[dealer].hand);
    clrConsole();
    console("Dealer crib: ");
    players[dealer].score += scoreHand(&players[dealer].crib);
    //getc(stdin);
    if (gameWon() > -1) {
        printf("game won during score comp\n"); sleep(5);
        return 0;
    } else {
        return 1;
    }
}
