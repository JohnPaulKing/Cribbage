#ifndef DECK_H
#define DECK_H

#include "card.h"
#include "player.h"
#include "scoring.h"

#define DECK_SIZE 52 // #cards
#define CUT_BUFFER 4 //number of cards on either side that need to be left

Card deck[DECK_SIZE]; //alot deck size
Card *shuffled[DECK_SIZE]; //shuffled pointers to each card in deck. 
Card *topCard; //points to a card somewhere in the deck, to simulate cut
bool topCardRevealed = false; //true once flipped, false again at deal

void shuffleDeck(); //arrange card pointers in shuffled randomly
void initDeck(); //create initial deck
void deal(Hand*,Hand*); //deal 6 cards from deck to each hand
void cutDeck(); //select a random card from startingAt, until end of deck
void cutForFirst();
void revealTopCard();
void collectCards(Hand*, Hand*, Hand*);

#endif