#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "view.h"
#include "edit.h"

void edit(char *file_name, int new_size, char *New_Content, char *edit_tag) /*taking inputs from the function call-->
file name,size of new content ,New content, tag to edit */

{

    FILE *fptr1 = fopen(file_name, "r");
    FILE *fptr2 = fopen("temp.mp3", "w"); // opening a temporary file to store the copying data from original file
    if (fptr1 == NULL || fptr2 == NULL)
    {
        printf("Failed to open the file\n");
        return;
    }
    // copying 10 bytes of header into temporary file
    char meta_data[10];
    fread(meta_data, 1, 10, fptr1);
    fwrite(meta_data, 1, 10, fptr2);

    bool _tag_found = false;
    int i = 0;
    // copying file info to temporary file until tag is found
    while (!_tag_found)
    {

        char tag[5];
        char flags[3];
        fread(tag, 1, 4, fptr1); // reading tag
        tag[4] = '\0';

        int size;
        fread(&size, 4, 1, fptr1);
        endian_conversion(&size, 4);
        // printf("%d\n",size); // reading size and converintg it into little endian
        if (is_tag(tag, edit_tag))   // checking whether the tag read is tag to edit or not
        {

            _tag_found = true;
            int temp=new_size;
            fwrite(tag, 1, 4, fptr2);
            // printf("%d\n",new_size);
            endian_conversion(&new_size, 4); // convering little endian to big endian
            // printf("%d\n",new_size);

            fwrite(&new_size, 4, 1, fptr2);

            fread(flags, 1, 3, fptr1); // copying flag data as it is
            fwrite(flags, 1, 3, fptr2);
            fwrite(New_Content, 1, temp - 1, fptr2); // copying new content to temp file

            fseek(fptr1, size - 1, SEEK_CUR); // moving fptr1 to previous size bytes to read rest of content

            break; // skip old content
        }

        fwrite(tag, 1, 4, fptr2); // reading tag
        int temp = size;
        endian_conversion(&size, 4); // convering little endian to big endian
        fwrite(&size, 4, 1, fptr2);
        fread(flags, 1, 3, fptr1);
        fwrite(flags, 1, 3, fptr2); // copying new content to temp file
        char *content = malloc(temp - 1);
        fread(content, 1, temp - 1, fptr1); // copying old content

        if (!content)
            break;

        fwrite(content, 1, temp - 1, fptr2);
        free(content); // freeing dynamically allocated memory
    }

    char ch;
    // reading rest of the data
    while ((ch = fgetc(fptr1)) != EOF)
    {

        fputc(ch, fptr2);
    }

    fclose(fptr1);
    fclose(fptr2);

    // removing the old file and Renaming the temporary file to old file
    if (_tag_found)
    {

        printf("The %s tag updated succesfully\n", edit_tag);
        remove(file_name);
        rename("temp.mp3", file_name);
    }
    else
    {
        printf("Tag %s not found in file.\n", edit_tag);
        remove("temp.mp3");
    }
}

int is_tag(char *tag, char *edit_tag) // to check read tag is tag to edit or not
{
    if (!strcmp(tag, edit_tag))
        return 1;
    else
        return 0;
}

char *Tag_to_edit(char *tag, char *tags[]) // finding which tag to edit based on command line arguments

{
    char *list_tags[6] = {"-t", "-a", "-y", "-A", "-g", "-c"};
    int choice = -1;
    for (int i = 0; i < 6; i++)
    {
        if (strcmp(tag, list_tags[i]) == 0)
        {
            choice = i;
            break;
        }
    }
    if (choice < 0)
    {
        printf("Invalid tag\n");
        return NULL;
    }

    return tags[choice];
}
