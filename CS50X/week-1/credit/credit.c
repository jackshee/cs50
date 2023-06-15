#include <cs50.h>
#include <stdio.h>

int main(void) 
{
    // starting with numbers second to last digit, multiply every other digit by 2 and sum 
    // add the result to the sum of digits that weren't multiplied by 2
    // number is valid if the sum of the two sums is divisible by 10

    long cc_num = get_long("Number: ");
    
    // use counter to track every second digit
    int counter = 0;

    // sums of digits in even and odd positions
    int odd_sum = 0;
    int even_sum = 0;

    // at the end of the iteration mod will be the first digit of the card
    // need to store the second digit as well to check validity for American Express

    int mod_hist; 
    int mod;

    while (cc_num > 0)
    {
        // utilise a temp variable to store the contents of mod before updating it
        int tmp = mod;
        mod = cc_num % 10;
        mod_hist = tmp;
        cc_num /= 10; 

        // we are in odd position 1, 3, 5 ... 
        if (counter % 2 == 0)
        {
            odd_sum += mod;
        }
        // we are in even position
        else
        {
            int tmp_mod = mod * 2; 

            // when digits are multiplied by 2, then we may have double digits that need to be split 
            while (tmp_mod > 0)
            {
                int prod_digit = tmp_mod % 10; 
                tmp_mod /= 10;
                even_sum += prod_digit;
            }
        }
        
        counter++;
    }

    // checking if the sums is divisible by 10
    if ((odd_sum + even_sum) % 10 != 0)
    {
        printf("INVALID\n");
    }
    else if (counter == 15)
    {
        // checking if starting with 34 or 37
        if ((mod == 3 && mod_hist == 4) || (mod == 3 && mod_hist == 7))
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (counter == 16)
    {
        // checking if starting with 50, 51, 52, 53, 54, 55
        if (mod == 5 && mod_hist < 6)
        {
            printf("MASTERCARD\n");           
        }
        else if (mod == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (counter == 13)
    {
        // checking if starting with 4
        if (mod == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");    
        }
    }
    else
    {
        printf("INVALID\n");
    }

}
