
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "view.h"
void view(FILE *fptr)
{
    char signature[4];

    if (fptr == NULL) 
    {
        printf("The Audio File Not found\n");
        return;
    }

    fread(signature, 3, 1, fptr); // reading signature
    signature[3] = '\0';
    if (strcmp(signature, "ID3") != 0) // checking for .mp3 file or not
    {
        printf("File is not a .MP3 file\n");
        return;
    }
    char *str[6] = {"TALB", "TIT2", "TYER", "TPE1", "COMM", "TCON"};
    int count = 0;
    fseek(fptr, 7, SEEK_CUR);
    printf("-----------------------------------------------------------\n");
    printf("Info of MP3 FILE ID3V2\n");
    printf("-----------------------------------------------------------\n");
    while (count < 6) // running the loop for 6 times to read 6 tags
    {
        char tag[50];
        fread(tag, 1, 4, fptr); // reading tag
        tag[4] = '\0';

        int flag = tagType(tag, str); // calling the function to know tag type

        int size;
        fread(&size, 1, 4, fptr);

        endian_conversion(&size, 4); // converting big endian to little endian

        fseek(fptr, 3, SEEK_CUR);     // moving fptr 3 bytes to skip flags
        char *content = malloc(size); // storing the content in a char *
        fread(content, 1, size - 1, fptr);

        if (flag)
        {
            for (int i = 0; i < size - 1; i++)
            {
                printf("%c", content[i]);
            }
            printf("\n");
            count++;
        }
        free(content);
    }
    printf("-----------------------------------------------------------\n");
}
int tagType(char *tag, char *ptr_to_tags[6]) // function to find the type of tag
{
    int choice = -1;
    for (int i = 0; i < 6; i++)
    {
        if (!strcmp(tag, ptr_to_tags[i]))
        {
            choice = i;
            break;
        }
    }
    if (choice < 0)
        return 0;
    switch (choice) // printing the tags on console
    {
    case 0:
        printf("Album \t: ");
        break;
    case 1:
        printf("Title \t: ");
        break;
    case 2:
        printf("Year \t: ");
        break;
    case 3:
        printf("Artist \t: ");
        break;
    case 4:
        printf("Comment : ");
        break;
    case 5:
        printf("Genre \t: ");
        break;
    }
    return 1;
}
void endian_conversion(void *ptr, int size) // converting big endian to little endian
{
    unsigned char *bytes = (unsigned char *)ptr;
    for (int i = 0; i < size / 2; i++)
    {
        unsigned char temp = bytes[i];
        bytes[i] = bytes[size - 1 - i];
        bytes[size - 1 - i] = temp;
    }
}
