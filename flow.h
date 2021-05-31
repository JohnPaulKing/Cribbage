/*
THIS FILE IS ONLY DOCUMENTATION AND PSEUDOCODE

The game flows as follows:

Basic game setup
    initiating cards
    initiating player info
    initiating board positions

Until game won:
    round:
        selecting cards for crib (CPU)
        selecting cards for crib (player)
        for 0-7, starting with !dealer:
            play pegging card
                verify card
                count points
                add total, etc
                detirmine next pegger
            draw screen
            change console message
            break if gamewon
        return cards to hand
        draw
*/