#include <iostream>
#include "Quote.hpp"
#include "Stock.hpp"
#include "Organism.hpp"
#include "Population.hpp"
#include <algorithm>
#include "global.hpp"
#include <fstream>

//////////////////////////////////////////////////////
//                                                  //
//             Class for the population             //
//                                                  //
//                  Imanol Perez                    //
//                  January 2017                    //
//                                                  //
//////////////////////////////////////////////////////

Population::Population() {

}

Population::Population(Stock S, int s, int ma)
{
  /*

  Constructor. Creates the object of class Population.

  */
  size=s;
  stock=S;
  filled=0;
  max_ma=ma;
  organisms=new Organism[size];

  // We fill in the population with null organisms.
  for (int i=0; i<size; i++)
  {
    organisms[i] = Organism(0, 0); // Quotes with moving averages 0 are considered Null
  }

}



void Population::addOrganism(Organism org) {
  /*

  We add the organism org to the population. If the population is full, throw exception.

  */

  if (filled==size) throw Exception("Population limit reached", "There is no space to store more organisms");

  organisms[filled]=org;
  filled++;

}

double Population::fitness(Stock& s, int n, int start) {
	/*

	Fitness function that will work as the criteria to select the top 20% of organisms.

	*/

	if (n<0 or n>=filled) throw Exception("Index out of bounds", "The index is negative or too big");
	double returns=1;

	// Instead of calculating returns over all the interval available, it only
	// runs through the interval specified in s, which was picked randomly.
	// The objective is to have organisms that perform well in any random
	// period of time.
	for (int i=start; i<s.getFilled()-1; i++) {
		// We run the algorithm: buy or sell S&P 500 depending on whether a mean average is larger
		// or less than the other mean average.

		if (s.sample(i-organisms[n].MA1+1, i).mean()>s.sample(i-organisms[n].MA2+1, i).mean()) {
			returns*=s.getData(i+1).getPrice()/s.getData(i).getPrice();	
		} else {
			returns*=s.getData(i).getPrice()/s.getData(i+1).getPrice();
		}
		

	}
	return returns;
}


double Population::returns(int n) {
	/*
	
	Gives the overall returns of the organism n

	*/

	if (n<0 or n>=filled) throw Exception("Index out of bounds", "The index is negative or too big");
	double returns=1;
	for (int i=max_ma; i<stock.getFilled()-1; i++) {
		if (stock.sample(i-organisms[n].MA1+1, i).mean()>stock.sample(i-organisms[n].MA2+1, i).mean()) {
			returns*=stock.getData(i+1).getPrice()/stock.getData(i).getPrice();	
		} else {
			returns*=stock.getData(i).getPrice()/stock.getData(i+1).getPrice();
		}
		

	}
	return returns;
}




Population Population::top20(void) {
	/*

	It returns the top 20% of the organisms of the population

	*/

	// How many organisms form the 20% of the population?
	int top20=floor(0.2*filled);
	Population population=Population(stock, top20, max_ma);

	{
		// Select a random interval of length FITNESS_TIME_INTERVAL,
		// and take a sample of S&P 500 for this interval.
		// The objective is to obtain organisms that perform
		// well in any random period of time.
		int r=rand()%(stock.getFilled()-FITNESS_TIME_INTERVAL);
		Stock S=stock.sample(std::max(0, r-max_ma), r+FITNESS_TIME_INTERVAL);
		
		// We calculate fitness score of the organisms
		for (int j=0; j<filled; j++) {
			organisms[j].returns=fitness(S, j, max_ma);
		}
	}

	// We store in the variable population the top 20% of the organisms
	for (int i=0; i<top20; i++) {
		for (int j=i+1; j<filled; j++) {
			if (organisms[j].returns>organisms[i].returns) {
				// Switch values between organisms[i] and organisms[j]
				Organism temp=organisms[i];
				organisms[i]=organisms[j];
				organisms[j]=temp;
			}
		}
		population.addOrganism(organisms[i]);
	}

	return population;

}

void Population::crossover(void) {
	/*

	Performs a crossover of the top 20% of the population to generate children.

	*/

	{
		Population top= top20();
		filled=0;

		for (int i=0; i<top.size; i++) {
			addOrganism(top.organisms[i]);
		}

		// We want to have a population of static size. Thus, while the population
		// size is not the original one, create new children.
		// To produce a children, pick two random and distinct parents. Take the
		// first moving average of one of them, and the second moving average of
		// the other one, and create a child.
		while (filled!=size) {
			int r1=rand()%top.size;
			int r2=rand()%top.size;
			if (r1==r2) continue;
			if (rand()%2==0) {
				addOrganism(Organism(top.organisms[r1].MA1, top.organisms[r2].MA2));
			} else {
				addOrganism(Organism(top.organisms[r2].MA1, top.organisms[r1].MA2));
			}
		}
	
	}
	
}

void Population::mutation(void) {
	/*

	Mutates some of the children.

	*/

	int top20=floor(0.2*filled);

	// We do not mutate the first 20% of the population, as these are the parents.
	// We only want to mutate children.
	for (int i=top20; i<filled; i++) {
		
		// Not all children are mutated. A children will suffer from a mutation
		// with probability MUTATION_PROBABILITY. In this case, we update
		// the moving average of the children with a random value between 1
		// and max_ma.
		if ((double)rand()/(RAND_MAX)<=MUTATION_PROBABILITY) {

			organisms[i].MA1=1+rand()%(max_ma+1);
			
		}
		if ((double)rand()/(RAND_MAX)<=MUTATION_PROBABILITY) {
			organisms[i].MA2=1+rand()%(max_ma+1);
		}

		// Check if the organism i is in population, as we do not
		// want to two identical children.
		for (int j=0; j<i; j++) {
			if (organisms[i].MA1==organisms[j].MA1 && organisms[i].MA2==organisms[j].MA2) {
				// Prevent from moving to children i+1, in order
				// to go to the mutation loop again with children i.
				i-=1;
				break;
			}
		}

	}
}

std::ostream& operator<<(std::ostream& output, Population& population) {
  /*

  Allows to output an object of class Population.

  */
  output<<"Population: "<<population.filled<<"\n";
  output<<"Stock: "<<population.stock.getName()<<"\n\n";
  for (int i=0; i<population.size; i++) {
    if (population.organisms[i].isNull()) continue;
    output<<"Organism no. "<<(i+1)<<":\n"<<population.organisms[i]<<"\n";
  }

  return output;
}