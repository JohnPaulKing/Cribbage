#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"

#define NAME_LENGTH 10 //# char permissible in a player name
#define HAND_SIZE 6 //starting cards in hand
#define CRIB_SIZE 4 // number of cards in crib

typedef struct {
    Card *cards[HAND_SIZE]; //the cards the hand holds
    char points; //#points that this hand achieved
} Hand;

typedef struct{
    char name[NAME_LENGTH];
    Hand hand; //array of card "slots" (ptrs), & points
    Card *selectedCard; //selected card
    unsigned char score; //score
    void (*playPeggingCard)(); //function to play a card in pegging
    void (*selectCardsForCrib)(); //function to select a two cards for the crib
} Player;

void revealCards(Hand*);

#endif
