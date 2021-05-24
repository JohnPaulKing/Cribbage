#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"

#define NAME_LENGTH 10 //# char permissible in a player name
#define HAND_SIZE 6 //starting cards in hand
#define CRIB_SIZE 4 // number of cards in crib
#define LEFT 75 //arrow key for left
#define RIGHT 77 //arrow key for right
//#define ENTER 

typedef struct {
    Card *cards[HAND_SIZE]; //the cards the hand holds
    char points; //#points that this hand achieved
} Hand;

typedef struct{
    char name[NAME_LENGTH];
    Hand hand; //array of card "slots" (ptrs), & points
    Hand crib; //card slots and points for this crib
    Card *selectedCard; //selected card
    unsigned char score; //score
    void (*playPeggingCard)(); //function to play a card in pegging
    void (*selectCardsForCrib)(); //function to select a two cards for the crib
} Player;

void revealCards(Hand*);
void selectCardsWithInput();
void selectCardsWithCPU();
void pegWithInput();
void pegWithCPU();
void sendCardToCrib(Hand*, char); //send a card from a hand to crib, and remove it
char countCardsInCrib(Player*); //returns number of cards in this players crib

#endif
