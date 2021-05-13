#ifndef CARD_H
#define CARD_H

#include <stdbool.h> //booleans

#define JACK 11
#define QUEEN 12
#define KING 13

typedef enum {SPADE,HEART,DIAMOND,CLUB} Suit;

/*
Card structure. Each card has a suit and type
Additionally, it can either be hidden or revealed
One card at a time may also be selected
*/
typedef struct{
    Suit suit; //suit of card
    unsigned char type; //Ace-9, J,Q,K
    bool hidden; //whether the cards value is shown or hidden
    bool selected; //whether current card is selected
} Card;

#endif