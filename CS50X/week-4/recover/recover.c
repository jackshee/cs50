#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int BLOCK_SIZE = 512;
 
int main(int argc, char *argv[])
{
    // Check exactly one argument IMAGE passed
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Open the memory card passed in from the first argument
    FILE *raw_file = fopen(argv[1], "r");

    if (raw_file == NULL)
    {
        printf("Error: cannot open %s\n", argv[1]);
        return 2;
    }

    // Repeat until end of card
    BYTE buffer[BLOCK_SIZE]; 
    int num_jpeg = 0;
    char filename[8];
    FILE *new_jpeg = NULL;

    while (fread(&buffer, BLOCK_SIZE, 1, raw_file) == 1)
    {
        // If start of new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Already previously opened JPEG, close file first 
            if (num_jpeg > 0)
            {
                fclose(new_jpeg);
            }

            // Open new jpeg file to write to
            sprintf(filename, "%03i.jpg", num_jpeg);
            new_jpeg = fopen(filename, "w");
            num_jpeg++;
        }
        if (num_jpeg > 0)
        {
            fwrite(&buffer, BLOCK_SIZE, 1, new_jpeg);
        }
    }

    // Close any remaining files
    fclose(new_jpeg);
    fclose(raw_file);

    return 0;

}
