#include "roulete.h"
#include <iostream>
void fillIndividuals(bitset<BITS_PER_INDIVIDUAL> set[]){
	srand (time(NULL));
	for (int i = 0; i < TOTAL_INDIVIDUALS; i++)
		set[i] = rand() % MAX_INDIVIDUAL_VALUE;
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
	
    int r = rand() % (totalAptitude + 1);
    int add = 0;
    int i;
    for(i = 0; i < TOTAL_INDIVIDUALS && add < r; i++) {
        add += getIndividualAptitude(set[i]);
    }
    return set[i];
}

bitset<BITS_PER_INDIVIDUAL> crossAlgorithm(bitset<BITS_PER_INDIVIDUAL> &p1, bitset<BITS_PER_INDIVIDUAL> &p2, int cross_point) {

    bitset<BITS_PER_INDIVIDUAL> aux = p1;

    for (int i = 0; i <= cross_point; i++)
    {
    	aux.set(cross_point - i, p2[cross_point - i]);
    }

    return aux;
}

bitset<BITS_PER_INDIVIDUAL> mutationAlgorithm(bitset<BITS_PER_INDIVIDUAL> individual){
	bitset<BITS_PER_INDIVIDUAL> result = individual;

	int cont = 0;

	while(cont <= MAX_SEARCH_VALUE)
	{
		
		int mutation_point = rand() % BITS_PER_INDIVIDUAL;
		if(result[mutation_point] == 0){
			result.set(mutation_point, 1);
			break;
		}
		cont++;
	}
	
	return result;
}

int getMinGenerationValue(bitset<BITS_PER_INDIVIDUAL> set[]){
	int min = 1000000, aux = 0;

	for (int i = 0; i < TOTAL_INDIVIDUALS; i++)
	{
		aux = getIndividualAptitude(set[i]);
		
		if(aux < min){
			min = aux;
		}
		
	}
	return min;
}

int getMaxGenerationValue(bitset<BITS_PER_INDIVIDUAL> set[]){
	int max = 0, aux = 0;

	for (int i = 0; i < TOTAL_INDIVIDUALS; i++)
	{
		aux = getIndividualAptitude(set[i]);
		
		if(aux > max){
			max = aux;
		}
		
	}
	return max;
}

int getGenerationAverage(bitset<BITS_PER_INDIVIDUAL> set[]){
	return (getTotalAptitude(set)/TOTAL_INDIVIDUALS);
}