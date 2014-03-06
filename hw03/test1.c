#include <stdio.h>
#include <stdlib.h>

#include "rand.c"

int main (int argc, char *argv[])
{
  int i;
  double x;

  srandom (time (NULL));

  for (i=0; i<1000000; i++) {
    x = my_random_double();
    printf ("%lf\n", x);
  }
}
