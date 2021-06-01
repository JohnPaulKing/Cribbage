#include "player.h"
#include "game.h"
#include "board.h"
#include "pegging.h"


//makes all cards visible
void revealCards(Hand* hand ) {
    for (char i = 0; i < hand->cardsInHand; i++) {
        hand->cards[i]->hidden = false;
    }
}

//makes all cards in hand hidden
void hideCards(Hand* hand ) {
    for (char i = 0; i < hand->cardsInHand; i++) {
        hand->cards[i]->hidden = true;
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

/*
The computer selects a card that is legally playable,
or says "go" if unable
*/ 
unsigned char pegWithCPU(){
    /* TODO
    Add logic, for now just pick first card
    */
   console("CPU selecting card");
   sleep(1);
   unsigned char value; //this will hold the 1-10 value of a card
   Hand* hand = &players[0].hand; 
   //for each card
   for (char i = 0; i < hand->cardsInHand; i++) { 
       if (value = cardPeggable(hand->cards[i])) { //if card playable
        sendCardToPegging(hand, i, 0); //send card at index i in hand to pegging slot
        //above function takes care of math, etc
        //at this point, this function just needs to return the amount (number) added to pegging count
        return value;
       } //end of loop, with no card played and value returned
       //therefor we coudldn't play a card
   }  return 0;
}


/*
Player selects a card
This function verifies that the card is legally playable
if the player has no options, they may press enter for go
*/
unsigned char pegWithInput() {
    console("select a card to peg"); //print message
    //first check if any cards are legally playable
    Hand* hand = &players[1].hand; 
    unsigned char value; //this will hold the 1-10 value of a card
    bool peggableCardInHand = false;
    for (char i = 0; i < hand->cardsInHand; i++) { 
       if (value = cardPeggable(hand->cards[i])) { //if card playable
            peggableCardInHand = true; //mark that a card is playable
       } 
    }

    if (peggableCardInHand) {
        while (true) {
            //player selects a card with input
            selectCard(&players[1]); //player 1 selects card for pegging
            if (value = cardPeggable(hand->cards[players[1].selectedCard])) { //if card is playable
                sendCardToPegging(hand, players[1].selectedCard, 1); //send card at index i in hand to pegging slot
                return value; 
            }
        }
    } else {
        return 0; //no cards playable
    }
    clearConsole();
}

/*
select to cards with 
*/
void selectCardsForCribWithInput(){
    console("select a card for the crib"); //print message
    selectCard(&players[1]); //player 1 selects first card
    sendCardToCrib(&players[1].hand, players[1].selectedCard);
    selectCard(&players[1]); //player 1 selects first card
    sendCardToCrib(&players[1].hand, players[1].selectedCard);
    draw();
}


/*
REDO parts of this function with curses?
*/

/*
The first card is selected by default
arrow keys move the card that is selected
enter "sends" the card, to either the crib or pegging phase
*/
void selectCard(Player* player) {
    //in other words, don't wait for enter
    char index = 0;
    //default the first card to selected
    player->hand.cards[0]->selected = true;
    while (true) { //until broken
        draw(); //draw the screen with currently selected card
        //await keypress 
        //can be either left or right arrow key, or enter
        //system ("/bin/stty raw"); //send all individual keystrokes to program
        char c = getc(stdin); //get a character from standard in stream
        //system("/bin/stty cooked"); //reset
        if (c == '\n') {
            //this will remove the color from it later
            player->hand.cards[index]->selected = false;
            //save the selected card, and return
            player->selectedCard = index;
            break;
        }
        //if key pressed was a left arrow
        if (c == ESCAPE) {
            getc(stdin);//middle character in sequence
            c = getc(stdin); //actual arrow key direction
            if (c == LEFT) {
                //deselect current card
                player->hand.cards[index]->selected = false;
                //increase index
                index = index ? index-1: player->hand.cardsInHand-1; //either move left, or to rightmost
                //reselect card
                player->hand.cards[index]->selected = true;
            } else if (c == RIGHT) {
                //deselect current card
                player->hand.cards[index]->selected = false;
                //increase index
                index = index < player->hand.cardsInHand-1 ? index+1: 0; //either move right, or to first
                //reselect card
                player->hand.cards[index]->selected = true;
            }
            getc(stdin); //this clears the last "enter" in buffer
        }
        //break;
    } 

}

/*
Select two cards to send to the crib
*/
void selectCardsForCribWithCPU() {
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
    //copy card pointer to crib
    players[dealer].crib.cards[countCardsInCrib(&players[dealer])] = hand->cards[index];
    players[dealer].crib.cardsInHand++; //increase
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
    hand->cardsInHand--;//decrease
}

void playersInit() {
    // proper functions assigned
    players[0].selectCardsForCrib = &selectCardsForCribWithCPU;
    players[1].playPeggingCard = &pegWithInput;
    players[1].selectCardsForCrib = &selectCardsForCribWithInput;
    players[0].playPeggingCard = &pegWithCPU;

    players[1].score=0;
    players[0].score=0;
}
