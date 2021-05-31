#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"
#include <stdlib.h>

#define NAME_LENGTH 10 //# char permissible in a player name
#define HAND_SIZE 6 //starting cards in hand
#define CRIB_SIZE 4 // number of cards in crib
#define LEFT 68 //arrow key for left
#define RIGHT 67 //arrow key for right
#define ESCAPE 27 //ANSI escape sequence
#define ENTER 10 //enter / newline 
//#define ENTER 

typedef struct {
    Card *cards[HAND_SIZE]; //the cards the hand holds
    char points; //#points that this hand achieved
    char cardsInHand; //number of cards in a hand
} Hand;

typedef struct{
    char name[NAME_LENGTH];
    Hand hand; //array of card "slots" (ptrs), & points
    Hand crib; //card slots and points for this crib
    char selectedCard; //selected card index
    unsigned char score; //score
    unsigned char (*playPeggingCard)(); //function to play a card in pegging
    void (*selectCardsForCrib)(); //function to select a two cards for the crib
} Player;

void revealCards(Hand*);
void hideCards(Hand*);
void selectCardsForCribWithInput();
void selectCardsForCribWithCPU();
unsigned char pegWithInput();
unsigned char pegWithCPU();
void sendCardToCrib(Hand*, char); //send a card from a hand to crib, and remove it
char countCardsInCrib(Player*); //returns number of cards in this players crib
void selectCard(Player*); //change the selected card in a players hand
void playersInit();

#endif
