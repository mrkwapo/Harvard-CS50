# This program ciphers a plain text message by shifting each character by the given key (which is a number)
import sys
import cs50

# validating length of command line arguments
if not len(sys.argv) == 2:
    print("Usage: python caesar.py key")
    exit(1)

# getting plaintext from the user
plaintext = cs50.get_string("plaintext: ")
print("ciphertext: ", end='')

# initializing the key argument, casting it as a number and handling the ASCII wrap around with the Modulo operator
key = int(sys.argv[1]) % 26

# iterating through each charcter in the plain text message
for i in range(0, len(plaintext), 1):
    encrypt = key + ord(plaintext[i])

    # handling non alphabetic characters
    if plaintext[i].isalpha() == False:
        print(plaintext[i], end='')

    # handling lowercase
    if plaintext[i].islower():
        if encrypt < 122:
            print(chr(key + ord(plaintext[i])), end='')
        elif encrypt > 122:
            print(chr(ord(plaintext[i]) - (26 - key)), end='')

    # handling uppercase
    if plaintext[i].isupper():
        if encrypt < 90:
            print(chr(key + ord(plaintext[i])), end='')
        elif encrypt > 90:
            print(chr(ord(plaintext[i]) - (26 - key)), end='')

print()
