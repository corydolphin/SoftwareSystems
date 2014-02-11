/* Example code for Software Systems at Olin College.

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define NUM_TRACKS 5

char tracks[][80] = {
    "So What",
    "Freddie Freeloader",
    "Blue in Green",
    "All Blues",
    "Flamenco Sketches"
};


// Finds all tracks that contain the given string.
//
// Prints track number and title.
void find_track(char search_for[])
{
    int i;
    for (i=0; i<NUM_TRACKS; i++) {
	if (strstr(tracks[i], search_for)) {
	    printf("Track %i: '%s'\n", i, tracks[i]);
	}
    }
}

//
// Helper function to handle cases of regex matches
//
// inputs: pointer to compiled regex
// returns 1 if match, 0 if no match, and -1 if error
// In the case of an error, the error is printed.
//
int doesMatch(regex_t *re, char *string){
    int no_match;
    char msgbuf[100];
    no_match = regexec(re, string, 0, NULL, 0);

    if( !no_match ){ // zero is success.
        return 1;
    }
    else if( no_match == REG_NOMATCH ){
        return 0;
    }
    else{
        regerror(no_match, re, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        return -1;
    }
}


// Finds all tracks that match the given pattern.
//
// Prints track number and title.
// Used http://www.peope.net/old/regex.html for help
void find_track_regex(char pattern[])
{
    regex_t    re;
    int no_match;

    if (regcomp(&re, pattern, REG_EXTENDED) != 0) {
        printf("Error");      /* report error */
    }

    for(int i = 0; i < NUM_TRACKS; i++){
        if(doesMatch(&re, tracks[i])){
            printf("Track %i: '%s'\n", i, tracks[i]);
        }
    }

    //Free the regex!
    regfree(&re);
}

// Truncates the string at the first newline, if there is one.
void rstrip(char s[])
{
    char *ptr = strchr(s, '\n');
    if (ptr) {
	*ptr = '\0';
    }
}

int main (int argc, char *argv[])
{
    char search_for[80];

    /* take input from the user and search */
    printf("Search for: ");
    fgets(search_for, 80, stdin);
    rstrip(search_for);

    // find_track(search_for);
    find_track_regex(search_for);

    return 0;
}
