#ifndef BOARD_H
#define BOARD_H

#include <stdio.h> //io
#include <stdlib.h> //system commands
#include "config.h" //screen size
#include "player.h" //card, hand, enums
#include <string.h>
#include <locale.h> //unicode
#include <wchar.h> //unicode

//escape sequences for changing colors
//TODO make constants
const char const *RED = "\x1B[31m";
const char const *GREEN = "\x1B[32m";
const char const *RESET_COLOR = "\x1B[0m";

int screenSize[] = {BOARD_HEIGHT,BOARD_WIDTH}; //row, column

enum gameMessages {BILL_HAND_TXT,PLAYER_HAND_TXT,CRIB_TXT,DECK_TXT,POINTS_TXT,PEGGING_TXT,SCORE_TXT,PLAYER_TXT,BILL_TXT,CONSOLE_TXT}; //output types correspond to a message

//Each string that needs to be printed
char *gameMessages[] = {"Bill's Hand","Player's Hand","Crib","Deck","Points: ","Pegging","Score","Player: ","Bill","Console: "};

char *consoleMessage; //Message that displays current information about game

//positions of each element on the board

//x,y pair for beginning of each element
struct position {
    int y;
    int x;
};


struct position positions[] = {  {1,15}, {1,45}, //player 1 hand and crib text
                                 {2,0}, {2,38}, //player 1 hand and crib
                                 {5,0}, {5,17}, {5,25}, {5,55}, //player 1 points
                                 {7,0}, //deck text
                                 {8,0}, //deck
                                 {10,14}, //pegging text
                                 {11,0}, {11,55}, //pegging cards, score text
                                 {12,55}, {12,65}, //player 1 score text, score
                                 {13,55}, {13,65}, //player 2 score text, score
                                 {14,0}, //pegging points
                                 {16,15}, {16,45}, //player 2 hand and crib text
                                 {17,0}, {17,38}, //player 2 hand and crib
                                 {20,0}, {20,17}, {20,25}, {20,55}, //player 2 points
                                 {22,0} //console
};
/*
Based on the board outlined in map.h
*/ 
enum POSITIONS {PLAYER1_TEXT,PLAYER1_CRIB_TEXT,
                PLAYER1_HAND,PLAYER1_CRIB,
                PLAYER1_POINTS_TEXT,PLAYER1_POINTS,PLAYER1_CRIB_POINTS_TEXT,PLAYER1_CRIB_POINTS, //PLAYER 1 SECTION
                DECK_TEXT,
                DECK,
                PEGGING_TEXT,
                PEGGING_CARDS,SCORE_TEXT,
                PLAYER1_SCORE_TEXT, PLAYER1_SCORE,
                PLAYER2_SCORE_TEXT, PLAYER2_SCORE,
                PEGGING_POINTS, 
                PLAYER2_TEXT,PLAYER2_CRIB_TEXT,
                PLAYER2_HAND,PLAYER2_CRIB,
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
void setPos(Datatype,enum POSITIONS, void* );
void setHand(int,enum POSITIONS, void*);

#endif