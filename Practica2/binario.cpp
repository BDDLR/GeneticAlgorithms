#include <cstdio>
#include <cstdlib>
#include <time.h>

using namespace std;

void fillArray();


int bin[10];

int main(int argc, char const *argv[])
{
	srand (time(NULL));
	fillArray();

	for (int i = 0; i < 10; i++)
	{
		if(i == 0)
			printf("| %d | ", bin[i]);
		else if(i < 9){
			printf(" %d | ", bin[i]);
		}
		else
			printf(" %d | \n", bin[i]);
	}

	return 0;
}


void fillArray(){
	for (int i = 0; i < 10; i++)
	{
		bin[i] = rand() % 2;
	}
}