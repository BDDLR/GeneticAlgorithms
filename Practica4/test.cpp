#include <iostream>
#include <algorithm>
#include <array>
#include <chrono>
#include "tournament.h"

using namespace std;

/*
	Algoritmo de selección por torneo:

	- Barajar los individuos de la población
	- Escoger p individuos (2)
	- Elegir un individuo al azar -> esto genera 16 individuos
	- Barajar de nuevo
	- Escoger p individuos (2)
	- Elegir un individuo al azar -> esto completa los 32 individuos
*/

void shufflePopulation(bitset<BITS_PER_INDIVIDUAL> set[]){
	
	array<int, TOTAL_INDIVIDUALS> arr;
	bitset<BITS_PER_INDIVIDUAL> aux[TOTAL_INDIVIDUALS];
	int aux1;
	int aux2;

	for (int i = 0; i < TOTAL_INDIVIDUALS; i++)
	{
		arr[i] = set[i].to_ulong();
	}

	random_shuffle(arr.begin(), arr.end());

	for (int i = 0; i < TOTAL_INDIVIDUALS; i++)
	{
		set[i] = arr[i];
	}
}

bitset<BITS_PER_INDIVIDUAL> tournamentSelection(bitset<BITS_PER_INDIVIDUAL> &p1, bitset<BITS_PER_INDIVIDUAL> &p2){
	
	int flip = rand() % 2;

	if((p1.to_ulong() < p2.to_ulong()) && flip == 1)
	{
		return p2;
	}
	else if ((p1.to_ulong() < p2.to_ulong()) && flip == 0)
	{
		return p1;
	}
	else if ((p1.to_ulong() > p2.to_ulong()) && flip == 1)
	{
		return p1;
	}
	else{
		return p2;
	}
	
}

int main(int argc, char const *argv[])
{
	bitset<BITS_PER_INDIVIDUAL> initial_individuals [TOTAL_INDIVIDUALS];
	bitset<BITS_PER_INDIVIDUAL> tournament_selection [TOTAL_INDIVIDUALS];

	fillIndividuals(initial_individuals);

	for (int z = 0; z < 2; ++z)
	{
		shufflePopulation(initial_individuals);

		for (int i = 0, winner = z*16; i < TOTAL_INDIVIDUALS; i+=2)
		{
			tournament_selection[winner] = tournamentSelection(initial_individuals[i], initial_individuals[i+1]);
			winner++;
		}
	}
	
	return 0;
}



