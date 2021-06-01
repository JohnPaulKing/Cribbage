#include "deck.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

//initialize deck
void initDeck() {
    char deckIndex = 0; //index of deck from 0-51
    //iterate through all suits
    for (Suit suit = SPADE; suit <= CLUB; suit++) {
        //iterate through all numbers
        for (char number = 1; number <= KING; number++) {
            //initialize all variables
            deck[deckIndex].suit = suit;
            deck[deckIndex].type = number;
            deck[deckIndex].hidden = true;
            deck[deckIndex].selected = false;
            deckIndex++; //increase to next slot
        }
    }
}

/*
Shuffle pointers to each card
*/
void shuffleDeck() {
    srand(time(NULL));// seed random with time
    //clear shuffled slots first
    memset(shuffled,0,sizeof(Card*)*DECK_SIZE); //set each pointer to NULL
    //for all 52 cards
    for (char i = 0; i < DECK_SIZE; i++) {
        //generate a random slot from 0-1
        char r = rand()%DECK_SIZE;
        //if there is already a card pointer at this slot,move up one slot
        //if it goes to 52, becomes 0, etc
        for (;shuffled[r%DECK_SIZE];r++){}
        //make random slot point to the card
        shuffled[r%DECK_SIZE] = &(deck[i]); //pointer to a card
    }
}

/*
Cut a card from the deck
from startingAt, until end of deck
set that card as cut card
*/
void cutDeck() {
    //must leave a buffer of cards on each side
    //starts at hand_size*2 because that many cards have been "dealt" from the top
    char low = (HAND_SIZE*2) + CUT_BUFFER; //16
    char high = DECK_SIZE - CUT_BUFFER - 1; //47
    //randomly generate a card
    char indexOfCut = rand()%(high-low);
    //offset it by adding low
    indexOfCut+=low;
    topCard = shuffled[indexOfCut]; //move card to "top"
}

/*
deal cards into each hand
alternate putting deck pointers into each hand
*/
void deal(Hand* hand0,Hand* hand1) {
    char cardIndex = 0;
    for (char i = 0; i < HAND_SIZE; i++) {
        //set the card ptr in each hand
        //increase the index in deck
        hand0->cards[i] = shuffled[cardIndex++];
        hand0->cardsInHand++; //increase number of cards
        hand1->cards[i] = shuffled[cardIndex++];
        hand1->cardsInHand++; // increase number of cards
    }
}

/*
This function just "flips" the card that has already been "cut" by the algorithm
*/
void revealTopCard() {
    topCard->hidden = false; //reveal the top card (cut card)
    if (topCard->type == JACK) {
        //2 points for jack cut
        players[dealer].score += HEELS_SCORE;
        console("Two For His Heels");
    }
}