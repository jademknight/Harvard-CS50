/**
 * initials.c
 * Written By Jade Knight
 * 
 * This program prompts the user for their name and assumes the user's input
 * will be only letters and single spaces between words. The initials will be
 * returned capitalized.
 */


#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // gets a name from the user
    string name = GetString();
    
    // prints the first char
    printf("%c", toupper(name[0]));
    
    // loop finds whitespace and prints the first char of next word
    for(int i = 0, n = strlen(name); i < n; i++)
    {
        if (name[i] == ' ')
        {
            printf("%c", toupper(name[i + 1]));
        }
    }
    
    printf("\n");
}
