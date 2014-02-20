/* Example code for Software Systems at Olin College.

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Returns a heap-allocated string with length n, with
// the given string in the middle, surrounded by fillchar.
//
// For example, if s is allen, n is 10 and fillchar is .
// the result is ..allen... 

char *center(char *s, int n, char fillchar)
{

    if(n < strlen(s)){
        printf("n (%i) is less than the string length of %zd, cannot fill!\n", n, strlen(s));
        exit(1);
    }


    char *centered_string = (char *)malloc((n+1)*sizeof(char));
    centered_string[n] = '\0'; //Add null terminator to always return a valid string

    int numFill = n - strlen(s);
    printf("%d\n", numFill);
    int i;

    //First fill the prepended fill characters
    for(i =0; i < numFill/2; i ++){
        centered_string[i] = fillchar;
    }
    //Then copy the real string
    strcpy(centered_string + i,s);

    //Then fill the right hand side padding
    for(i +=strlen(s); i < n; i ++){
        centered_string[i] = fillchar;
    }


   return centered_string;
}


int main (int argc, char *argv[])
{
    char *s = center("Software", 30, '.');
    printf("%s\n", s);

    char *s2 = center("Systems", 31, '-');
    printf("%s\n", s2);

    char *s3 = center("Spring 2014", 32, '*');
    printf("%s\n", s3);

    char *s4 = center("Exam 1", 33, '^');
    printf("%s\n", s4);

    char *s5 = center("allen", 10, '.');
    printf("%s\n", s5);

    char *s7 = center("*$#Finishing Exam 1#$*", 80, '~');
    printf("%s\n", s7);

    return 0;
}
