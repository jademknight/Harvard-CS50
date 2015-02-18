/**
 * mario.c
 * written by Jade Knight
 *
 * This program prompts the user for an integer between 0 and 23 and creates
 * a mario-like pyramid using that integer as the height. 
 */

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // variable to hold pyramid height
    int height;
    
    // loops only for an invalid entry
    do
    {
    // Gets height from user
        printf("Height: ");
        height = GetInt();
    } while(height < 0 || height > 23);
    
    // Prints pyramid if height is within 0 and 23
    for(int i = 1; i <= height; i++)
    {
        for(int j = (height - i); j > 0; j--)
        {
            printf(" ");
        }
        for(int k = 1; k <= (i + 1); k++)
        {
            printf("#");
        }
        
        printf("\n");
        
        }    
}

