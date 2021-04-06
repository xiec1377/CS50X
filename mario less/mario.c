#include <cs50.h> //to get get_int function
#include <stdio.h>

int main(void)
{
    int i, j, k; //declares int variables
    do
    {
        i = get_int("Height: "); //prompts user, sets variable i
    }
    while (i <= 0 || i > 8); //continues to prompt during these conditions
    for (j = 1; j <= i; j++)
    {
        for (k = i - j; k > 0; k--) //spaces
        {
            printf(" ");
        }
        for (k = 1; k <= j; k++) //"#"
        {
            printf("#");
        }
        printf("\n");
    }
}
