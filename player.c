#include "player.h"


//makes all cards visible
void revealCards(Hand* hand ) {
    for (char i = 0; i < HAND_SIZE; i++) {
        hand->cards[i]->hidden = !hand->cards[i]->hidden;
    }
}