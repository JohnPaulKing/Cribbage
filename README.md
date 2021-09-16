# Cribbage

This is a project I made in my free time to get more familiar with the C programming language, and basic game programming in terminal.

#Limitations (Will be addressed in future updates)
1. For now, this game only runs correctly on unix operating systems.
2. Depending on the shell you use, the arrow keys will not move the selected cards. You will have to enter an arrow key and then press enter, in order for the shell to send the text to the process.
3. The next planned feature is the option to pass in parameters to select gamemode, as well as players name and debug config options. For now these are stored in config.h and the code must be recompiled for each change. 

#How to Play
After compiling game.c, the executable can be run. 
config.h has the following options:
Difficulty: may either be set to EASY, MOODERATE, and HARD
PLAYER_NAME: the name of the human player
COMPUTER_NAME: the name of the player simulated by the computer

config.h has the following debugging options as well:
CLEAR_SCREEN_ON_REFRESH: if set to false, the screen will not be cleared, leaving old game states present on screen for debugging
HIDE_CARDS: if set to false, opponents cards will not be hidden, which is also useful for debugging.

The gameplay is simple, and relies on an understanding of the card game Cribbage (https://en.wikipedia.org/wiki/Cribbage)
The player will be instructed through on screen messages to select a card from their hand. They must navigate between their cards using left and right arrow keys (see note above about pressing enter to send the arrow key input to program) and then when they have selected a card, the player presses enter. 

#Overview of modules
board.h/board.c: functions to keep track of where cards are layed out, and to print out the cards, and refresh the screen
card.h: types and definitions for cards
config: settings, including debugging settings
deck.h/deck.c: types and definitions for a deck of cards, as well as algorithms to initialize, shuffle, deal, and cut the deck
game.h/game.c: main game loop and operations, as well as static memory definitions
pegging.h/pegging.c: algorithms for selecting and scoring cards during pegging phase
player.h/player.c: types and definitions for player, as well as algorithms for player selections
scoring.h/scoring.c: algorithms to score hands
