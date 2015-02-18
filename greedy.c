/**
 * greedy.c
 * Written By Jade Knight
 *
 * This program asks the user for the amount of change to be received and 
 * prints out the lowest number of coins that the change can be divded into.
 * Only quarters, dimes, nickels, and pennies can be used.  
 */
#include <cs50.h>
#include <stdio.h>
#include <math.h>
 
int main(void)
{
    // total amount in cents
    int total; 
    // keeps track of the number of coins
    int counter = 0;
    
    printf("How much change is owed?\n");
    float change = GetFloat(); 
    
    // if user enters a negative number
    while (change < 0.00)
    {
        printf("How much change is owed?\n");
        change = GetFloat();
    }
    // rounds the total and stores as an int
    total = round(change * 100);
        
    // counts the number of quarters
    while (total >= 25)
    {
        counter++;
        total -= 25;
    }
    // counts the number of dimes
    while (total >= 10)
    {
        counter++;
        total -= 10;
    }
    // counts the number of nickels
    while (total >= 5)
    {
        counter++;
        total -= 5;
    }
    // counts the number of pennies
    while (total >= 1)
    {
        counter++;
        total -= 1;
    }
         
    // prints the total number of coins
    printf("%i\n", counter);
}
