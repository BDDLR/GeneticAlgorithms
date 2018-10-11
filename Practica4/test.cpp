#include <iostream>
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

bitset<BITS_PER_INDIVIDUAL>* sortPopulation(bitset<BITS_PER_INDIVIDUAL> set[]){
	
	int aux1;
	int aux2;

	//bitset<BITS_PER_INDIVIDUAL>* aux = set;

	bitset<BITS_PER_INDIVIDUAL> aux[TOTAL_INDIVIDUALS];

	for (int i = 0; i < TOTAL_INDIVIDUALS; i++)
	{
		aux[i] = set[i];
	}

	for (int i = 0; i < TOTAL_INDIVIDUALS; i++)
	{
		aux1 = rand() % TOTAL_INDIVIDUALS;
		aux2 = rand() % TOTAL_INDIVIDUALS;

		set[i].set();
	}
	return aux;
}

int main(int argc, char const *argv[])
{
	bitset<BITS_PER_INDIVIDUAL> initial_individuals [TOTAL_INDIVIDUALS];
	bitset<BITS_PER_INDIVIDUAL> tournament_selection [TOTAL_INDIVIDUALS];

	fillIndividuals(initial_individuals);

	for (int i = 0; i < TOTAL_INDIVIDUALS; i++)
	{
		cout << initial_individuals[i] << endl;
	}

	cout << " ------- " << endl;

	sortPopulation(initial_individuals);

	for (int i = 0; i < TOTAL_INDIVIDUALS; i++)
	{
		cout << initial_individuals[i] << endl;
	}

	
	return 0;
}



