#ifndef SCORING_H
#define SCORING_H

#define FIFTEEN 15 //just fifteen
#define PEGGING_RESET 31 //the highest number that can be pegged
#define GO 1 //points for go / last
#define FIFTEEN_SCORE 2 //points for pegging or scoring a 15

//scores for 0, 1, 2, 3, or 4 matching cards
const char TUPLE_SCORES[] = {0,0,2,6,12};

char scorePegging(); //count the points gained by a pegging card
bool isRun(char*, char); //given an array of numbers, 

#endif