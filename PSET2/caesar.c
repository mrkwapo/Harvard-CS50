#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    //Validating that there is exactly 2 arguments
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    //Validating each character in the key is a number
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (isalpha(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    //getting the plain text and returning the ciphertext
    string p = get_string("plaintext: ");
    printf("ciphertext: ");

    //iterating through each character in the plaintext
    for (int i = 0, n = strlen(p); i < n; i++)
    {
        //Declaring a variable that handles numbers that would cause a wrap around
        int key = atoi(argv[1]) % 26;
        //Declaring a variable that combines the value of each letter plus the key to determine how to handle encryption
        int encrypt = key + p[i];
        //handling encryption for lowercase letters
        if (islower(p[i]))
        {         
            //if no wrap around needed encrypt
            if (encrypt < 122)
            {
                printf("%c", key + p[i]);    
            }
            // if wrap around needed handle wrap around and encrypt
            else if (encrypt > 122)
            {
                printf("%c",  p[i] - (26 - key));    
            }

        }
        //handling uppercase letters        
        if (isupper(p[i]))
        {
            //if no wrap around needed encrypt
            if (encrypt < 90)
            {
                printf("%c", key + p[i]);    
            }
            // if wrap around needed handle wrap around and encrypt
            else if (encrypt > 90)
            {
                printf("%c",  p[i] - (26 - key));    
            }
            
        }

        // if character is not an alphabet just print it
        if (!isalpha(p[i]))
        {
            printf("%c", p[i]);
        }
    }
    printf("\n");
}
