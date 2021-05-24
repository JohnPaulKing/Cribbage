#include "board.h"
#include "game.h"
#include "deck.h"

#define BUFFER_SIZE 15 //max characters in string

void boardInit() {
    strcpy(consoleMessage,"board under development");
    char *locale = setlocale(LC_ALL, ""); //set up unicode printing
    //set positions of text on data map
    setPos(TEXT,PLAYER1_TEXT,gameMessages[BILL_HAND_TXT]);
    setPos(TEXT,PLAYER1_CRIB_TEXT,gameMessages[CRIB_TXT]);
    setPos(TEXT,PLAYER1_POINTS_TEXT,gameMessages[POINTS_TXT]);
    setPos(TEXT,PLAYER1_CRIB_POINTS_TEXT,gameMessages[POINTS_TXT]);
    setPos(TEXT,DECK_TEXT,gameMessages[DECK_TXT]);
    setPos(TEXT,PEGGING_TEXT,gameMessages[PEGGING_TXT]);
    setPos(TEXT,SCORE_TEXT,gameMessages[POINTS_TXT]);
    setPos(TEXT,PEGGING_TEXT,gameMessages[PEGGING_TXT]);
    setPos(TEXT,SCORE_TEXT,gameMessages[SCORE_TXT]);
    setPos(TEXT,PLAYER1_SCORE_TEXT,gameMessages[BILL_TXT]);
    setPos(TEXT,PLAYER2_SCORE_TEXT,gameMessages[PLAYER_TXT]);
    setPos(TEXT,PLAYER2_TEXT,gameMessages[PLAYER_HAND_TXT]);
    setPos(TEXT,PLAYER2_CRIB_TEXT,gameMessages[CRIB_TXT]);
    setPos(TEXT,PLAYER2_POINTS_TEXT,gameMessages[POINTS_TXT]);
    setPos(TEXT,PLAYER2_CRIB_POINTS_TEXT,gameMessages[POINTS_TXT]);
    setPos(TEXT,CONSOLE,consoleMessage);
    //set positions of numbers 
    setPos(NUMBER,PLAYER1_POINTS,&players[0].hand.points); //player 0's hand points
    setPos(NUMBER,PLAYER1_CRIB_POINTS,&players[0].crib.points); //player 0's crib points
    setPos(NUMBER,PLAYER1_SCORE,&players[0].score); //player 0's overall score
    setPos(NUMBER,PLAYER2_SCORE,&players[1].score); //playyer 1's overall score
    setPos(NUMBER,PLAYER2_POINTS,&players[1].hand.points); //player 1's hand points
    setPos(NUMBER,PLAYER2_CRIB_POINTS,&players[1].crib.points); //player 1's crib points
    //for each pegging points
    //set positions of card slots
    //print series of cards
    setPosForHand(&players[0].hand,PLAYER1_HAND,HAND_SIZE); //player 0's hand
    setPosForHand(&players[0].crib,PLAYER1_CRIB,CRIB_SIZE); //player 0 crib
    setPosForHand(&players[1].crib,PLAYER2_CRIB,CRIB_SIZE); //player 0 crib
    setPosForHand(&players[1].hand,PLAYER2_HAND,HAND_SIZE); //player 1's hand
    //set position for the "cut card" or top card
    setPos(CARD,DECK,&topCard);
}

void setPosForPegging(){
    //for each pegging card
    for (char i = 0; i < peggingCardsPlayed; i++) {
        //first set positions for the card
        char y = positions[PEGGING_CARDS].y + pegging[i].owner; //offset slightly based on who played card
        char x = positions[PEGGING_CARDS].x + ((CARD_WIDTH+3)*i); //offset for each card
        setPosForCard(&pegging[i].card,y,x); //set position
        y += (pegging[i].owner) ? -1 : 3; //offset to either above or below card
        x+=2; //center of the card
        //set positions mauaslly
        board[y][x].ptr = &pegging[i].points;
        board[y][x].type = NUMBER;
    }
}

void draw(){
    printf("%s",RESET_COLOR); //default color
    setPosForPegging(); //set dynamically set pegging cards
    system("clear"); //clear console
    Printable *node;
    for (int y = 0; y < BOARD_HEIGHT; y++) {

        for (int x = 0; x < BOARD_WIDTH; ) { //don't increase x here
            node = &board[y][x];
            if (node->ptr) { //if valid pointer
                if (node->type == NUMBER) {
                    //print as dereferenced int pointer
                    //print as 3 numbers always
                    char str[BUFFER_SIZE];
                    //print to buffer
                    snprintf(str,BUFFER_SIZE,"%d",(* (int*) (node->ptr)));
                    printf("%s",str); //changed from %sd ? is this a bug? 
                    //increase x by number of chars printed
                    x+= strlen(str); //length of score, 
                } else if (node->type >= CARD) {
                    
                    //starting at value CARD, type is incremented with each part of the card
                    if (*(Card**)(node->ptr)) { //if valid card
                        x+= drawPartOfCard((* (Card**) (node->ptr)),(node->type-CARD));
                    } else {
                        x++;
                        printf(" ");//move to the right
                    }
                    //note to mark rest of card
                } else if (node->type == TEXT) {
                    printf("%s",(char*) (node->ptr));
                    x+= strlen((char*) (node->ptr));
                }
            } else {
                x++; //increase one space
                printf(" ");//move to the right
            }
        } printf("\n");//new line
    }


    /* draw a card
    struct card c = {HEART,KING,true,false};
    for (int i = 0; i < 5; i++) {
        drawPartOfCard(&c,i);
        printf("\n");
    }
    */

    //reset console graphics
    printf("%s",RESET_COLOR); 
}

//print special character (unicode)
void spChar(wchar_t c) {
    printf("%lc",c);
    //putwchar(c);
}
//reevaluate height of card TODO
int drawPartOfCard(Card *card, int partOfCard) {
    //compiler throws warning if not const
    const char *color = (card->selected) ? RED : GREEN;
    printf("%s",color); //change color of text
    switch (partOfCard) {
        case 0: //top row
            spChar(wallSymbol[TOP_LEFT]);
            for (int i = 0; i < CARD_WIDTH; i++) {
                spChar(wallSymbol[HORIZONTAL]);
            }
            spChar(wallSymbol[TOP_RIGHT]);
            break;
        case 1: //center row
            spChar(wallSymbol[VERTICAL]);
            if (card->hidden) { //print question marks
                for (int i = 0; i < CARD_WIDTH; i++) {
                    printf("%c",'?');
                }
            } else { //print suit|value|suit
                spChar(suitSymbol[card->suit]);
                if (card-> type == 1) {
                    printf("%c",'A'); //Ace
                } else if (card->type < 10){
                    printf("%d",card->type);
                } else if (card-> type == 10) {
                    printf("%c",'X'); //10 is two characters and would mess things up
                } else if (card->type == 11) {
                    printf("%c",'J');
                } else if (card->type == 12) {
                    printf("%c",'Q');
                } else if (card->type == 13) {
                    printf("%c",'K');
                }
                spChar(suitSymbol[card->suit]);
            }
            spChar(wallSymbol[VERTICAL]);
            break;
        case 2:
            spChar(wallSymbol[BOTTOM_LEFT]);
            for (int i = 0; i < CARD_WIDTH; i++) {
                spChar(wallSymbol[HORIZONTAL]);
            }
            spChar(wallSymbol[BOTTOM_RIGHT]);
            //printf("%s",RESET_COLOR); //reset the color after the last part has been printeed
            break;
    }
    printf("%s",RESET_COLOR); //default color
    return CARD_WIDTH +2; //amount of characters printed
}

//for a certain size of hand, will call set pos
void setHand(int length, enum POSITIONS pos, void* ptr){
    for (int i = 0; i < length; i++) {
        setPos(CARD, pos, ptr);
    }
}

// pass in a pointer and some position info, and this creates the printables
void setPos(Datatype type,enum POSITIONS pos, void* ptr) {
    //set pointers
    if (type == TEXT || type == NUMBER) {
        //set the printable at this pos to this ptr;
        board[positions[pos].y][positions[pos].x].ptr = ptr;
        board[positions[pos].y][positions[pos].x].type = type;
    } else { //if type == card
        /*
        Because cards take up vertical space, each vertical part has to have its pointer "stored" on the board
        As well as which part it is. The type is of course card (the last type), so we add to that which part it is
        Meaning CARD is the first layer of a card, CARD+1 the next, etc
        */
        for (char i = 0; i < CARD_HEIGHT; i++) {
            //add pointer to each position of the card vertically
            setPosForCard(ptr,positions[pos].y,positions[pos].x);
        }
    }
}

/*
set the position for each part of the card
*/
void setPosForCard(void* ptr,int y, int x) {
        //if card pointer not null
        //if (* (Card**) ptr) { //convert to a pointer to a pointer to a card, dereference
        for (char i = 0; i < CARD_HEIGHT; i++) {
            //add pointer to each position of the card vertically
            board[y+i][x].ptr = ptr;
            //mark which part of the card
            board[y+i][x].type = CARD+i;
        }
        //}
}

/*
Calls set pos for each card in a hand of size size

*/
void setPosForHand(Hand* hand, enum POSITIONS pos, char size){
    //for each card, set its position
    for (char i = 0; i < size; i++) {
        /*
        This function calls the set pos for cards
        First it converts the card pointer pointer into a void pointer
        Then it passes in the y pos, and the x pos, which is modified by the amount of cards printed so far
        */
        setPosForCard((void*) &(hand->cards[i]),positions[pos].y,positions[pos].x + ((CARD_WIDTH+3)*i));
    }
}



