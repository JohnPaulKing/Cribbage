#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "card.h"
#include "pegging.h"

#define WIN_NUMBER 121 //needed to win
#define RESET 31 // 
#define PEGGING_CARD_AMOUNT 8 //number of cards that can be played during pegging
#define PLAYER_COUNT 2 //number of players

//Initialize players
Player players[PLAYER_COUNT]; //initialize players

//pegging info
PeggingSlot pegging[PEGGING_CARD_AMOUNT];
char peggingCardsPlayed = 0; 
char peggingCount = 0; // starts at 0, resets at 31
bool currentPegger; //which player must play a pegging card (if able)

bool dealer = 0; //0 or 1
bool gameWon = false; //true when game ends


int main(); //main, starting point for game
void gameInit(); // initiate the board and deck
    //deck init
    //set each player
void cutForFirst();
void switchDealer();
void singleRound();

#endif