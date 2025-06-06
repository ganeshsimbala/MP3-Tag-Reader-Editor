#include <stdio.h>
#include <string.h>
#include "view.h"
#include "help_Menu.h"
#include "edit.h"
int main(int argc, char *argv[])
{
    if (argc <= 1 || (argc == 2 && strcmp(argv[1], "-h"))) // checking for command line arguments
    {
        printf("ERROR : %s --Invalid Arguments\n", argv[0]);
        printf("Usage:\n");
        printf("For help : ");
        printf("Please Pass like \"./a.out -h\"\n");
        return 1;
    }
    if (!strcmp(argv[1], "-v") && argv[2] != NULL) // command line argument is for view
    {
        FILE *fptr = fopen(argv[2], "r");
        if (fptr != NULL)
            view(fptr);
        else
        {
            printf("Failed to load the file %s\n", argv[2]);
            return 1;
        }
    }
    if (!strcmp(argv[1], "-e") && argc == 5) // checking for edit part
    {
        char *str[6] = {"TIT2", "TPE1", "TYER", "TALB", "TCON", "COMM"}; // finding which tag to edit
        char *edit_tag = Tag_to_edit(argv[2], str);
        int len = strlen(argv[4]) + 1;

        if (edit_tag != NULL)
            edit(argv[3], len, argv[4], edit_tag); // calling finction to edit

        else
            return 1;

        return 0;
    }

    // for help menu
    else if (!strcmp(argv[1], "-h")) 
    {
        help_Menu();
        return 1;
    }
}