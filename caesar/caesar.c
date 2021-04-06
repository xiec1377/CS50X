#include <cs50.h>
#include <stdio.h>
#include <stdlib.h> /*to get atoi function*/
#include <string.h> /*to get strlen function*/
#include <ctype.h> /*to get isdigit function*/

/*declares constant values*/
const string ALPHA = "abcdefghijklmnopqrstuvwxyz";
const int LOWER = 97;
const int UPPER = 65;
const int LETTERS = 26;

/*command-line argument*/
int main(int argc, string argv[])
{
    /*declares variables*/
    int key, ctext;

    /*checks if user only inputted one command-line argument*/
    if (argc == 2)
    {
        /*scans through command-line argument*/
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            /*checks if command-line argument is positive integer*/
            if (isdigit(argv[1][i]) == false)
            {
                /*instructs user to input integer in command-line argument*/
                printf("Usage: %s key\n", argv[0]);
                /*exit code shows that program went wrong*/
                return 1;
            }
        }
        /*converts user's command-line argument from string to integer*/
        key = atoi(argv[1]);

        /*declares variable, prompts user for plaintext*/
        string ptext = get_string("plaintext: ");

        /*scans through plaintext string*/
        for (int i = 0, n = strlen(ptext); i < n; i++)
        {
            /*Caesar's algorithm for lowercase letters*/
            if (ptext[i] >= 'a' && ptext[i] <= 'z')
            {
                ctext = ((int) ptext[i] - LOWER + key) % LETTERS;
                ptext[i] = ALPHA[ctext];
            }
            /*Caesar's algorithm for uppercase letters*/
            else if (ptext[i] >= 'A' && ptext[i] <= 'Z')
            {
                ctext = ((int) ptext[i] - UPPER + key) % LETTERS;
                ptext [i] = toupper(ALPHA[ctext]);
            }
        }
        /*outputs ciphertext*/
        printf("ciphertext: %s\n", ptext);
        /*exit code shows that there were no problems running the program*/
        return 0;
    }
    else
    {
        /*instructs user to input with one command-line argument*/
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }
}
