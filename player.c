#include "player.h"
#include "game.h"


//makes all cards visible
void revealCards(Hand* hand ) {
    for (char i = 0; i < HAND_SIZE; i++) {
        hand->cards[i]->hidden = !hand->cards[i]->hidden;
    }
}

char countCardsInCrib(Player* player) {
    char count = 0;
    for (char i = 0; i < CRIB_SIZE; i++) {
        if (player->crib.cards[i]) { //if valid pointer
            count++;
        }
    } return count;
}

void pegWithCPU(){
}

/*
select to cards with 
*/
void selectCardsWithInput(){
    strcpy(consoleMessage,"select a card");
    players[1].hand.cards[0]->selected = true;
    draw();
    
}

/*
Select two cards to send to the crib
*/
void selectCardsWithCPU() {
    //for now select first two cards
    //later replace this with AI

    //if the second index is after the first, 
    //it needs to have one subtracted from it
    //to account for the "collapsing"
    sendCardToCrib(&players[0].hand, 0);
    sendCardToCrib(&players[0].hand, 0);
}

/*
Send a card from a hand to the crib
Also must move subsequent cards down, and make null
*/
void sendCardToCrib(Hand* hand, char index) {
    //copy card pointer to peggingslot
    players[dealer].crib.cards[countCardsInCrib(&players[dealer])] = hand->cards[index];
    //set card in hand to null (this will be overwritten)
    //hand->cards[index] = NULL;
    //collapse the array by moving each subsequent card down
    /*
    for example:
    0, 1, 2, 3, 4, 5
    a, b, c, d, e, f
    subtract 2
    0, 1, 2, 3, 4, 5
    a, b,  , d, e, f
    move d to 2, e to 3, f to 4
    */
    for (char i = index; i < HAND_SIZE-1 ;i++){
        //move the subsequent pointer down one
        hand->cards[i] = hand->cards[i + 1];
    }
    //finally, set last index to null
    hand->cards[HAND_SIZE-1] = NULL;
}
