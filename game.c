#include "game.h"
#include "board.c"
#include "deck.c"
#include "player.c"
#include <locale.h> //unicode
#include <stdio.h> //std out
#include "test.c"

int main(int argc, char **argv) {
    gameInit();
    switchDealer();

    draw();
    for (int i = 0; i < 100; i++) {
        cutDeck();
    }
}

//runs once at start of game
void gameInit() {
    memset(players[0].hand.cards,0,sizeof(Card*)*HAND_SIZE);
    //initialize deck
    initDeck();
    shuffleDeck();
    deal(&players[0].hand,&players[1].hand);
    cutDeck();
    revealCards(&players[1].hand); //flip human players cards
    //fill memory locations of board
        //initialize variables, and game
    boardInit();
}

void round(){
    
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

