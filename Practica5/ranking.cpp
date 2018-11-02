#include "ranking.h"
#include <iostream>
#include <algorithm>
#include <array>
#include <cmath>
#include <map>

using namespace std;

map<int, float> expected_values;

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

float getIndividualAptitude(bitset<BITS_PER_INDIVIDUAL> individual){
	int result;
	float numerador;
	float denominador;
	float x = individual.to_ulong();
	float senX = sin(x);

	numerador = x - 5;
	denominador = 2 + senX;

	result = abs(numerador/denominador);

	return (int) result;
}	

void simple_ranking(bitset<BITS_PER_INDIVIDUAL> population[]) {
    int values[TOTAL_INDIVIDUALS];
    int n = sizeof(values) / sizeof(values[0]); 
    for(int i = 0; i < TOTAL_INDIVIDUALS; i++) {
        values[i] = getIndividualAptitude(population[i]);
    }
    
    sort(values, values+n);
    
    for (int i = 1; i <= TOTAL_INDIVIDUALS; i++) {
        expected_values[values[i]] = MIN_R + (MAX_R - MIN_R) * (i - 1) / (TOTAL_INDIVIDUALS - 1);
    }
}

float get_expected_value(bitset<BITS_PER_INDIVIDUAL>& p) {
    return expected_values[(int)(p.to_ulong())];
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
	
	float flip = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

	//printf("%.2f\n", flip);

	if((getIndividualAptitude(p1) < getIndividualAptitude(p2)) && flip >= 0.70)
	{
		return p2;
	}
	else if ((getIndividualAptitude(p1) < getIndividualAptitude(p2)) && flip < 0.70)
	{
		return p1;
	}
	else if ((getIndividualAptitude(p1) > getIndividualAptitude(p2)) && flip >= 0.70)
	{
		return p1;
	}
	else{
		return p2;
	}
	
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