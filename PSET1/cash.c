//This program is the Greedy Algorithm. When a user inputs an amount of change owed in USD, the program returns the smallest amount of coins that can be used to pay in increments of .25, .10, .05 and .01 cents.
#include <cs50.h>
#include <stdio.h>
#include <math.h>

//Declares a function that will only recieve a positive integer
float get_positive_float(string prompt);

int main(void)
{
    //Getting a positive integer from the user input
    float change = get_positive_float("Change owed: $");
    //changing a float to a whole number to avoid flaws in working with floats
    int convertedchange = round(change * 100);
    //declaring a variable to store and output how many coins will be used to make change
    int count = 0;
    
    //when the change owed is 25 cents or more, divide it by 25, store the amount of times divided into count and save the remainder in the variable convertedchange.
    if (convertedchange >= 25)
    {
        count += (convertedchange / 25);
        convertedchange %= 25;
    }
    //when the change owed or remainder of change is 10 cents or more, divide it by 10, store the amount of times divided into count and save the remainder in the variable convertedchange.
    if (convertedchange >= 10 && convertedchange < 25)
    {
        count += (convertedchange / 10);
        convertedchange %= 10;
    }
    //when the change owed or remainder of change is 5 cents or more, divide it by 5, store the amount of times divided into count and save the remainder in the variable convertedchange.
    if (convertedchange >= 5 && convertedchange < 10)
    {
        count += (convertedchange / 5);
        convertedchange %= 5;
    }
    //when the change owed or remainder of change is 1 cent or more, divide it by 1, store the amount of times divided into count and save the remainder in the variable convertedchange.
    if (convertedchange >= 1 && convertedchange < 5)
    {
        count += (convertedchange / 1);
        convertedchange %= 1;
    }
    //output the value of count which is keeping track of how many times the change was divided by using the least amount of coins
    printf("%i\n", count);
    
}

//Prompts user to submit a positive float
float get_positive_float(string prompt)
{
    float n;
    do
    {
        n = get_float("%s", prompt);
    }
    // re-prompts user if they do not input a positive integer
    while (n <= 0);
    return n;
}
