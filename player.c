#include "player.h"
#include "game.h"
#include "board.h"


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
void selectCardsForCribWithInput(){
    strcpy(consoleMessage,"select a card"); //print message
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
    //copy card pointer to peggingslot
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
    players[0].hand.points=0;
    players[1].hand.points=0;
}
