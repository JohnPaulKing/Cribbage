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
        printf("deck: %d = val: %d of suit: %d\n",i,deck[i].type,deck[i].suit);
    }
    /*
    deck: 0 = val: 1 of suit: 1
deck: 1 = val: 2 of suit: 2
deck: 2 = val: 3 of suit: 3
deck: 3 = val: 4 of suit: 4
deck: 4 = val: 5 of suit: 5
deck: 5 = val: 6 of suit: 6
deck: 6 = val: 7 of suit: 7
deck: 7 = val: 8 of suit: 8
deck: 8 = val: 9 of suit: 9
deck: 9 = val: 10 of suit: 10
deck: 10 = val: 11 of suit: 11
deck: 11 = val: 12 of suit: 12
deck: 12 = val: 13 of suit: 13
deck: 13 = val: 1 of suit: 1
deck: 14 = val: 2 of suit: 2
deck: 15 = val: 3 of suit: 3
deck: 16 = val: 4 of suit: 4
deck: 17 = val: 5 of suit: 5
deck: 18 = val: 6 of suit: 6
deck: 19 = val: 7 of suit: 7
deck: 20 = val: 8 of suit: 8
deck: 21 = val: 9 of suit: 9
deck: 22 = val: 10 of suit: 10
deck: 23 = val: 11 of suit: 11
deck: 24 = val: 12 of suit: 12
deck: 25 = val: 13 of suit: 13
deck: 26 = val: 1 of suit: 1
deck: 27 = val: 2 of suit: 2
deck: 28 = val: 3 of suit: 3
deck: 29 = val: 4 of suit: 4
deck: 30 = val: 5 of suit: 5
deck: 31 = val: 6 of suit: 6
deck: 32 = val: 7 of suit: 7
deck: 33 = val: 8 of suit: 8
deck: 34 = val: 9 of suit: 9
deck: 35 = val: 10 of suit: 10
deck: 36 = val: 11 of suit: 11
deck: 37 = val: 12 of suit: 12
deck: 38 = val: 13 of suit: 13
deck: 39 = val: 1 of suit: 1
deck: 40 = val: 2 of suit: 2
deck: 41 = val: 3 of suit: 3
deck: 42 = val: 4 of suit: 4
deck: 43 = val: 5 of suit: 5
deck: 44 = val: 6 of suit: 6
deck: 45 = val: 7 of suit: 7
deck: 46 = val: 8 of suit: 8
deck: 47 = val: 9 of suit: 9
deck: 48 = val: 10 of suit: 10
deck: 49 = val: 11 of suit: 11
deck: 50 = val: 12 of suit: 12
deck: 51 = val: 13 of suit: 13
*/
}

void cutOverride() {
    topCard = &deck[10];
}

/*
results in unshuffled deck
*/
void shuffleOverride(){
//Leave this for testing with sequences
/*
    //clear shuffled slots first
    memset(shuffled,0,sizeof(Card*)*DECK_SIZE); //set each pointer to NULL
    //for all 52 cards
    for (char i = 0; i < DECK_SIZE; i++) {
        shuffled[i] = &(deck[i]); //pointer to a card
    }
    //leave this for manual testing
    */
   shuffleDeck();
shuffled[0] = &deck[0]; //discared
shuffled[1] = &deck[1]; //discared
shuffled[2] = &deck[2]; //discared
shuffled[3] = &deck[3]; //discared
shuffled[4] = &deck[48]; //second (comp)
shuffled[5] = &deck[22]; //first (player)
shuffled[6] = &deck[49]; //fourth (comp) //go
shuffled[7] = &deck[23]; //third (player)
shuffled[8] = &deck[50]; //6th (comp)
shuffled[9] = &deck[24]; //5th (player)
shuffled[10] = &deck[51]; //8th (comp)
shuffled[11] = &deck[25]; //7th (player)
}