#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/game.h"
#include "../include/player.h"
#include "../include/deck.h"
#include "../include/poker_hand.h"

void test_setBlinds()
{
    Player players[2];
    createPlayer(1, "Alice", 1000, &players[0]);
    createPlayer(2, "Bob", 1000, &players[1]);

    setBlinds(players, 2);

    assert(players[0].wallet == 1000 - SMALL_BLIND);
    assert(players[1].wallet == 1000 - BIG_BLIND);
}

void test_dealCards()
{
    Player players[2];
    Deck deck;

    createPlayer(1, "Alice", 1000, &players[0]);
    createPlayer(2, "Bob", 1000, &players[1]);
    initialiseDeck(&deck);
    shuffleDeck(&deck);

    dealCards(players, 2, &deck);

    for (int i = 0; i < 2; i++)
    {
        assert(players[i].hand != NULL);
        assert(getCardValue(players[i].hand[0]) > 0);
        assert(getCardValue(players[i].hand[1]) > 0);
    }
}

void test_executeBettingRound()
{
    Player players[2];
    Deck deck;
    Card communityCards[5];
    int pot = INITIAL_POT;

    createPlayer(1, "Alice", 1000, &players[0]);
    createPlayer(2, "Bob", 1000, &players[1]);
    initialiseDeck(&deck);
    shuffleDeck(&deck);

    dealCards(players, 2, &deck);
    for (int i = 0; i < 5; i++)
    {
        communityCards[i] = drawCard(&deck);
    }

    executeBettingRound(players, 2, communityCards, &pot);

    assert(pot >= INITIAL_POT);
    for (int i = 0; i < 2; i++)
    {
        assert(players[i].wallet >= 0);
    }
}

void test_determineWinner()
{
    Player players[2];
    Deck deck;
    Card communityCards[5];
    int pot = INITIAL_POT;

    createPlayer(1, "Alice", 1000, &players[0]);
    createPlayer(2, "Bob", 1000, &players[1]);
    initialiseDeck(&deck);
    shuffleDeck(&deck);

    dealCards(players, 2, &deck);
    for (int i = 0; i < 5; i++)
    {
        communityCards[i] = drawCard(&deck);
    }

    determineWinner(players, 2, communityCards, &pot);

    assert(players[0].wallet == 1000 + pot || players[1].wallet == 1000 + pot);
}

void test_displayPlayerCards()
{
    Player player;
    createPlayer(1, "Alice", 1000, &player);
    player.hand = (Card *)malloc(2 * sizeof(Card));
    player.hand[0] = (mapSuitToNumber('H') << VALUE_BITS) | 10;
    player.hand[1] = (mapSuitToNumber('S') << VALUE_BITS) | 11;

    player.pin = 1234;
    printf("Enter PIN to display Alice's cards: 1234\n");
    displayPlayerCards(&player, 1);

    free(player.hand);
}

void test_displayCommunityCards()
{
    Deck deck;
    initialiseDeck(&deck);
    shuffleDeck(&deck);

    Card communityCards[5];
    for (int i = 0; i < 5; i++)
    {
        communityCards[i] = drawCard(&deck);
    }

    displayCommunityCards(communityCards, 5);
}

void test_burnCard()
{
    Deck deck;
    initialiseDeck(&deck);
    shuffleDeck(&deck);

    int initialTop = deck.top;
    burnCard(&deck);
    assert(deck.top == initialTop + 1);

    cleanupDeck(&deck);
}

void test_handleFlop()
{
    Deck deck;
    initialiseDeck(&deck);
    shuffleDeck(&deck);

    Card communityCards[5];
    for (int i = 0; i < 3; i++)
    {
        communityCards[i] = drawCard(&deck);
    }

    handleFlop(&deck, communityCards);
}

void test_handleTurn()
{
    Deck deck;
    initialiseDeck(&deck);
    shuffleDeck(&deck);

    Card communityCards[5];
    for (int i = 0; i < 3; i++)
    {
        communityCards[i] = drawCard(&deck);
    }

    handleTurn(&deck, communityCards);
}

void test_handleRiver()
{
    Deck deck;
    initialiseDeck(&deck);
    shuffleDeck(&deck);

    Card communityCards[5];
    for (int i = 0; i < 4; i++)
    {
        communityCards[i] = drawCard(&deck);
    }

    handleRiver(&deck, communityCards);
}

int main()
{
    test_setBlinds();
    test_dealCards();
    test_executeBettingRound();
    test_determineWinner();
    test_displayPlayerCards();
    test_displayCommunityCards();
    test_burnCard();
    test_handleFlop();
    test_handleTurn();
    test_handleRiver();

    printf("All tests passed!\n");
    return 0;
}