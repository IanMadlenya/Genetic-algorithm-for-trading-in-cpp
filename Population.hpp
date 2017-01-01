#ifndef POPULATIONDEF
#define POPULATIONDEF

//////////////////////////////////////////////////////
//                                                  //
//             Class for the population             //
//                                                  //
//                  Imanol Perez                    //
//                  December 2016                   //
//                                                  //
//////////////////////////////////////////////////////

#include <cmath>
#include "Exception.hpp"//  This class throws errors using the class "error"
#include "Quote.hpp"
#include "Stock.hpp"
#include "Organism.hpp"
#include <algorithm>

class Population;

class Population
{
public:
   Population(); // constructor
   Population(Stock, int, int); // constructor

   void addOrganism(Organism); // Add organism
   double fitness(Stock&, int, int); // fitness function: gives the returns of the organism in a random period of a specific length
   double returns(int); // fitness function: gives the returns of the organism
   Population top20(void); // returns the strongest 20% organisms
   void crossover(void); // performs crossover
   void mutation(void); // performs mutation of the new generation
   
   Stock stock;
   Organism* organisms;
   int size, filled, max_ma;

   //output
   friend std::ostream& operator<<(std::ostream&, Population&);


};


#endif
