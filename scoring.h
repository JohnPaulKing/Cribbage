#ifndef SCORING_H
#define SCORING_H

#define FIFTEEN 15 //just fifteen
#define PEGGING_RESET 31 //the highest number that can be pegged
#define GO 1 //points for go / last
#define FIFTEEN_SCORE 2 //points for pegging or scoring a 15
#define TUPLE_SCORE 2
#define RUN_LENGTH 3 //minimum length of a run
#define HEELS_SCORE 2; //cutting a jack
#define NOB_SCORE 1; //having a jack matching top (cut) card

#include "game.h"
#include "card.h"
#include "deck.h"
#include "board.h"
//scores for 0, 1, 2, 3, or 4 matching cards
//these scores are used for the pegging stage
const char TUPLE_SCORES[] = {0,0,2,6,12};

char scorePegging(); //count the points gained by a pegging card
bool isRun(char[], char); //given an array of numbers, 
char scoreHand(Hand*); //given a hand pointer, calculate number of points
char score15(Hand*); //count number of combinations of 15
bool scoreNobs(Hand*); //returns either a 1 or 0 to represent nobs or no nobs
char scoreTuples(Hand*); //calculates points for any cards that match 1 or more other cards
char scoreRuns(Hand*); //calculates runs
char scoreFlush(Hand*); //checks if hand contains a flush of a suit
char count15(Hand*, char, char);
char countTuples(Hand*,char);
bool scoringPhase();

#endif