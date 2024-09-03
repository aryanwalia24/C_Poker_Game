#include "game.h"
#include "player.h"
#include "deck.h"

int main()
{
    Player *players = NULL;
    int numPlayers = 0;
    Deck deck;

    startGame(&players, &numPlayers, &deck);

    return 0;
}