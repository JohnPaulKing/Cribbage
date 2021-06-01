#include "pegging.h"
#include "game.h"
#include "player.h"
#include <stdio.h>


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
    pegging[peggingCardsPlayed].points = 0; //this gets updated later
    peggingCardsPlayed++; //increase global var to account for card added
    peggingCardsSinceReset++; //same deal
    
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
    //reset values
    peggingCardsPlayed = peggingCardsSinceReset = 0;

    //start with non-dealer
    //while all cards have not yet been pegged
    //and while game not won
    char numberAdded; //the "value of the card" played, face value for A-10, 10 for j,q,k
    bool go = false; // simbolizes that last player said "go"
    for (currentPegger = !dealer ;!gameWon && peggingCardsPlayed < CRIB_SIZE*2; ) {
        numberAdded= players[currentPegger].playPeggingCard(); //whether player able to play card
        //play pegging card also calls sendCardToPegging
        if (numberAdded) { //a card is sucessfully played (0 if no card played)
            /*
            todo, get scoring of last card played
            */
            peggingCount += numberAdded; //add the value of the pegged card to the total. if 15, and a J is played, count is 25
            pegging[peggingCardsPlayed-1].points = scorePegging(); //calculate the scoring of last card played
            players[currentPegger].score += pegging[peggingCardsPlayed-1].points; //adds the point of last card played
            draw(); //draw screen
            if (players[currentPegger].score >= WIN_NUMBER) {
                gameWon = true; //game has been won, return
                return;
            }
            
        } else if (go) { //if last player said go
            go = false; //reset
            peggingCount = 0; //reset the counter
            peggingCardsSinceReset = 0;
            players[currentPegger].score += GO; //points for go go (or last)
            pegging[peggingCardsPlayed].points += GO; //represent this visually
        } else {
            go = true; //unable to play
        }
        currentPegger = !currentPegger; // switch the pegging player
        
    }
    console("Press enter to continue to scoring");
    //return cards to hands
    for (char i = 0; i < peggingCardsPlayed; i++) {
        bool owner = pegging[i].owner;
        players[owner].hand.cards[players[owner].hand.cardsInHand++] = pegging[i].card; //give card back to owner
        //also increment the cards in hand
        pegging[i] = (PeggingSlot) {NULL,0,0}; //reset the pegging slot
    }
    
    getc(stdin);
    console(" ");
}
