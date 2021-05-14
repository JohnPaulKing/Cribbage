#include "game.h"
#include "board.c"
#include "deck.c"
#include "player.c"
#include <locale.h> //unicode
#include <stdio.h> //std out
#include "test.c"

int main(int argc, char **argv) {
    //initialize variables, and game
    gameInit();
    switchDealer();
    draw();
    
    draw();
}

//runs once at start of game
void gameInit() {
    memset(players[0].hand.cards,0,sizeof(Card*)*HAND_SIZE);
    //initialize deck
    initDeck();
    shuffleDeck();
    deal(&players[0].hand,&players[1].hand);
    revealCards(&players[1].hand); //flip human players cards
    //fill memory locations of board
    boardInit();
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

