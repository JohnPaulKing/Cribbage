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
            deck[deckIndex].hidden = HIDE_CARDS;
            deck[deckIndex].selected = false;
             //value either number value, or 10 for face card
            deck[deckIndex].value= (number > 10) ? 10: number;
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
    //this just picks the next card that isn't dealt
    topCard = shuffled[HAND_SIZE*2]; 
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
        clrConsole();
        console("Two For His Heels");
        draw();
        getc(stdin);
    }
}

void collectCards(Hand* hand0, Hand* hand1, Hand* crib) {
    //nullify the crib
    for (char i = 0; i < crib->cardsInHand; i++) {
        //hide all cards
        hand0->cards[i]->hidden = HIDE_CARDS;
        hand1->cards[i]->hidden = HIDE_CARDS;
        crib->cards[i]->hidden = HIDE_CARDS;
        topCard->hidden = HIDE_CARDS;
        //remove refs
        hand0->cards[i] = NULL;
        hand1->cards[i] = NULL;
        crib->cards[i] = NULL;

        //remove points
        hand0->points = 0;
        hand1->points =0;
        crib->points = 0;
    }
    //recount
    crib->cardsInHand = 0;
    hand0->cardsInHand = 0;
    hand1->cardsInHand = 0;
}