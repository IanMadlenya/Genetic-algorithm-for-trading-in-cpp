#include <iostream>
#include "Organism.hpp"
#include <algorithm>

//////////////////////////////////////////////////////
//                                                  //
//           Class for a single organism            //
//                                                  //
//                  Imanol Perez                    //
//                  January 201                    //
//                                                  //
//////////////////////////////////////////////////////

Organism::Organism() {

}

Organism::Organism(int i, int j)
{
  /*

  Constructor

  */

  //Updates moving averages, which must be greater or equal to 0.
  MA1=std::max(i, 0);
  MA2=std::max(j, 0);
  returns=0.0;
}

Organism::~Organism() { }

void Organism::DisposeObject() {
	delete this;
}



bool Organism::isNull(void) {
  /*

  Checks if the organism is null.
  An organism is considered null if both moving
  averages are zero.

  */

  return MA1==0 && MA2==0;
}



std::ostream& operator<<(std::ostream& output, Organism& org) {
  /*

  Allows to output an object of class Organism.

  */
	
  if (org.returns!=0.0) output<<"Returns: "<<org.returns<<"\n";
  output<<"First Moving Average: "<<org.MA1<<"\nSecond Moving Average: "<<org.MA2<<"\n";

  return output;
}

