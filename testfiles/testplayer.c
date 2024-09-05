#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../include/player.h"
#include "../include/card.h"

void test_createPlayer()
{
    Player player;
    int result = createPlayer(1, "Alice", 1000, &player);
    assert(result == 0);
    assert(player.id == 1);
    assert(strcmp(player.name, "Alice") == 0);
    assert(player.wallet == 1000);
    assert(player.hand != NULL);
    assert(player.pin == 0);
    freePlayer(&player);
}

void test_createPlayer_invalid()
{
    Player player;
    int result;

    result = createPlayer(-1, "Alice", 1000, &player);
    assert(result == -1);

    result = createPlayer(1, NULL, 1000, &player);
    assert(result == -1);

    result = createPlayer(1, "", 1000, &player);
    assert(result == -1);

    result = createPlayer(1, "Alice", -1000, &player);
    assert(result == -1);

    result = createPlayer(1, "Alice", 1000, NULL);
    assert(result == -1);
}

void test_updateWallet()
{
    Player player;
    createPlayer(1, "Alice", 1000, &player);

    int result = updateWallet(&player, 500);
    assert(result == 0);
    assert(player.wallet == 1500);

    result = updateWallet(&player, -200);
    assert(result == 0);
    assert(player.wallet == 1300);

    result = updateWallet(&player, -1400);
    assert(result == -1);
    assert(player.wallet == 1300);

    freePlayer(&player);
}

void test_getWallet()
{
    Player player;
    createPlayer(1, "Alice", 1000, &player);

    int balance;
    int result = getWallet(&player, &balance);
    assert(result == 0);
    assert(balance == 1000);

    result = getWallet(NULL, &balance);
    assert(result == -1);

    result = getWallet(&player, NULL);
    assert(result == -1);

    freePlayer(&player);
}

void test_displayPlayer()
{
    Player player;
    createPlayer(1, "Alice", 1000, &player);

    displayPlayer(&player);

    freePlayer(&player);
}

void test_setPlayerPin()
{
    Player player;
    createPlayer(1, "Alice", 1000, &player);

    freePlayer(&player);
}

void test_validatePlayerPin()
{
    Player player;
    createPlayer(1, "Alice", 1000, &player);

    freePlayer(&player);
}

void test_displayPlayerCardsSimple()
{
    Player player;
    createPlayer(1, "Alice", 1000, &player);

    displayPlayerCardsSimple(&player);

    freePlayer(&player);
}

void test_freePlayer()
{
    Player player;
    createPlayer(1, "Alice", 1000, &player);

    freePlayer(&player);
    assert(player.name == NULL);
    assert(player.hand == NULL);
}

int main()
{
    printf("All the Errors are intentional\n");
    test_createPlayer();
    test_createPlayer_invalid();
    test_updateWallet();
    test_getWallet();
    test_displayPlayer();
    test_setPlayerPin();
    test_validatePlayerPin();
    test_displayPlayerCardsSimple();
    test_freePlayer();

    printf("All tests passed!\n");
    return 0;
}