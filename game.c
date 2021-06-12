#include "game.h"
#include "board.c"
#include "deck.c"
#include "player.c"
#include "pegging.c"
#include "scoring.c"
#include <locale.h> //unicode
#include <stdio.h> //std out
#include "test.c"

int main(int argc, char **argv) {
    
    gameInit();
    //printDeck();
    //while game isn't won, start the next round
    //at both pegging and scoring, need breaks to check
    while (singleRound()) {}//continue round until game ends
    //announce win, and player stats
    announceWin(&players[gameWon()],&players[!gameWon()]); 

}

//runs once at start of game
void gameInit() {
    //initialize deck
    //fill memory locations of board
        //initialize variables, and game
    playersInit();
    initDeck();
    boardInit();
}

bool singleRound(){
    shuffleDeck();
    //deal 6 cards to each player
    deal(&players[0].hand,&players[1].hand);
    //cut the deck (not revealed until after selection)
    //reveal the cards for the player
    revealCards(&players[1].hand); //flip human players cards
    printf("revealed cards\n");
    //wait until player selects their cards to discard
    cutDeck();
    printf("cut deck\n");
    players[1].selectCardsForCrib(); //person selects their cards
    players[0].selectCardsForCrib(); //computer selects their cards
    revealTopCard();
    draw();
    sleep(1); //maybe not necesary?
    if (!pegger()) {
        return 0; //end round ( and game)
    }
    //revealCards(&players[0].hand); //flip comp cards
    revealCards(&players[dealer].crib);
    if (!scoringPhase()) {
        return 0; //end round (and game)
    }
    draw();
    collectCards(&players[!dealer].hand, &players[dealer].hand, &players[dealer].crib);
    switchDealer();
    return 1;
}

void switchDealer() {
    //clear the first dealer message
    strcpy(dealerMessages[dealer],"");
    dealer = !dealer; //switch 
    //add the dealer tag to the new dealer
    strcpy(dealerMessages[dealer],"Dealer's Crib");
}

/*
Set dealer first
*/
void cutForFirst() {
    dealer = 0;
}

/*
return 1 or 0 if a player has enough points to have won
return -1 otherwise
*/
char gameWon() {
    for (char i = 0; i < 2; i++) {
        if (players[i].score > WIN_NUMBER) {
            return i;
        }
    } return -1;
}

