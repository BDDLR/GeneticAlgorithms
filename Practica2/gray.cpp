#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <time.h>

using namespace std;

void fillArray();
int xorOp(int a, int b);


int original[10];
int gray[10];

int main(int argc, char const *argv[])
{
	srand (time(NULL));

	

	for (int j = 0; j < 10; j++)
	{
		cout << "Individuo No. " << j+1 << endl;
		fillArray();

		gray [0] = original[0];

		for (int i = 1; i < 10; i++)
		{
			gray[i] = xorOp(original[i-1], original[i]);
		}
		for (int i = 0; i < 10; i++)
		{
			if(i == 0)
				printf("\t| %d | ", original[i]);
			else if(i < 9){
				printf(" %d | ", original[i]);
			}
			else
				printf(" %d | \n", original[i]);
		}

		for (int i = 0; i < 10; i++)
		{
			if(i == 0)
				printf("\t| %d | ", gray[i]);
			else if(i < 9){
				printf(" %d | ", gray[i]);
			}
			else
				printf(" %d | \n", gray[i]);
		}
	}	

	return 0;
}

int xorOp(int a, int b){
	if(a == b)
		return 0;
	else 
		return 1;
}


void fillArray(){
	for (int i = 0; i < 10; i++)
	{
		original[i] = rand() % 2;
	}
}







