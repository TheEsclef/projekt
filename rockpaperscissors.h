#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

char command[100]; // create variable to store user input

// ASKS THE USER FOR COMMANDS
int askUserCommand()
{
    system("cls"); // Clear the terminal, mainly for readability
    printf("---- WELCOME TO ROCK PAPER SCISSORS ----\n \t"
           "start - Begins the game of Rock Paper Scissors\n \t"
           "exit - Exits the game\n");

    scanf("%s", command); // Prompt the user on what he'd like to do
}

// ASKS THE USER FOR HIS MOVE
int askUserMove()
{
    int x;
    printf("CHOOSE YOUR MOVE\n \t"
           "1 - Rock\n \t"
           "2 - Paper\n \t"
           "3 - Scissors\n \t"
           "4 - Give up\n");
    scanf("%d", &x); // Ask the move
    return x;
}

// GENERATES THE COMPUTER MOVE
int computerMove()
{
    srand(time(NULL));        // C needs a seed in order to not generate the same random number over and over, for the seed we use time
    int x = (rand() % 3) + 1; // gets a random integer between 1 and 3

    switch (x)
    {
    case 1:
        printf("Computer picked ROCK\n");
        break;
    case 2:
        printf("Computer picked PAPER\n");
        break;
    case 3:
        printf("Computer picked SCISSORS\n");
        break;
    }
    return x;
}

// HANDLES THE COMPARISON OF MOVES
int handleComparsion(int user, int computer)
{
    int x;
    if (user == computer)
    {
        x = 0;
    } // Draw

    else if ((user == 1 && computer == 3) || // ROCK BEATS SCISSORS
             (user == 2 && computer == 1) || // PAPER BEATS ROCK
             (user == 3 && computer == 2))   // SCISSORS BEATS PAPER
    {
        x = 1;
    } // User Wins
    else
    {
        x = 2;
    } // User loses
    return x;
}

int rockPaperScissors()
{
    askUserCommand();
    if (strcmp(command, "start") == 0) // User chooses to begin the game
    {
        bool gameEnded = false; // Create a boolean to check whether the game is finished
        system("cls");          // CLEAR THE TERMINAL
        printf("-- THE GAMES HAVE BEGUN --\n");

        while (!gameEnded) // Loops until the game ends
        {
            int userMove = askUserMove(); // ask the user what move he'd like to use
            system("cls");
            int compMove = computerMove(); // the program stores it's pick
            switch (userMove)
            {
            case 1:
                printf("User picked ROCK\n");
                break;
            case 2:
                printf("User picked PAPER\n");
                break;
            case 3:
                printf("User picked SCISSORS\n");
                break;
            case 4:
                printf("User gave up");
                gameEnded = true;
                break;
            default:
                printf("INVALID");
            }

            int outcome = handleComparsion(userMove, compMove); // calculate the outcome and output in integer
            switch (outcome)
            {
            case 0:
                printf("Draw!\n");
                break;
            case 1:
                printf("You win!\n");
                gameEnded = true;
                sleep(2);
                break;
            case 2:
                printf("You lose!\n");
                gameEnded = true;
                sleep(2);
                break;
            }
        }
    }

    else if (strcmp(command, "exit") == 0)
    {
        return 0;
    }
}

int RPSgame()
{
    while (true)
    {
        rockPaperScissors();

        if (strcmp(command, "exit") == 0)
        {
            printf("BIGGUS DICKUS JOHNNUS IS WAITING FOR YOUR COMMAND\n");
            break;
        }
    }
    return 0;
}