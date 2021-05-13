#include <stdio.h> //io
#include "board.h"
int x = 1;

//Show number of cards
int cardsInHand(Card *cards[]) {
    int length = 0; //length so far
    for (;cards[length];length++){} //if card is valid, move to next
    return length;
}

int main() {
    int x;
    x = -1 % 52;
    printf("x: %d\n",x);
}
