#include "player.h"
#include "game.h"
#include "card.h"
#include "deck.h"

void testDeckInit() {
    //test if deal worked
    for (int i = 0; i < 52; i++ ) {
        printf("suit: %d, number: %d\n",deck[i].suit,deck[i].type);
    }
}

void testDeal() {
    //test if deal worked
    for (int i = 0; i < 6; i++ ) {
        printf("suit: %d, number: %d\n",players[0].hand.cards[i]->suit,players[0].hand.cards[i]->type); 
    }
}

void testShuffle() {
    //test if deal worked
    for (int i = 0; i < 52; i++ ) {
        printf("suit: %d, number: %d\n",shuffled[i]->suit,shuffled[i]->type);
    }
}

void testCribContents() {
        //print cards in crib
    for (char i = 0; i < CRIB_SIZE; i++) {
        if (players[dealer].crib.cards[i]) {
            printf("crib slot %d = %p, suit = %d\n", i, players[dealer].crib.cards[i],players[dealer].crib.cards[i]->suit);
        }
    }
}