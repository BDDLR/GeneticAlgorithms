#include <cstdio>
#include <string>
#include <cstdlib>
#include "gfx.h"

using namespace std;

void fillArray(int arr[], int tam);

int main(int argc, char const *argv[])
{

	//Size of the window displayed
	int ysize = 400;
	int xsize = 1200;

	//Array of values
	int values[10];
	srand (time(NULL));

	fillArray(values, sizeof(values)/sizeof(int));

	// Open a new window for drawing.
	gfx_open(xsize,ysize,"Line Histogram");

	// Set the current drawing color to green.
	gfx_color(0,255,0);

	//Axis line
	gfx_line(80, 300, 1110, 300);


	int max = 300;
	int step = 1000 / (sizeof(values)/sizeof(int));
	
	//Loop to draw the values as a histogram
	for (int i = 0; i < (sizeof(values)/sizeof(int)) ; i++)
	{
		if(i == (sizeof(values)/sizeof(int)) -1){
			gfx_Number((i+1)*step-5, max - (values[i]*5+10), (char*)to_string(values[i]).c_str());
			gfx_Number((i+1)*step, 320, (char*)to_string(i+1).c_str());
		}
		else{
			gfx_line((i+1)*step, max - (values[i]*5), (i+2)*step, max - (values[i+1]*5));
			gfx_Number((i+1)*step-5, max - (values[i]*5+10), (char*)to_string(values[i]).c_str());
			gfx_Number((i+1)*step, 320, (char*)to_string(i+1).c_str());	
		}
		
	}


	char c;
	while(1) {
		// Wait for the user to press a character.
		c = gfx_wait();

		// Quit if it is the letter q.
		if(c=='q') break;
	}


	return 0;
}

void fillArray(int arr[], int tam){
	for (int i = 0; i < tam; i++)
	{
		arr[i] = rand() % 50;
	}
}
