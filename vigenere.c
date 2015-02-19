/**
 * vigenere.c
 * Written By Jade Knight
 *
 * This program acts as a Vigenere Cipher. The user must enter a command line 
 * argument that is all letters. After pressing enter, the user can then enter
 * a line of text. Each letter in the keyword will be given a value of 0-25
 * where a is 0 and z is 25. All letters in the user's line of text will be
 * shifted using the keyword and any whitespace or numbers will be printed 
 * as is. 
 */
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // prompts user if no or more than one argument is entered
    if (argc != 2)
    {
        printf("Please enter one and only one command line argument.");
        return 1;
    }
    else
    {
        // declares secret  key
        string k = argv[1];
        // loops through each character and checks if it is a letter
        for( int l = 0, m = strlen(k); l < m ; l++)
        {
            // prompts user if key contains any numerical values
            if (isdigit(k[l]))
            {
                printf("The keyword must be all letters.\n");
                return 1;
            }
        }
        
        // get plaintext from user
        string text = GetString();
        
        // loops through each character in user input
        // i used to loop through plaintext, j used to loop key
        for (int i = 0, j = 0, n = strlen(text); i < n; i++, j++)
        {
            // restarts the loop for the key once it has been looped
            if (j >= strlen(k))
            {
                j = 0;
            }
           
            // checks to see if character is a letter
            if (isalpha(text[i]))
            {
                // checks for capital letter
                if (isupper(text[i]))
                {
                    // if key is also capital
                    if (isupper(k[j]))
                    {
                        // prints value where both text and key is capital
                        printf("%c", ((text[i] + k[j] - 65 - 65) % 26) + 65);
                    }
                    else
                    {
                        // prints value where text is capital and key 
                        // is lowercase
                        printf("%c", ((text[i] + k[j] - 65 - 97) % 26) + 65);
                    }
                  
                }
                else
                {
                    // checks to see if key is capital
                    if (isupper(k[j]))
                    {
                        // prints value where text is lowercase and key
                        // is capital
                        printf("%c", ((text[i] + k[j] - 97 - 65 ) % 26) + 97);
                    }
                    else  
                    {   
                        // prints calue where text and key are both lowercase
                        printf("%c", ((text[i] + k[j] - 97 - 97) % 26) + 97);
                    }
                }
            }
            else
            {
                // if not alpha, prints character as is
                printf("%c", text[i]);
                // makes sure j does not increase for spaces/numbers
                j -= 1;
            }   
        }
        
        // print new line at end of ouput
        printf("\n");
        
        }
}
