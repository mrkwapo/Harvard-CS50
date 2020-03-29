//this program asks for the height of a Nintendo Mario pyramid from the user and then creates it using hashes.
#include <cs50.h>
#include <stdio.h>

int get_positive_int(string prompt);

int main(void)
{
    //asking user for the height
    int height = get_positive_int("Height: ");
    //This is the main loop loop that handle the height of each pyramid
    for (int i = 0; i < height; i++)
    {
        //this loop uses the given height minus one to create the spaces needed to justify/align the hashes to the right
        for (int k = 1; k < height - i; k++)
        {
            printf(" ");
        }
        //this loop prints the amount of hashes for each row based on each iteration for the given height
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        //this creates a new line after each iteration of the outer for loop
        printf("\n");
       
    }
    
}

// Prompt user for positive integer
int get_positive_int(string prompt)
{
    int n;
    do
    {
        n = get_int("%s", prompt);
    }     
    while (n > 8 || n < 1);
    return n;
}
