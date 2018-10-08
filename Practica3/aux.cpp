#include <iostream>
#include <bitset>
#include <vector>
#include <random>
#include <fstream>

#define TOTAL_INDIVIDUALS 32
#define BITS_PER_INDIVIDUAL 5
#define MAX_INDIVIDUAL_VALUE 31
#define PROBABILITY 10
#define CROSS_POINT 2
#define MAX_SEARCH_VALUE 100

using namespace std;

//Fill the individuals randomly between 0 and 31
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

bitset<BITS_PER_INDIVIDUAL> rouleteSelection(bitset<BITS_PER_INDIVIDUAL> set[], int totalAptitude) {
	
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
	int min = 32, aux = 0;

	for (int i = 0; i < TOTAL_INDIVIDUALS; i++)
	{
		aux = set[i].to_ulong();
		
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
		aux = set[i].to_ulong();
		
		if(aux > max){
			max = aux;
		}
		
	}
	return max;
}

int getGenerationAverage(bitset<BITS_PER_INDIVIDUAL> set[]){
	return (getTotalAptitude(set)/TOTAL_INDIVIDUALS);
}

int main(int argc, char const *argv[])
{

	if(argc != 2){
		cout << "Correct way: ./roulete <NUM_GENERATIONS>" << endl;
		exit(0);
	}

	int NUM_GENERATIONS = atoi(argv[1]);

	bitset<BITS_PER_INDIVIDUAL> initial_individuals [TOTAL_INDIVIDUALS];
	bitset<BITS_PER_INDIVIDUAL> roulete_selection [TOTAL_INDIVIDUALS];
	bitset<BITS_PER_INDIVIDUAL> cross_descendency [TOTAL_INDIVIDUALS];
	bitset<BITS_PER_INDIVIDUAL> mutation_descendency [TOTAL_INDIVIDUALS];

	ofstream file;
	file.open("generation.txt", fstream::out);
	
	fillIndividuals(initial_individuals);		//Random individuals

	for (int k = 0; k < NUM_GENERATIONS; k++)
	{
		int totalAptitude = getTotalAptitude(initial_individuals);

		for (int i = 0; i < TOTAL_INDIVIDUALS; i++)
		{
			roulete_selection[i] = rouleteSelection(initial_individuals, totalAptitude);
		}

		for (int i = 0; i < TOTAL_INDIVIDUALS; )
		{
			cross_descendency[i] = crossAlgorithm(roulete_selection[i], roulete_selection[i + 1], CROSS_POINT);
			cross_descendency[i + 1] = crossAlgorithm(roulete_selection[i + 1], roulete_selection[i], CROSS_POINT);
			i+=2;
		}

		for (int i = 0; i < TOTAL_INDIVIDUALS; i++)
		{
			mutation_descendency[i] = cross_descendency[i];
		}

		int mutation_value = TOTAL_INDIVIDUALS / PROBABILITY;

		srand (time(NULL));

		for (int i = 0; i < mutation_value; i++)
		{
			int indivual_to_mutate = rand() % TOTAL_INDIVIDUALS;
			mutation_descendency[indivual_to_mutate] = mutationAlgorithm(cross_descendency[indivual_to_mutate]);
		}

		int min_gen_value = getMinGenerationValue(mutation_descendency);
		int max_gen_value = getMaxGenerationValue(mutation_descendency);
		int gen_average = getGenerationAverage(mutation_descendency);

		cout << "Minimun: " << min_gen_value << endl;
		cout << "Maximun: " << max_gen_value << endl;
		cout << "Average: " << gen_average << endl;


		for (int i = 0; i < TOTAL_INDIVIDUALS; i++)
		{
			initial_individuals[i] = mutation_descendency[i];
		}


		file << "Generation: " << k+1 << endl;
		for (int i = 0; i < TOTAL_INDIVIDUALS; i++)
		{
			file << initial_individuals[i] << " - " << roulete_selection[i] << " - " << cross_descendency[i] << " - " << mutation_descendency[i] << endl;
		}
		file << endl;file << endl;
		cout << endl;
	}

	
	

	return 0;
}

