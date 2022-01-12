
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// sqrt( 300000000 )  is  17320.508075688773 
//       10,000^2 + 10,000^2 + 10,000^2

#define GEN_RAND_3D_PT(MIN,MAX,X,Y,Z)                 \
    X = (MAX-MIN) * ((float)rand()/RAND_MAX) + MIN;  \
    Y = (MAX-MIN) * ((float)rand()/RAND_MAX) + MIN;  \
    Z = (MAX-MIN) * ((float)rand()/RAND_MAX) + MIN;

int main(int argc, char *argv[])
{
    int i, numpts = 40;
    float x,y,z;

    srand( 7 );

    if (argc > 1)
    {
        numpts = atoi(argv[1]);
    }

    for (i=0; i < numpts; i++)
    {
        GEN_RAND_3D_PT(0,10000,x,y,z);
        if (numpts < 50)
            printf("%.3f %.3f %.3f\n", x,y,z);
    }
}
