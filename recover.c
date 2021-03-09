#include <stdio.h>
#include <stdlib.h>

typedef unsigned char BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2) // check for the correct input from user
    {
        printf("Invalid usage\n");
        return 1;
    }

    FILE *raw = fopen(argv[1], "r"); // open file from user
    if (raw == NULL) // if no data
    {
        printf("No data was found\n");
        return 2;
    }

    BYTE *buffer = malloc(512); // allocate memory for buffer
    int count = 0; // jpeg files count
    char filename[8]; // string for name of the file

    while (fread(buffer, 512, 1, raw)) // go through the data in 512 bytes chanks
    {
        FILE *jpg = NULL; // declare file name
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) // begining of jpeg file
        {
            sprintf(filename, "%03i.jpg", count); // create name of the file
            jpg = fopen(filename, "w"); // open file for writing
            fwrite(buffer, 512, 1, jpg); // write to the file
            count++; // update count of files
            fclose(jpg); // close file
        }
        else // if it's not begining of jpeg file
        {
            if (count > 0) // jpeg files already found
            {
                jpg = fopen(filename, "a"); //open file to append (add) next chank of data
                fwrite(buffer, 512, 1, jpg); // write data to a file
                fclose(jpg); // close file
            }
            else // no files has been found yet
            {
                continue;
            }
        }
    }
    free(buffer); // free memory from buffer
    fclose(raw); //close raw file
    return 0;
}

