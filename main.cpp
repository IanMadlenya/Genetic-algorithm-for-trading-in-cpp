#include <stdlib.h>
#include <iostream>
#include <cassert>
#include <fstream>
#include "Exception.hpp"
#include "Quote.hpp"
#include "Stock.hpp"
#include "Organism.hpp"
#include "Population.hpp"
#include "global.hpp"
#include <math.h>
#include <algorithm>

//////////////////////////////////////////////////////
//                                                  //
//                   Main file                      //
//                                                  //
//                  Imanol Perez                    //
//                  January 2017                    //
//                                                  //
//////////////////////////////////////////////////////


void loadData(Stock&, std::string);
Population randomPopulation(Stock, int, int);
Population geneticAlgorithm(Stock, int, int, int);

Population randomPopulation(Stock stock, const int max_population, const int max_ma) {
	Population population=Population(stock, max_population, max_ma);
	for (int i=0; i<max_population; i++) {
		population.addOrganism(Organism(1+rand()%(max_ma+1), 1+rand()%(max_ma+1)));
	}
	return population;
}

void loadData(Stock& S, std::string file) {
	/*

	Loads all historical data available in the given file into
	the object S, of class Stock.

	*/


	std::ifstream input0(file.c_str());
	assert(input0.is_open());
	int lines=0;
	std::string date;
	double price;
	while (!input0.eof()) {
		input0 >> date >> price;
		lines+=1;
	}
	input0.close();
	S=Stock("S&P 500", lines);

	std::ifstream input(file.c_str());

	assert(input.is_open());
	while (!input.eof()) {
		input >> date >> price;
		S.addData(Quote(S.getName(), price, date));
	}
	input.close();

}

Population geneticAlgorithm(Stock stock, const int max_population, const int max_ma, const int number_generations) {
	/*

	Runs the genetic algorithm, simulating all the generations.

	*/



	// Produce the initial population randomly
	std::cout<<"Generating a random population of "<<max_population<<" organisms...";
	Population population=randomPopulation(stock, max_population, max_ma);
	std::cout<<" Done.\n";

	// Simulate all the generations
	std::cout<<"Starting simulation.\n";
	for (int i=1; i<=number_generations; i++) {
		// We perform a crossover, selecting the top 20% of the population, and creating a new generation of children
		population.crossover();

		// We randomly mutate some of the children
		population.mutation();	
		std::cout << "\r" <<"Generation number "<<i<<"/"<<number_generations<<std::flush;
	}
	std::cout<<"\nCalculating returns of the organisms...";

	// We calculate returns of the organisms
	for (int j=0; j<population.filled; j++) {
		population.organisms[j].returns=population.returns(j);
	}

	std::cout<<" Done.";

	return population;

	

}

int main(int argc, char* argv[])
{
	// Initialise random seed
	srand(time(NULL));

	// We load the historical data for S&P 500
	Stock SP500;
	loadData(SP500, "SP500.dat");


	// We run the genetic algorithm. We simulate the evolution of a population
	// of POPULATION_SIZE organisms, for NUMBER_OF_GENERATIONS generations.
	Population population=geneticAlgorithm(SP500.sample(0, floor(0.6*SP500.getFilled())), POPULATION_SIZE, MAX_MOVING_AVERAGE, NUMBER_OF_GENERATIONS);
	
	// Now, we show the top 3 organisms of the last generation
	for (int i=0; i<3;i++) {
		std::cout<<"\nOrganism no. "<<(i+1)<<":\n"<<population.organisms[i]<<"\n";
	}
	
	
}
