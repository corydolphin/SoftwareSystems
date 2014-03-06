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


typedef struct {
    regex_t inner_struct[1];
    char msg_buf[100];
    int res = 3;

} Regex;



void perror_exit (char *s)
{
  perror (s);
  exit (-1);
}

void *check_malloc(int size)
{
  void *p = malloc (size);
  if (p == NULL) perror_exit ("malloc failed");
  return p;
}


// Returns a new Regex that matches the given pattern.
// pattern: string regex
// flags: flags passed to regcomp
// returns: new Regex 
Regex *make_regex(char *pattern, int flags) {

    Regex* regex = (Regex*)check_malloc(sizeof(Regex));

    int ret = regcomp(regex->inner_struct, pattern, flags );
    if (ret) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }
    return regex;
}



// Checks whether a regex matches a string.
// regex: Regex
// s: string
// returns: 1 if there's a match, 0 otherwise
int regex_match(Regex *regex, char *s) {

    int ret = regexec(regex->inner_struct, s, 0, NULL, 0);

    if (!ret) {
        return 1;
    } else if (ret == REG_NOMATCH) {
        return 0;
    } else {
       // regerror(ret, regex->inner_struct, regex->msgbuf, sizeof(char)*regex->msg_buf_size);
       // fprintf(stderr, "Regex match failed: %s\n", regex->msg_buf);
       // exit(1);
        return 0;
    }

    return 0;
}

// Frees a Regex.
// regex: Regex
void regex_free(Regex *regex) {

    regfree(regex->inner_struct);
    free(regex);
    // FILL THIS IN
}


// Finds all tracks that match the given pattern.
//
// Prints track number and title.
void find_track_regex(char pattern[])
{
    int i;

    Regex *regex = make_regex(pattern, REG_EXTENDED | REG_NOSUB);

    for (i=0; i<NUM_TRACKS; i++) {
	if (regex_match(regex, tracks[i])) {
	    printf("Track %i: '%s'\n", i, tracks[i]);
	}
    }

    regex_free(regex);
}


int main (int argc, char *argv[])
{
    char *pattern = "F.*F.*";
    find_track_regex(pattern);

    return 0;
}
