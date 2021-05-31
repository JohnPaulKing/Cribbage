#include "game.h"
#include "board.c"
#include "deck.c"
#include "player.c"
#include "pegging.c"
#include <locale.h> //unicode
#include <stdio.h> //std out
#include "test.c"

int main(int argc, char **argv) {
    gameInit();

    //while game isn't won, start the next round
    //at both pegging and scoring, need breaks to check
    singleRound();

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

void singleRound(){
    shuffleDeck();
    //deal 6 cards to each player
    deal(&players[0].hand,&players[1].hand);
    //cut the deck (not revealed until after selection)
    //reveal the cards for the player
    revealCards(&players[1].hand); //flip human players cards
    revealCards(&players[0].hand); //flip comp cards
    //wait until player selects their cards to discard
    cutDeck();

    players[!dealer].selectCardsForCrib(); //non dealer selects cards
    players[dealer].selectCardsForCrib(); //dealer selects cards

    //they are then hidden
    hideCards(&players[dealer].crib);
    draw();
    pegger();

}

/*
Set dealer first
*/
void cutForFirst() {
    dealer = 0;
}

/*
switches the dealer
*/
void switchDealer() {
    dealer = !dealer;
}
