#include <cstdio>
#include <cstdlib>
#include <time.h>

using namespace std;

void fillArray();


float f[10];

int main(int argc, char const *argv[])
{
	srand (time(NULL));
	fillArray();

	for (int i = 0; i < 10; i++)
	{
		if(i == 0)
			printf("| %.02f | ", f[i]);
		else if(i < 9){
			printf(" %.02f | ", f[i]);
		}
		else
			printf(" %.02f | \n", f[i]);
	}

	return 0;
}


void fillArray(){
	for (int i = 0; i < 10; i++)
	{
		f[i] = (float) (rand() % (100))/((rand() % (10))+1);
	}
}