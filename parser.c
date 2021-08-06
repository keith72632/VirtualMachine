#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define FILE_NAME "test.txt"

char file_size = 0;

char *file_parse(char *file_name)
{
    FILE *fp = NULL;
    char junk, ch, i = 0;
    char *return_array = NULL;
    
    fp = fopen(file_name, "r");

    while((junk = fgetc(fp))!=EOF && junk){
        if(!isdigit(junk))
        {
            file_size++;
            return_array = realloc(return_array, (sizeof(char) * file_size));        
            return_array[i] = junk;
            i++;
            putchar(junk);
        }
    }
    putchar('\n');

    printf("File size = %d\n", file_size);

    fclose(fp);

    return return_array;
    
}


int main()
{
    char *stuff = file_parse(FILE_NAME);
    printf("it works\n");
    puts(stuff);
    return 0;
}
