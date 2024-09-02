#include "../include/player.h"

int createPlayer(int id, const char *name, int startMoney, Player *player)
{
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

    player->id = id;
    strncpy(player->name, name, MAX_NAME_LENGTH - 1);
    player->name[MAX_NAME_LENGTH - 1] = '\0';
    player->wallet = startMoney;
    player->pin = 0; // Initialize PIN

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
    printCard(player->hand[0]);
    printCard(player->hand[1]);
    printf("\n");
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
    do
    {
        printf(prompt, max);
        scanf("%d", &value);
        while (getchar() != '\n') // Clear input buffer
            ;
    } while (value < min || value > max);
    return value;
}
