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

    //fill memory locations of board
        //initialize variables, and game
    boardInit();
}

void round(){
    //deal 6 cards to each player
    deal(&players[0].hand,&players[1].hand);
    //cut the deck (not revealed until after selection)
    cutDeck();
    //reveal the cards for the player
    revealCards(&players[1].hand); //flip human players cards
    //wait until player selects their cards to discard
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

void pegger() {
    //while the game has not yet been won and 
    //while all cards have not yet been pegged
    while (!gameWon && peggingCardsPlayed < PEGGING_CARDS) {
        players[dealer].playPeggingCard();
    }
    if (gameWon) {
        //deal with this later
    }
}