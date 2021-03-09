#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Invalid usage\n");
        return 1;
    }
    else
    {
        int counter_1 = 0; //check how many files
        int counter_2 = 0; // check if we are inside the file

        FILE *f = fopen(argv[1], "r"); // open file for reading

        unsigned char *bytes = malloc(sizeof(char) * 512);

        fread(bytes, 512, 1, f);// read 512 bytes chank of memory

        if () // beginning of JPEG
        {
            if (counter_1 == 0)// first jpeg found
            {
                FILE *img = fopen("000.jpg", "w");
                fwrite(bytes, 8, 512, img);
                counter_1 = 1;
                counter_2++;
            }
            else // not first jpeg
            {
                sprintf("filename", "%03i.jpg", counter_1);
                FILE *img = fopen("filename", "w");
                fwrite(bytes,8 ,512, img);
                counter_1++;
                counter_2++;
            }
        }
        else if (counter_2 != 0) //not beggining of JPEG
        {

            FILE *img = fopen("filename", "r");
            char ch;
            if ((ch = fgetc(img)) != EOF)
            {
                fwrite(bytes, 8, 512, img);
                counter_2++;
            }
            else
            {
                fclose(img);
                counter_2 = 0;
                return 0;
            }
        }
        free(bytes);
    }
}
