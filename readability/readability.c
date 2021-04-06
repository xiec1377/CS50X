#include <stdio.h>
#include <cs50.h>
#include <string.h> //to get strlength, etc.

int main(void)
{
    int words = 0, letters = 0, sentences = 0; //initialize int variables

    string text = get_string("Text: "); //prompt user for text
    for (int i = 0, n = strlen(text); i < n; i++) //run through each character in string
    {
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        {
            letters += 1; //add letter when character is 'a' - 'z' or 'A' - 'Z'
        }
        if (text[i + 1] == 32 || text[i + 1] == '\0')
        {
            words += 1; //add word if next character is space or null
        }
        if (text[i + 1] == '.' || text[i + 1] == '!' || text[i + 1 ] == '?')
        {
            sentences += 1; //add sentence if next character is ending punctuation        }
        }
    }

    float L = (100 / (float)words) * (float)letters; //assign values to variables
    float S = (100 / (float)words) * (float)sentences;
    float index = 0.0588 * L - 0.296 * S - 15.8; //Coleman-Liau index

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.0f\n", index);
    }

}
