#ifndef ORGANISMDEF
#define ORGANISMDEF

//////////////////////////////////////////////////////
//                                                  //
//           Class for a single organism            //
//                                                  //
//                  Imanol Perez                    //
//                  January 2017                    //
//                                                  //
//////////////////////////////////////////////////////

#include <cmath>
#include "Exception.hpp"//  This class throws errors using the class "error"
#include <algorithm>

class Organism;

class Organism
{
public:
   int MA1;   // first moving average
   int MA2; // second moving average
   double returns; // returns created by this organism
   Organism(); // constructor
   Organism(int, int); // constructor
   ~Organism();
   void DisposeObject();


   bool isNull(void); // checks if organism is null
   //output
   friend std::ostream& operator<<(std::ostream&, Organism&);


};


#endif
