#include <stdio.h>

// help menu

void help_Menu()
{
    printf("Usage : \n");
    printf("-c - To modify Composer\n-t - To modify title tag\n-a - To modify Artist tag\n-A - To modify Album Tag\n-y - To modify Year Tag\n-g - To modify Genere Tag\n-h - For Help menu\n-v - To view File.mp3 Info : Pass like  \"./a.out -e <file_name.mp3>\"\n-e - To edit Tags : Pass like  \"./a.out -e -t/-a/-A/-y/-g/-c <file_name.mp3> \"New_content\"\n");
    return;
}