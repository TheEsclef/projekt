#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include "rockpaperscissors.h"
#include "cryption.h"

// Function for when the user asks for HELP
int helpCommand()
{
    system("cls");
    printf("Available commands: \n \t"
           "encrypt - Asks for input and encrypts the input \n \t"
           "decrypt - Asks for input and decrypts the input\n \t"
           "games - lists games available to be played\n \t"
           "exit - Exits the program\n");
}

// Function to ask the user which game he'd like to play
int gameAskCommand()
{
    system("cls");
    printf(
        "Select a game from the list: \n"
        "\t1. Rock Paper Scissors \n"
        "\t2. TicTacToe \n");

    int subCommand;           // Variable to store the user's choice of game
    scanf("%d", &subCommand); // Read the user's choice from input
    switch (subCommand)
    {
    case 1: // User picks "Rock Paper Scissors"
        RPSgame();
        break;
    case 2: // User picks "TicTacToe"
        printf("tictactoe");
        break;
    default:
        printf("INVALID");
        break;
    }
}

int main()
{
    char command[100]; // Declare variable for user input and commands

    printf("big dick john is waiting for your command ;) \n"); // greet the user with a nice and friendly message

    while (true) // Infinite loop to continuously prompt the user for commands
    {
        scanf("%s",command); // Read the user's command from input
        strlwr(command);        
        // if the user inputs "Help"
        if (strcmp(command, "help") == 0)
        {
            helpCommand();
        }

        // User inputs "encrypt"
        else if (strcmp(command, "encrypt") == 0)
        {
            encryptAskCommand(); // Run the encrypt function
        }

        // User inputs "decrypt"
        else if (strcmp(command, "decrypt") == 0)
        {
            decryptAskCommand(); // Run the decrypt function
        }

        // User inputs "exit"
        else if (strcmp(command, "exit") == 0)
        {
            printf("cya later alligator.\n");
            break; // Exit the loop and terminate the program
        }

        else if (strcmp(command, "games") == 0)
        {
            gameAskCommand();
        }

        else
        {
            printf("Unknown command. Type \"help\" for a list of commands.\n");
        } // Handle unknown commands
    }

    return 0;
}