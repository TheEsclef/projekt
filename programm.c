#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#define SIZE 1000

// Function to encrypt text using base64
char *base64Encoder(char input_str[], int len_str)
{
    // Character set of base64 encoding scheme
    char char_set[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    // Resultant string
    char *res_str = (char *)malloc(SIZE * sizeof(char));

    int index, no_of_bits = 0, padding = 0, val = 0, count = 0, temp;
    int i, j, k = 0;

    // Loop takes 3 characters at a time from
    // input_str and stores it in val
    for (i = 0; i < len_str; i += 3)
    {
        val = 0, count = 0, no_of_bits = 0;

        for (j = i; j < len_str && j <= i + 2; j++)
        {
            // binary data of input_str is stored in val
            val = val << 8;

            // (A + 0 = A) stores character in val
            val = val | input_str[j];

            // calculates how many time loop
            // ran if "MEN" -> 3 otherwise "ON" -> 2
            count++;
        }

        no_of_bits = count * 8;

        // calculates how many "=" to append after res_str.
        padding = no_of_bits % 3;

        // extracts all bits from val (6 at a time)
        // and find the value of each block
        while (no_of_bits != 0)
        {
            // retrieve the value of each block
            if (no_of_bits >= 6)
            {
                temp = no_of_bits - 6;

                // binary of 63 is (111111) f
                index = (val >> temp) & 63;
                no_of_bits -= 6;
            }
            else
            {
                temp = 6 - no_of_bits;

                // append zeros to right if bits are less than 6
                index = (val << temp) & 63;
                no_of_bits = 0;
            }
            res_str[k++] = char_set[index];
        }
    }

    // padding is done here
    for (i = 1; i <= padding; i++)
    {
        res_str[k++] = '=';
    }
    res_str[k] = '\0';
    return res_str;
}

// Function to decrypt text using base64
char *base64Decoder(char encoded[], int len_str)
{
    char *decoded_string;

    decoded_string = (char *)malloc(sizeof(char) * SIZE);

    int i, j, k = 0;

    // stores the bitstream.
    int num = 0;

    // count_bits stores current
    // number of bits in num.
    int count_bits = 0;

    // selects 4 characters from
    // encoded string at a time.
    // find the position of each encoded
    // character in char_set and stores in num.
    for (i = 0; i < len_str; i += 4)
    {
        num = 0, count_bits = 0;
        for (j = 0; j < 4; j++)
        {
            // make space for 6 bits.
            if (encoded[i + j] != '=')
            {
                num = num << 6;
                count_bits += 6;
            }

            /* Finding the position of each encoded
            character in char_set
            and storing in "num", use OR
            '|' operator to store bits.*/

            // encoded[i + j] = 'E', 'E' - 'A' = 5
            // 'E' has 5th position in char_set.
            if (encoded[i + j] >= 'A' && encoded[i + j] <= 'Z')
                num = num | (encoded[i + j] - 'A');

            // encoded[i + j] = 'e', 'e' - 'a' = 5,
            // 5 + 26 = 31, 'e' has 31st position in char_set.
            else if (encoded[i + j] >= 'a' && encoded[i + j] <= 'z')
                num = num | (encoded[i + j] - 'a' + 26);

            // encoded[i + j] = '8', '8' - '0' = 8
            // 8 + 52 = 60, '8' has 60th position in char_set.
            else if (encoded[i + j] >= '0' && encoded[i + j] <= '9')
                num = num | (encoded[i + j] - '0' + 52);

            // '+' occurs in 62nd position in char_set.
            else if (encoded[i + j] == '+')
                num = num | 62;

            // '/' occurs in 63rd position in char_set.
            else if (encoded[i + j] == '/')
                num = num | 63;

            // ( str[i + j] == '=' ) remove 2 bits
            // to delete appended bits during encoding.
            else
            {
                num = num >> 2;
                count_bits -= 2;
            }
        }

        while (count_bits != 0)
        {
            count_bits -= 8;

            // 255 in binary is 11111111
            decoded_string[k++] = (num >> count_bits) & 255;
        }
    }

    // place NULL character to mark end of string.
    decoded_string[k] = '\0';

    return decoded_string;
}

// Function to encrypt text using the Caesar cipher
char *caesarEncrypt(char text[])
{
    static char buffer[100]; // Static buffer to hold the encrypted text
    int i = 0;               // Index for iterating through the input text
    while (text[i] != '\0')  // Loop until the end of the input text
    {
        buffer[i] = text[i] + 1; // Shift each character by 1 to encrypt
        i++;
    }

    buffer[i] = '\0'; // Null-terminate the encrypted string
    return buffer;    // Return the encrypted string
}

// Function to decrypt text using the Caesar cipher
char *caesarDecrypt(char text[])
{
    static char buffer[100]; // Static buffer to hold the decrypted text
    int i = 0;               // Index for iterating through the input text

    while (text[i] != '\0') // Loop until the end of the input text
    {
        buffer[i] = text[i] - 1; // Shift each character by -1 to decrypt
        i++;
    }

    buffer[i] = '\0'; // Null-terminate the decrypted string
    return buffer;
}

int helpCommand()
{
    printf("Available commands: \n \t"
           "encrypt - Asks for input and encrypts the input \n \t"
           "decrypt - Asks for input and decrypts the input\n \t"
           "exit - Exits the program\n");
}

// Function to ask the user for the encryption/decryption algorithm
int askEncryptSubCommand()
{
    int choice; // Variable to store the user's choice of encryption/decryption algorithm
    printf(
        "Please select the decryption algorithm \n"
        "\t1. Caesar \n"
        "\t2. base64 \n");

    scanf("%d", &choice); // Read the user's choice from input
    return choice;
}

// Handle the logic of encryption command
int encryptAskCommand()
{
    int subCommand;
    char unecrypted[100];
    subCommand = askEncryptSubCommand(); // Ask the user for the encryption algorithm
    switch (subCommand)
    {
    case 1:
        printf("Please enter the text to encrypt: \n");
        scanf("%s", unecrypted);

        char *x = caesarEncrypt(unecrypted);
        printf("Encrypted: %s\n", x);
        printf("Waiting for input....\n");
        break;

    case 2:
        printf("Please enter the text to encrypt: \n");
        scanf("%s", unecrypted);                                           // ask the user for input
        int lenOfUnencrypted = sizeof(unecrypted) / sizeof(unecrypted[0]); // get the length of the text
        printf("Encrypted: %s\n", base64Encoder(unecrypted, lenOfUnencrypted));
        break;

    default: // Handle unknown subcommands
        printf("Unknown subcommand.\n");
        break;
    }
}

int decryptAskCommand()
{
    char encrypted[100];
    int subCommand;
    subCommand = askEncryptSubCommand(); // Ask the user for the decryption algorithm
    switch (subCommand)
    {
    case 1:
        printf("Please enter the text to decrypt: \n");
        scanf("%s", encrypted); // ask the user for input

        char *x = caesarDecrypt(encrypted); // Decrypt the text using the Caesar cipher
        printf("Decrypted: %s\n", x);
        printf("Waiting for input....\n");
        break;

    case 2:
        printf("Please enter the text to encrypt: \n");
        scanf("%s", encrypted);
        int lenOfEncrypted = sizeof(encrypted) / sizeof(encrypted[0]); // Gets the length of the encrypted text
        printf("Decrypted: %s\n", base64Decoder(encrypted, lenOfEncrypted));
        break;

    default: // Handle unknown subcommands
        printf("Unknown subcommand.\n");

        break;
    }
}

int main()
{
    // Declare variables for user input and commands
    char command[100];
    int subCommand;
    char unecrypted[100];
    char encrypted[100];

    printf("big dick john is waiting for your command ;) \n"); // greet the user with a nice and friendly message

    while (true) // Infinite loop to continuously prompt the user for commands
    {
        scanf("%s", command); // Read the user's command from input

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

        else
        {
            printf("Unknown command. Type \"help\" for a list of commands.\n");
        } // Handle unknown commands
    }

    return 0;
}