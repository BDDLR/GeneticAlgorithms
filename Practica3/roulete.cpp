#include <iostream>
#include <bitset>
#include <vector>
#include <random>

#define TOTAL_INDIVIDUALS 32
#define BITS_PER_INDIVIDUAL 5
#define MAX_INDIVIDUAL_VALUE 31
#define PROBABILITY 10
#define CROSS_POINT 2

using namespace std;

//Fill the individuals randomly between 0 and 31
void fillIndividuals(bitset<BITS_PER_INDIVIDUAL> set[]){
	srand (time(NULL));
	for (int i = 0; i < TOTAL_INDIVIDUALS; i++)
		set[i] = rand();
}

void printIndividuals(bitset<BITS_PER_INDIVIDUAL> set[]){
	for (int i = 0; i < TOTAL_INDIVIDUALS; i++)
		cout << set[i].to_ulong() << endl;
}

int getIndividualValue(bitset<BITS_PER_INDIVIDUAL> individual){
	return individual.to_ulong();
}

int getIndividualAptitude(bitset<BITS_PER_INDIVIDUAL> individual){
	return (individual.to_ulong()*individual.to_ulong());
}	

int getTotalAptitude(bitset<BITS_PER_INDIVIDUAL> set[]){
	int total = 0;
	for (int i = 0; i < TOTAL_INDIVIDUALS; i++)
	{
		total += getIndividualAptitude(set[i]);
	}
	return total;
}	

bitset<BITS_PER_INDIVIDUAL> rouletteSelection(bitset<BITS_PER_INDIVIDUAL> set[], int totalAptitude) {
    float r = rand() % (totalAptitude + 1);
    int add = 0;
    int i;
    for(i = 0; i < TOTAL_INDIVIDUALS && add < r; i++) {
        add += getIndividualAptitude(set[i]);
    }
    return set[i];
}

bitset<BITS_PER_INDIVIDUAL> crossAlgorithm(bitset<BITS_PER_INDIVIDUAL> &p1, 
	bitset<BITS_PER_INDIVIDUAL> &p2, 
    int cross_point) {

    bitset<BITS_PER_INDIVIDUAL> aux = p1;

    for (int i = 0; i <= cross_point; i++)
    {
    	aux.set(cross_point - i, p2[cross_point - i]);
    }

    //aux.set(cross_point, p2[cross_point]);

    return aux;
}

int main(int argc, char const *argv[])
{
	bitset<BITS_PER_INDIVIDUAL> initial_individuals [TOTAL_INDIVIDUALS];
	bitset<BITS_PER_INDIVIDUAL> roulette_selection [TOTAL_INDIVIDUALS];
	bitset<BITS_PER_INDIVIDUAL> cross_descendency [TOTAL_INDIVIDUALS];
	bitset<BITS_PER_INDIVIDUAL> mutation_descendency [TOTAL_INDIVIDUALS];
	
	fillIndividuals(initial_individuals);		//Random individuals

	for (int k = 0; k < 1; k++)
	{
		int totalAptitude = getTotalAptitude(initial_individuals);
		cout << "Initial total aptitude " << totalAptitude << endl;

		for (int i = 0; i < TOTAL_INDIVIDUALS; i++)
		{
			roulette_selection[i] = rouletteSelection(initial_individuals, totalAptitude);
		}

		cout << "Roulette total aptitude " << getTotalAptitude(roulette_selection) << endl;

		for (int i = 0; i < TOTAL_INDIVIDUALS/2; i++)
		{
			cross_descendency[i] = crossAlgorithm(roulette_selection[i], roulette_selection[i + 1], CROSS_POINT);
			cross_descendency[i + 1] = crossAlgorithm(roulette_selection[i + 1], roulette_selection[i], CROSS_POINT);
		}

		cout << "Cross total aptitude " << getTotalAptitude(cross_descendency) << endl;

		cout << endl;
	}

	
	

	return 0;
}

