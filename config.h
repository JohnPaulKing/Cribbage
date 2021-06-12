#ifndef CONFIG_H
#define CONFIG_H
#include "game.h"

//whether to clear the screen before reprinting board
bool CLEAR_SCREEN_ON_REFRESH = true;


//EASY, MODERATE, HARD
//OR 0, 1, 2
Difficulty GAME_DIFFICULTY = HARD;

//Player names
const char *const PLAYER_NAME = "Player";
const char *const COMPUTER_NAME = "JP";


//For debugging, this can be set to false to see the computer's cards
bool HIDE_CARDS = true;




#endif