#include <stdio.h>
#include "game.h"

int main()
{
    Player players[2];
    int numPlayers = 0;
    Deck deck;

    startGame(players, &numPlayers, &deck);
    return 0;
}
