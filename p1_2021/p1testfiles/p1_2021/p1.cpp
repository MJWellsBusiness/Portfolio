//Matthew Wells
//CSCI 3240
//Project 1: due September 7, 2021
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <vector>

using namespace std;

//each struct is a 3d point with coordinates
struct point {
	float x;
	float y;
	float z;
};

int main(int argc, char *argv[])
{
	//setting arguments to srand and number of points respectively
	srand(atoi(argv[1]));
	
	int i, numpts = atoi(argv[2]);

	const float MIN = 0;
	const float MAX = 10000;
	float distMin, distMax, distance;

	vector<point> pts(numpts);

	//Initializes each point in the vector
	for (i = 0; i < numpts; i++)
	{
		pts[i].x = (MAX-MIN) * ((float)rand()/RAND_MAX) + MIN;
		pts[i].y = (MAX-MIN) * ((float)rand()/RAND_MAX) + MIN;
		pts[i].z = (MAX-MIN) * ((float)rand()/RAND_MAX) + MIN;
	}

	//These are the distance boundaries of our program swapped so that they'll immediately be replaced upon first iteration
	distMin = sqrt(300000000);
	distMax = 0;

	//This loop specifically will not run any distance calculations twice in order to run at optimal speed.
	//It stores the largest and smallest distances as it progresses.
	for (i = 0; i < numpts-1; i++)
	{
		for (int j = i+1; j < numpts; j++)
		{
			distance = sqrt(float(pow(pts[j].x - pts[i].x,2) + pow(pts[j].y - pts[i].y,2) + pow(pts[j].z - pts[i].z,2)));
			if(distance > distMax)
				distMax = distance;
			if(distance < distMin)
				distMin = distance;
		}
	}
	
	//Prints min and max distances to the third decimal place
	printf("%.3f %.3f\n", distMin,distMax);
}
