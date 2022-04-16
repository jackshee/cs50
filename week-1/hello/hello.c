#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // attempt to read string from stdin
    string name = get_string("What's your name? ");

    // ensure string was read
    //
    printf("hello, %s\n", name);
}

