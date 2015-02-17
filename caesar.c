/**
 * caesar.c
 * Written by Jade Knight
 *
 * This program accepts a single command-line integer as 'k' in the
 * following formula: c = (p + k) % 26 where c is ciphertext, p is plaintext
 * entered by the user, and k is a secret key. Plaintext will be shifted k
 * amount of characters, only including a through z. Result is printed.
 */
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // returns 1 if no argument or more than one argument is entered
    if ( argc != 2)
    {
        //
        printf("Enter a key, and only one key. Try again.");
        return 1;
    }
    else
    {
        // converts secret key to an integer
        int k = atoi(argv[1]);
        // gets text from the user
        string text = GetString();
        
        // loops through each character in user input
        for (int i = 0, n = strlen(text); i < n; i++)
        {
            // checks to see if character is a letter
            if (isalpha(text[i]))
            {
                // checks for capital letter
                if (isupper(text[i]))
                {
                    // shifts k amount of spaces and prints capital letter
                    printf("%c", ((text[i] + k - 65) % 26) + 65);
                }
                else
                {
                    // shifts k amount of spaces and prints lowercase letter
                    printf("%c", ((text[i] + k - 97) % 26) + 97);
                }
            }
            else
            {
                // if not alpha, prints character as is
                printf("%c", text[i]);
            }
        }
        
        // provides new line at end of output
        printf("\n");
        return 0;     
    } 
}
