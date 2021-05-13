#include "board.h"
#include "game.h"


#define BUFFER_SIZE 15 //max characters in string

void boardInit() {
    consoleMessage = "board under development";
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
    setPos(NUMBER,PLAYER1_CRIB_POINTS,&crib.points); //player 0's crib points
    setPos(NUMBER,PLAYER1_SCORE,&players[0].score); //player 0's overall score
    setPos(NUMBER,PLAYER2_SCORE,&players[1].score); //playyer 1's overall score
    setPos(NUMBER,PLAYER2_POINTS,&players[1].hand.points); //player 1's hand points
    setPos(NUMBER,PLAYER2_CRIB_POINTS,&crib.points); //player 1's crib points
    //for each pegging points

    //set positions of card slots
    //print series of cards
    setPos(CARD,PLAYER1_HAND,&players[0].hand.cards[0]); //player 0's hand
    //setPos(CARD,PLAYER1_CRIB,&crib->cards); //player 0 crib
    //setPos(CARD,PLAYER2_CRIB,&crib->cards); //player 1 crib
    setPos(CARD,PLAYER2_HAND,&players[1].hand.cards[0]); //player 1's hand
    //for each pegging card

    
}

void draw(){
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
                    x+= drawPartOfCard((* (Card**) (node->ptr)),(node->type-CARD));
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
                if (card->type < 10){
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
            board[positions[pos].y+i][positions[pos].x].ptr = ptr;
            //mark which part of the card
            board[positions[pos].y+i][positions[pos].x].type = type+i;

            //this commented out print demonstrates that each card is held in the correct position
            //printf("position: x%d, y%d, type:%d\n",positions[pos].x,positions[pos].y+i,board[positions[pos].y+i][positions[pos].x].type);
        }
    }
}

