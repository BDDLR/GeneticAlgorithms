#include <iostream>
#include <fstream>
#include "tournament.h"
#include "gfx.h"

void drawHistogram(int minGenerationValues[], int maxGenerationValues[], int generationValuesAverage[], int num_gen);

int main(int argc, char const *argv[])
{

	if(argc != 2){
		cout << "Correct way: ./roulette <NUM_GENERATIONS>" << endl;
		exit(0);
	}

	ofstream logGenerations;
	logGenerations.open("logGenerations.txt", fstream::out);

	int NUM_GENERATIONS = atoi(argv[1]);

	bitset<BITS_PER_INDIVIDUAL> initial_individuals [TOTAL_INDIVIDUALS];
	bitset<BITS_PER_INDIVIDUAL> tournament_selection [TOTAL_INDIVIDUALS];
	bitset<BITS_PER_INDIVIDUAL> cross_descendency [TOTAL_INDIVIDUALS];
	bitset<BITS_PER_INDIVIDUAL> mutation_descendency [TOTAL_INDIVIDUALS];

	int minGenerationValues[NUM_GENERATIONS];
	int maxGenerationValues[NUM_GENERATIONS];
	int generationValuesAverage[NUM_GENERATIONS];
	
	fillIndividuals(initial_individuals);		//Random individuals

	for (int k = 0; k < NUM_GENERATIONS; k++)
	{
		for (int z = 0; z < P_TOURNAMENT_INDIVIDUALS; z++)
		{
			shufflePopulation(initial_individuals);

			for (int i = 0, winner = z*(TOTAL_INDIVIDUALS/P_TOURNAMENT_INDIVIDUALS); i < TOTAL_INDIVIDUALS; i+=2)
			{
				tournament_selection[winner] = tournamentSelection(initial_individuals[i], initial_individuals[i+1]);
				winner++;
			}
		}


		for (int i = 0; i < TOTAL_INDIVIDUALS; )
		{
			cross_descendency[i] = crossAlgorithm(tournament_selection[i], tournament_selection[i + 1], CROSS_POINT);
			cross_descendency[i + 1] = crossAlgorithm(tournament_selection[i + 1], tournament_selection[i], CROSS_POINT);
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

		minGenerationValues[k] = min_gen_value;
		maxGenerationValues[k] = max_gen_value;
		generationValuesAverage[k] = gen_average;

		logGenerations << "Generation: " << k+1 << endl;
		for (int i = 0; i < TOTAL_INDIVIDUALS; i++)
		{
			logGenerations << initial_individuals[i] << " -- " << tournament_selection[i] << " -- " 
			<< cross_descendency[i] << " -- " << mutation_descendency [i] << endl;
		}

		//Asign the final individuals as the begining of the next generation
		for (int i = 0; i < TOTAL_INDIVIDUALS; i++)
		{
			initial_individuals[i] = mutation_descendency[i];
		}
		
	}

	drawHistogram(minGenerationValues, maxGenerationValues, generationValuesAverage, NUM_GENERATIONS);

	return 0;
}

void drawHistogram(int minGenerationValues[], int maxGenerationValues[], int generationValuesAverage[], int num_gen){
	int ysize = 400;
	int xsize = 1200;
	float factor = 10;	
	int max = 300;
	int step = 1000 / num_gen;

	gfx_open(xsize,ysize,"Tournament Selection Results");

	// Set the current drawing color to green.
	gfx_color(0,255,0);
	//Axis line
	gfx_line(80, 300, 1110, 300);

	//Draw the y axis numbers
	for (int i = 0; i < num_gen; i++)
	{
		gfx_Number((i+1)*step, 320, (char*)to_string(i+1).c_str());	

	}
	// Set the current drawing color to red.
	gfx_color(255,0,0);
	//Draw the minumum values
	for (int i = 0; i < num_gen ; i++)
	{
		if(i == num_gen -1){
			gfx_Number((i+1)*step-5, max - (minGenerationValues[i] * factor + 10), (char*)to_string(minGenerationValues[i]).c_str());
		}
		else{
			gfx_line((i+1)*step, max - (minGenerationValues[i] * factor), (i+2)*step, max - (minGenerationValues[i+1] * factor));
			gfx_Number((i+1)*step-5, max - (minGenerationValues[i] * factor + 10), (char*)to_string(minGenerationValues[i]).c_str());
		}
		
	}
	// Set the current drawing color to blue.
	gfx_color(0,0,255);
	//Draw the maximum values
	for (int i = 0; i < num_gen ; i++)
	{
		if(i == num_gen -1){
			gfx_Number((i+1)*step-5, max - (maxGenerationValues[i] * factor + 10), (char*)to_string(maxGenerationValues[i]).c_str());
		}
		else{
			gfx_line((i+1)*step, max - (maxGenerationValues[i] * factor), (i+2)*step, max - (maxGenerationValues[i+1] * factor));
			gfx_Number((i+1)*step-5, max - (maxGenerationValues[i] * factor + 10), (char*)to_string(maxGenerationValues[i]).c_str());
		}
		
	}
	// Set the current drawing color to white.
	gfx_color(255,255,255);

	//Draw the average values
	for (int i = 0; i < num_gen ; i++)
	{
		if(i == num_gen -1){
			gfx_Number((i+1)*step-5, max - (generationValuesAverage[i] * factor + 10), (char*)to_string(generationValuesAverage[i]).c_str());
		}
		else{
			gfx_line((i+1)*step, max - (generationValuesAverage[i] * factor), (i+2)*step, max - (generationValuesAverage[i+1] * factor));
			gfx_Number((i+1)*step-5, max - (generationValuesAverage[i] * factor + 10), (char*)to_string(generationValuesAverage[i]).c_str());
		}		
	}

	char c;
	while(1) {
		// Wait for the user to press a character.
		c = gfx_wait();

		// Quit if it is the letter q.
		if(c=='q') break;
	}
}