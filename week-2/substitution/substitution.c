#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void print_usage();

int main(int argc, string argv[]) 
{

    // Use to store upper case version of key
    char key_upper[26];
    // Validate user input 
    if (argc == 2)
    {
        string key = argv[1];
        int key_length = strlen(key);

        // Check that key length is 26
        if (key_length != 26)
        {
            print_usage();
            return 1;
        }
        // Check that all the characters are letters and convert to upper
        for (int i = 0; i < key_length; ++i)
        {
            if (isalpha(key[i]) == 0)
            {
                print_usage();
                return 1;
            }           
            key_upper[i] = toupper(key[i]);

            // Check that the letter has not been duplicated
            for (int j = 0; j < i; ++j)
            {
                if (key_upper[i] == key_upper[j])
                {
                    print_usage();
                    return 1;
                } 
            }
        }
        // Get user input for message to encrypt
        string message = get_string("plaintext: ");
        string cipher = message; 

        // Encrypt message 
        for (int i = 0, message_length =  strlen(message); i < message_length; i++) 
        {
            if (isalpha(message[i]))
            {
                // If character is upper case
                // Get corresponding index for key by subtracting 65 which is ASCII for 'A'
                if (isupper(message[i]))
                {
                    cipher[i] = key_upper[message[i] - 65];
                }
                else
                {
                    // If character is lower case
                    // Convert first to upper case to get corresponding key
                    // Convert back to lower case
                    cipher[i] = tolower(key_upper[toupper(message[i]) - 65]);
                }
            }    
        }

        printf("ciphertext: %s\n", cipher);
        
        return 0;
    }
    else
    {
        print_usage(); 
        return 1;
    }
}

void print_usage()
{
    printf("Usage: ./substitution key\n");
}
