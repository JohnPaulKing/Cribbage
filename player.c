#include "player.h"


//makes all cards visible
void revealCards(Hand* hand ) {
    for (char i = 0; i < HAND_SIZE; i++) {
        hand->cards[i]->hidden = !hand->cards[i]->hidden;
    }
}

void pegWithCPU(){
}

/*
Select two cards to sne dto the crib
*/
void selectCardsWithCPU() {
    //for now select first two cards
    //later replace this with AI
    sendCardToCrib(&players[0].hand, 0);
    sendCardToCrib(&players[0].hand, 1);
}

/*
Send a card from a hand to the crib
Also must move subsequent cards down, and make null
*/
void sendCardToCrib(Hand* hand, char index) {
    
}
