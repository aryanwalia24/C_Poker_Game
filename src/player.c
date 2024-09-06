#include "../include/player.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int createPlayer(int id, const char *name, int startMoney, Player *player)
{
    player->id = id;
    player->name = (char *)calloc(MAX_NAME_LENGTH, sizeof(char));
    if (name == NULL || strlen(name) == 0)
    {
        strncpy(player->name, "Guest", MAX_NAME_LENGTH - 1);
    }
    else
    {
        strncpy(player->name, name, MAX_NAME_LENGTH - 1);
    }
    player->name[MAX_NAME_LENGTH - 1] = '\0';

    player->wallet = startMoney;
    player->pin = 0;

    player->hand = (Card *)calloc(HAND_SIZE, sizeof(Card));
    if (player->hand == NULL)
    {
        fprintf(stderr, "Memory allocation failed for player hand.\n");
        free(player->name);
        return -1;
    }

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

void setPlayerPin(Player *player)
{
    if (player == NULL)
    {
        fprintf(stderr, "Error: Player pointer is null.\n");
        return;
    }

    printf("Set a PIN for %s: ", player->name);
    player->pin = getValidInt(1000, 9999, "Enter PIN: ");
}

int validatePlayerPin(const Player *player)
{
    if (player == NULL)
    {
        fprintf(stderr, "Error: Player pointer is null.\n");
        return 0;
    }

    int enteredPin;
    printf("Enter PIN to view your cards: ");
    enteredPin = getValidInt(1000, 9999, "Enter PIN: ");
    return enteredPin == player->pin;
}

void displayPlayerCardsSimple(const Player *player)
{
    if (player == NULL)
    {
        fprintf(stderr, "Error: Player pointer is null.\n");
        return;
    }

    printf("%s's cards: ", player->name);
    for (int i = 0; i < HAND_SIZE; i++)
    {
        printCard(player->hand[i]);
    }
    printf("\n");
}

void freePlayer(Player *player)
{
    if (player->name != NULL)
    {
        free(player->name);
        player->name = NULL;
    }
    if (player->hand != NULL)
    {
        free(player->hand);
        player->hand = NULL;
    }
}

void clearConsole()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int getValidInt(int min, int max, const char *prompt)
{
    int value;
    int result;
    do
    {
        printf("%s", prompt);
        result = scanf("%d", &value);
        while (getchar() != '\n')
            ;
        if (result != 1 || value < min || value > max)
        {
            printf("Invalid input. Please enter a number between %d and %d.\n", min, max);
        }
    } while (result != 1 || value < min || value > max);

    return value;
}