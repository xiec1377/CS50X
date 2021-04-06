#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int counter = 0;
    // Buffer with 512 bytes
    unsigned char bytes[512];
    char filename[8];
    FILE *img;

    // Check if there is only one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    // Open file
    FILE *file = fopen(argv[1], "r");
    // Check if file exists
    if (!file)
    {
        printf("%s cannot be opened.\n", argv[1]); //change?
        return 1;
    }
    // Read file while items of size 512 B are greater than 0
    while (fread(bytes, sizeof(bytes), 1, file) > 0)
    {
        // Check first three bytes
        if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && ((bytes[3] & 0xf0) == 0xe0))
        {
            // Write first JPEG
            if (counter == 0)
            {
                sprintf(filename, "%03i.jpg", counter);
                counter += 1;
                img = fopen(filename, "w");
                fwrite(bytes, sizeof(bytes), 1, img);
            }
            // Open new JPEG to write to
            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", counter);
                counter += 1;
                img = fopen(filename, "w");
                fwrite(bytes, sizeof(bytes), 1, img);
            }
        }
        // Continue writing JPEG
        else if (counter > 0)
        {
            fwrite(bytes, sizeof(bytes), 1, img);
        }
    }

    // Close files
    fclose(file);
    fclose(img);
    return 0;
}
