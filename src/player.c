#include "../include/player.h"

int createPlayer(int id, char *name, int startMoney, Player *player)
{
    // checking errors
    if (id < 0)
    {
        fprintf(stderr, "Error: Player ID must be a non-negative integer.\n");
        return -1;
    }
    if (name == NULL || strlen(name) == 0)
    {
        fprintf(stderr, "Error: Player name cannot be null or empty.\n");
        return -1;
    }
    if (startMoney < 0)
    {
        fprintf(stderr, "Error: Start money cannot be negative.\n");
        return -1;
    }
    if (player == NULL)
    {
        fprintf(stderr, "Error: Player pointer is null.\n");
        return -1;
    }
    // intializing data for player
    player->id = id;
    strncpy(player->name, name, MAX_NAME_LENGTH - 1);
    player->name[MAX_NAME_LENGTH - 1] = '\0'; // char array last item '\0'
    player->wallet = startMoney;
    return 0;
}

int updateWallet(Player *player, int amount)
{
    if (player == NULL)
    {
        fprintf(stderr, "Error: Player pointer is null.\n");
        return -1;
    }
    if (amount < 0 && player->wallet + amount < 0)
    {
        fprintf(stderr, "Error: Insufficient funds in the wallet.\n");
        return -1;
    }
    // amount can be -ve or +ve
    player->wallet += amount;
    return 0;
}

int getWallet(const Player *player, int *balance)
{
    if (player == NULL || balance == NULL)
    {
        fprintf(stderr, "Error: Player or balance pointer is null.\n");
        return -1;
    }
    // updates the balance variable
    *balance = player->wallet;
    return 0;
}

void displayPlayer(const Player *player)
{
    if (player == NULL)
    {
        fprintf(stderr, "Error: Player pointer is null.\n");
        return;
    }

    printf("Player ID: %d\n", player->id);
    printf("Player Name: %s\n", player->name);
    printf("Wallet Balance: $%d\n", player->wallet);
}
