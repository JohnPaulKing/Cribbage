#ifndef PEGGING_H
#define PEGGING_H

#include "player.h"
#include "card.h"

#define PEGGING_RESET 31 //the highest number that can be pegged
#define GO 1 //points for go / last

//Each pegging slot holds a card, but also has an owner
typedef struct {
    Card *card; //card pointer
    bool owner; //who owns the card
    unsigned char points; // points that this card gained
} PeggingSlot;

void pegger(); //each player takes turns pegging (using functions from player)
bool verifyPlayableCard(Card*); //verify that a certain card may be played during pegging
char cardPeggable(Card*); //test if a card is peggable (can be played during pegging?)
void sendCardToPegging(Hand*, char, bool); // take a card out of a hand, and place it in a pegging slot

#endif