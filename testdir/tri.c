#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc != 2)
        return (1);
    float f = atof(argv[1]);
    printf ("sin: %f\n", sin(f));
    printf ("cos: %f\n", cos(f));
    return (0);
}