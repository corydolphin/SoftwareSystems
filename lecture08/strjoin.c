/* Example code for Software Systems at Olin College.

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

char *tracks[] = {
    "So What",
    "Freddie Freeloader",
    "Blue in Green",
    "All Blues",
    "Flamenco Sketches"
};

/* Returns a heap-allocated string that contains the strings 
   from the given array, joined up with no spaces between.
*/
char *strjoin(char *array[], int n)
{
    int i;
    int totalLength = 0;
    for(i=0; i < n; i ++){
        totalLength += strlen(array[i]);
    }

    // printf("%d\n", totalLength);

    char * result = malloc(sizeof(char)* (totalLength + 1));
    for(i=0; i < n; i ++){
        strcat(result,array[i]);
    }

    return result;
}

/* Returns a heap-allocated string that contains the strings 
   from the given array, joined up with no spaces between.
*/
char *strjoin2(char *array[], int n)
{
    int i;
    int totalLength = 0;
    for(i=0; i < n; i ++){
        totalLength += strlen(array[i]);
    }

    // printf("%d\n", totalLength);

    char * result = malloc(sizeof(char)* (totalLength + 1));
    char * start = result;
    int offset =0;
    for(i=0; i < n; i ++){
        // strcat(result,array[i]);
        strcpy(start,array[i]);
        start += strlen(array[i]);
    }

    return result;
}


int main (int argc, char *argv[])
{
    char *s = strjoin(tracks, 5);
    printf("%s\n", s);

    char *s2 = strjoin2(tracks, 5);

    assert(strlen(s) == strlen(s2));

    assert(!strcmp(s,s2));


    return 0;
}
