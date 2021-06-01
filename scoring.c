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
    
    so the scorer should start at slot 4 (not interested in last card), and stop at slot 3 when searching
   */
  char tupleCount = 1; //as in there is a match of only 1 card 
  for (char i = peggingCardsPlayed-2; i >+ peggingCardsSinceReset; i--) {
      if (pegging[i].card->type == lastPlayed->type) {
          tupleCount++; 
      } else {
          break; //can't continue match
      }
  }
  score+= TUPLE_SCORES[tupleCount];
  return score;
}