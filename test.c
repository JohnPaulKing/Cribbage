/*
THIS FILE IS ONLY FOR TESTING
*/

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

void printDeck() {
    for (int i = 0; i < 52; i++) {
        printf("deck: %d = val: %d of suit: %d\n",i,deck[i].type,deck[i].type);
    }getc(stdin);
}

void cutOverride() {
    topCard = &deck[10];
}

/*
results in unshuffled deck
*/
void shuffleOverride(){

//leave this for manual testing
shuffled[0] = &deck[0]; //discared
shuffled[1] = &deck[1]; //discared
shuffled[2] = &deck[2]; //discared
shuffled[3] = &deck[3]; //discared
shuffled[4] = &deck[4]; //second
shuffled[5] = &deck[5]; //first
shuffled[6] = &deck[6]; //fourth
shuffled[7] = &deck[7]; //third
shuffled[8] = &deck[8]; //kept
shuffled[9] = &deck[9];
shuffled[10] = &deck[10]; //kept
shuffled[11] = &deck[12];
shuffled[12] = &deck[11]; //cut card


/*
//Leave this for testing with sequences

    //clear shuffled slots first
    memset(shuffled,0,sizeof(Card*)*DECK_SIZE); //set each pointer to NULL
    //for all 52 cards
    for (char i = 0; i < DECK_SIZE; i++) {
        shuffled[i] = &(deck[i]); //pointer to a card
    }
*/
}