#ifndef BOARD_H
#define BOARD_H

#include <stdio.h> //io
#include <stdlib.h> //system commands
#include "config.h" //screen size
#include "player.h" //card, hand, enums
#include <string.h>
#include <locale.h> //unicode
#include <wchar.h> //unicode

#define BOARD_WIDTH 80
#define BOARD_HEIGHT 25

//escape sequences for changing colors
const char const *RED = "\x1B[31m";
const char const *GREEN = "\x1B[32m";
const char const *RESET_COLOR = "\x1b[36m";

//don't change these
const int CARD_WIDTH = 3; //minimum 3 (adds two for edges)
const int CARD_HEIGHT = 3;

int screenSize[] = {BOARD_HEIGHT,BOARD_WIDTH}; //row, column

enum gameMessages {BILL_HAND_TXT,PLAYER_HAND_TXT,DECK_TXT,POINTS_TXT,PEGGING_TXT,SCORE_TXT,PLAYER_TXT,BILL_TXT,CONSOLE_TXT}; //output types correspond to a message

//Each string that needs to be printed
char *gameMessages[] = {"Bill's Hand","Player's Hand","Deck","Points: ","Pegging","Score","Player: ","Bill: ","Console: "};
char dealerMessages[2][13] = {"Dealer's Crib",""};

char consoleMessage[BOARD_WIDTH]; //Message that displays current information about game

char messsageBuffer[100]; //A buffer for the scoring messages (easier to input numbers and such)

//positions of each element on the board

//x,y pair for beginning of each element
struct position {
    int y;
    int x;
};

/*
contains a map of tuples, each tuple represents a starting point for a certain element
this is mapped to a list of printable objects (which have a pointer to some memory location)
*/
struct position positions[] = {  {1,15}, {1,45}, //player 1 hand and crib text
                                 {2,0}, {2,38}, //player 1 hand and crib
                                 {3,60}, //player 1 dealer text
                                 {5,0}, {5,8}, {5,40}, {5,48}, //player 1 points
                                 {7,0}, //deck text
                                 {8,0}, //deck
                                 {10,20}, {10,30},//pegging text, and current count
                                 {12,0}, {12,55}, //pegging cards, score text
                                 {12,50}, {12,58}, //player 1 score text, score
                                 {13,50}, {13,58}, //player 2 score text, score
                                 {14,0}, //pegging points {UNUSED}
                                 {18,15}, {18,45}, //player 2 hand and crib text
                                 {19,0}, {19,38}, //player 2 hand and crib
                                 {20,60},
                                 {22,0}, {22,8}, {22,40}, {22,48}, //player 2 points
                                 {24,0} //console
};
/*
Based on the board outlined in map.h
*/ 
enum POSITIONS {PLAYER1_TEXT,PLAYER1_CRIB_TEXT,
                PLAYER1_HAND,PLAYER1_CRIB,
                PLAYER1_DEALER_TAG,
                PLAYER1_POINTS_TEXT,PLAYER1_POINTS,PLAYER1_CRIB_POINTS_TEXT,PLAYER1_CRIB_POINTS, //PLAYER 1 SECTION
                DECK_TEXT,
                DECK,
                PEGGING_TEXT, PEGGING_COUNT,
                PEGGING_CARDS,SCORE_TEXT,
                PLAYER1_SCORE_TEXT, PLAYER1_SCORE,
                PLAYER2_SCORE_TEXT, PLAYER2_SCORE,
                PEGGING_POINTS, 
                PLAYER2_TEXT,PLAYER2_CRIB_TEXT,
                PLAYER2_HAND,PLAYER2_CRIB,
                PLAYER2_DEALER_TAG,
                PLAYER2_POINTS_TEXT,PLAYER2_POINTS,PLAYER2_CRIB_POINTS_TEXT,PLAYER2_CRIB_POINTS, //PLAYER 2 SECTION
                CONSOLE //console prints out additional game messages to player
}; 


typedef enum {TEXT,NUMBER,CARD} Datatype;
//printable object
typedef struct {
    void *ptr; // point to data
    Datatype type; //type of data (card, string, int)
} Printable;

//board in memory, where printables can be inserted
Printable board[BOARD_HEIGHT][BOARD_WIDTH];

int suitSymbol[] = {0x2660,0x2665,0x2666,0x2663}; //unicode values
int wallSymbol[] = {0x2550,0x2551,0x2554,0x2557,0x255A,0x255D}; //unicode symbols for boarders

enum walls {HORIZONTAL,VERTICAL,TOP_LEFT,TOP_RIGHT,BOTTOM_LEFT,BOTTOM_RIGHT}; //correspond 

void boardInit(); //initialize board
void draw(); //draw board to screen
int drawPartOfCard(Card*, int); //draws part of card specified
void spChar(wchar_t); //print special characters
void setPos(Datatype,enum POSITIONS, void* ); //set positions of screen objects
void setHand(int,enum POSITIONS, void*);
void setPosForHand(Hand*, enum POSITIONS, char); //set the position for each card in a hand
void setPosForCard(void*,int,int); //set position for an individual card
void setPosForPegging(); //set positions for a pegging slot, containing a card and points
void console(char*); //print a message to console
void clrConsole();
void announceWin(Player*,Player*); //print out who won, with how many points, etc

#endif