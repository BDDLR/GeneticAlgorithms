#include <bitset>

#define TOTAL_INDIVIDUALS 32
#define BITS_PER_INDIVIDUAL 5
#define MAX_INDIVIDUAL_VALUE 31
#define PROBABILITY 10
#define CROSS_POINT 2
#define MAX_SEARCH_VALUE 100
#define P_TOURNAMENT_INDIVIDUALS 2

using namespace std;

//Fill the individuals randomly between 0 and 31
void fillIndividuals(bitset<BITS_PER_INDIVIDUAL> set[]);

void shufflePopulation(bitset<BITS_PER_INDIVIDUAL> set[]);

void printIndividuals(bitset<BITS_PER_INDIVIDUAL> set[]);

int getIndividualValue(bitset<BITS_PER_INDIVIDUAL> individual);

float getIndividualAptitude(bitset<BITS_PER_INDIVIDUAL> individual);

int getTotalAptitude(bitset<BITS_PER_INDIVIDUAL> set[]);

bitset<BITS_PER_INDIVIDUAL> rouletteSelection(bitset<BITS_PER_INDIVIDUAL> set[], int totalAptitude);

bitset<BITS_PER_INDIVIDUAL> tournamentSelection(bitset<BITS_PER_INDIVIDUAL> &p1, bitset<BITS_PER_INDIVIDUAL> &p2);

bitset<BITS_PER_INDIVIDUAL> crossAlgorithm(bitset<BITS_PER_INDIVIDUAL> &p1, bitset<BITS_PER_INDIVIDUAL> &p2, int cross_point);

bitset<BITS_PER_INDIVIDUAL> mutationAlgorithm(bitset<BITS_PER_INDIVIDUAL> individual);

int getMinGenerationValue(bitset<BITS_PER_INDIVIDUAL> set[]);

int getMaxGenerationValue(bitset<BITS_PER_INDIVIDUAL> set[]);

int getGenerationAverage(bitset<BITS_PER_INDIVIDUAL> set[]);