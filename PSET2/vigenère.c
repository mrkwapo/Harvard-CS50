//this program encrypts messages using a keyword
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int shift(char c);
int main(int argc, string argv[])
{
    //validating that exactly 1 keyword is used when running the program
    if (argc != 2)
    {
        printf("Usage: ./vigenere keyword \n");
        return 1;
    }
    
    //validating that they keyword uses all letters
    for (int i = 0, len = strlen(argv[1]); i < len; i++)
    {
        if (isdigit(argv[1][i]))
        {
            printf("Usage: ./vigenere keyword \n");
            return 1;
        }        
        
    }    
    
    //Initializing a counter to itereate through the length of the keyword
    int count = 0;   
    
    
    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");
        
    for (int i = 0; i < strlen(plaintext); i++)
    {      
        //Declared a variable so we can use each letter in the keyword as a key
        int key = shift(argv[1][count]);
        
        //if no wrap around needed this just prints plaintext plus key for lowercase and uppercase letters
        if (islower(plaintext[i]) && plaintext[i] + key <= 122)
        {
            printf("%c", plaintext[i] + key);            
        }
        if (isupper(plaintext[i]) && plaintext[i] + key <= 90)
        {
            printf("%c", plaintext[i] + key);
        }
        
        //handles plaintext characters that need a wrap around  for lowercase and uppercase letters    
        if (islower(plaintext[i]) &&  plaintext[i] + key > 122)
        {
            printf("%c", (plaintext[i] - 26) + key);            
        }        
        if (isupper(plaintext[i]) &&  plaintext[i] + key > 90)
        {
            printf("%c", (plaintext[i] - 26) + key);
        }
        
        //preserves spaces and punctuation and does not count itself to shift the value of the keyword letter
        if (isspace(plaintext[i]) || ispunct(plaintext[i]))
        {
            printf("%c", plaintext[i]);
            count--;
        }
        //if we reach the last index character in the keyword this resets the counter to zero so we start back at the beginning of the keyword
        if (count + 1 == strlen(argv[1]))
        {
            count = (count + 1) % strlen(argv[1]);
            count--;
        }
        
        count++; 
        
    }
    printf("\n");
}

//this function converts the values of lowercase and uppercase characters to numbers from 0 to 25. For example, 'A' or 'a' = 0. 'B' or 'b' = 1. 'Z' or 'z' = 25
int shift(char c)
{    
    if (islower(c))
    {
        int value = c - 97;
        return value;
    }
    if (isupper(c))
    {
        int value = c - 65;
        return value;
    }
    return 1;
}
