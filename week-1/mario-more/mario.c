#include <cs50.h>
#include <stdio.h>

int main(void) 
{
    // Get input from user 
    int height;
    
    do
    {
        height = get_int("Height: ");    
    }
    while (height < 1  || height > 8);


    for (int i = 0; i < height; i++)
    {
        // print spaces preceding blocks 
        for (int j = 1; j < height - i; j++)
        {
            printf(" ");
        }

        for (int j = 0; j < i + 1; j++)
        {
            printf("#");    
        }
        // print two blank space separator
        printf("  ");
        for (int j = 0; j < i + 1; j++) 
        {
            printf("#");    
        }
        // new line
        printf("\n");
    }

}
