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
    players[!dealer].selectCardsForCrib(); //non dealer selects cards
    players[dealer].selectCardsForCrib(); //dealer selects cards
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
    collectCards(&players[!dealer].hand, &players[dealer].crib, &players[dealer].crib);
    dealer = !dealer; //switch 
    return 1;
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
            printf("game won!!!");
            sleep(5);
            return i;
        }
    } return -1;
}

/*
switches the dealer
*/
void switchDealer() {
    dealer = !dealer;
}
