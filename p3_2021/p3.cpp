//Matthew Wells
//CSCI 3240
//Project 3: due October 5, 2021
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <vector>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include <iostream>

//Max # of threads expected for program
#define MAXTHREADS 8

using namespace std;

void* subMinMax(void *arg);

//each struct is a 3d point with coordinates
struct point {
	float x;
	float y;
	float z;
};

//time function to see how long the function takes
double time1()
{
    struct timeval tv;

    gettimeofday( &tv, ( struct timezone * ) 0 );
    return ( (double) (tv.tv_sec + (tv.tv_usec / 1000000.0)) );
}

vector<point> pts;
int numthreads;
int numpts;
float localMax[8];
float localMin[8];

//MAX pTHREADS IS 8 (class before he said 4?)
int main(int argc, char *argv[])
{
	//This is an exit statement in case something goes horribly wrong
	alarm(90);
	
	//setting arguments to srand and number of points respectively
	srand(atoi(argv[1]));
	
	int i, rc;
	numpts = atoi(argv[2]); 
	numthreads = atoi(argv[3]);
	double time, t2;
	point tempPt;

	time = time1();

	int ids[8];
        pthread_t threadId[8];

	const float MIN = 0;
	const float MAX = 10000;
	float distMin, distMax, distance;
	
	pts.resize(numpts);

	//Initializes each point in the vector
	for (i = 0; i < numpts; i++)
	{
		pts[i].x = (MAX-MIN) * ((float)rand()/RAND_MAX) + MIN;
		pts[i].y = (MAX-MIN) * ((float)rand()/RAND_MAX) + MIN;
		pts[i].z = (MAX-MIN) * ((float)rand()/RAND_MAX) + MIN;

		//pts.push_back(tempPt);
	}

    	for (i=0; i < numthreads; i++)
    	{
        	ids[i]=i;

        	rc = pthread_create(&threadId[i],NULL,subMinMax,(void *)&ids[i]);
    	}

	//These are the distance boundaries of our program swapped so that they'll immediately be replaced upon first iteration
	distMin = sqrt(300000000);
	distMax = 0;

	for (i=0; i < numthreads; i++)
    	{
        	pthread_join(threadId[i],NULL);
    	}

        for (i=0; i < numthreads; i++)
        {
        	if(localMax[i] > distMax)
                	distMax = localMax[i];
                if(localMin[i] < distMin)
                        distMin = localMin[i];

        }


	t2 = time1();
	//Prints min and max distances to the third decimal place
	printf("%.3f %.3f\n", distMin,distMax);
	printf("TIME %lf\n", t2-time);

}

void* subMinMax(void *arg)
{
    int i, j;

    int k = *( (int *)arg );
    
   //These are the distance boundaries of our program swapped so that they'll immediately be replaced upon first iteration
   float Min = sqrt(300000000);
   float Max = 0;
   float distance;

        //This loop specifically will not run any distance calculations twice in order to run at optimal speed.
        //It stores the largest and smallest distances as it progresses.
        for (i = k; i < numpts-1; i+=numthreads)
        {
	       	for (j = i+1; j < numpts; j++)
                {
                        distance = sqrt(float(pow(pts[j].x - pts[i].x,2) + pow(pts[j].y - pts[i].y,2) + pow(pts[j].z - pts[i].z,2)));
                        if(distance > Max)
			{
                                Max = distance;
				localMax[k] = distance;
			}
                        if(distance < Min)
			{
				Min = distance;
                                localMin[k] = distance;
			}
                }	
        }
}
