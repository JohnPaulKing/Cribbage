#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "card.h"

#define WIN_NUMBER 121 //needed to win
#define RESET 31 // 
#define PEGGING_CARD_AMOUNT 8 //number of cards that can be played during pegging
#define PLAYER_COUNT 2 //number of players


//Each pegging slot holds a card, but also has an owner
typedef struct peggingSlot {
    Card *card; //card
    bool owner; //who owns the card
    unsigned char points; // points that this card gained
} PeggingSlot;

//Initialize players
Player players[PLAYER_COUNT]; //initialize players
//players[0].hand.points=0;
//set up 8 pegging slots
PeggingSlot pegging[PEGGING_CARD_AMOUNT];
char peggingCardsPlayed = 0;
bool dealer; //0 or 1
bool gameWon = false; //true when game ends


int main(); //main, starting point for game
void gameInit(); // initiate the board and deck
    //deck init
    //set each player
void cutForFirst();
void switchDealer();
void singleRound();
void pegger(); //each player takes turns pegging

#endif