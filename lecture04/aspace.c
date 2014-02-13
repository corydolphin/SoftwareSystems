/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

#include <stdio.h>
#include <stdlib.h>

int global;


void foo(){
    int loc = 3;
    printf ("Address of local in foo is %p\n", &loc);
}

int main ()
{
    int local = 5;
    void *p = malloc(128);
    int local2 = 1;
    foo();
    printf ("Address of main is %p\n", main);
    printf ("Address of global is %p\n", &global);
    printf ("Address of local is %p\n", &local);
    printf ("Address of p is %p\n", p);
    return 0;
}
