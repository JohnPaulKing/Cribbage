#include "pegging.h"
#include "game.h"
#include "player.h"

/*
A small function to test if a card can be played during pegging
It also returns the number value of the card, if playable
*/
char cardPeggable(Card* card) {
    //if the value of the card is over 10 (J,Q,or K, then it is 10 for pegging purposes)
    char value = (card->type > 10) ? 10 : card->type;
    if (value + peggingCount <= PEGGING_RESET) { //if the card doesnt go over 31
        return value;
    } else { //otherwise return a 0
        return 0; //this indicates card not playable
    }
}

/*
Much of this code, and the algorithm itself is taken from my sendCardsToCrib function
if I were to rewrite this project, I could consider making the pegging slots a hand in itself,
this could allow me to use the same function
As it is now, this is slighly redundant but might help with code clarity
*/
void sendCardToPegging(Hand* hand, char index, bool owner) {
    //copy card pointer to peggingslot
    pegging[peggingCardsPlayed].card = hand->cards[index];
    //keep track of owner
    pegging[peggingCardsPlayed].owner = owner;
    peggingCardsPlayed++; //increase to account for card added
    
    //now remove the card from the hand

    //collapse hand
    for (char i = index; i < HAND_SIZE-1 ;i++){
        //move the subsequent pointer down one
        hand->cards[i] = hand->cards[i + 1];
    }
    //finally, set last index to null
    hand->cards[HAND_SIZE-1] = NULL;
    hand->cardsInHand--;//decrease
}

void pegger () {

    //start with non-dealer
    //while all cards have not yet been pegged
    //and while game not won
    char numberAdded; //the "value of the card" played, face value for A-10, 10 for j,q,k
    bool go = false; // simbolizes that last player said "go"
    for (currentPegger = !dealer ;!gameWon && peggingCardsPlayed <= CRIB_SIZE*2; ) {
        numberAdded= players[currentPegger].playPeggingCard(); //whether player able to play card
        draw(); //draw screen
        if (numberAdded) { //a card is sucessfully played (0 if no card played)
            /*
            todo, get scoring of last card played
            */
            peggingCardsPlayed++; //increase the number played
            peggingCount += numberAdded; //add the value of the pegged card to the total. if 15, and a J is played, count is 25
            if (players[0].score >= WIN_NUMBER) {
                gameWon = true; //game has been won, return
                return;
            }
        } else if (go) { //if last player said go
            go = false; //reset
            peggingCount = 0; //reset the counter
            players[currentPegger].score += GO; //points for go go (or last)
        } else {
            go = true; //unable to play
        }
        currentPegger = !currentPegger; // switch the pegging player
        
    }
    if (gameWon) {
        //deal with this later
    }
    //return cards to hands
    for (char i = 0; i < peggingCardsPlayed; i++) {
        bool owner = pegging[i].owner;
        players[owner].hand.cards[players[owner].hand.cardsInHand] = pegging[i].card; //give card back to owner
        pegging[i] = (PeggingSlot) {NULL,0,0}; //reset the pegging slot
    }
}
