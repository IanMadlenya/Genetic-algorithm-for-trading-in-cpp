#ifndef STOCKDEF
#define STOCKDEF

//////////////////////////////////////////////////////
//                                                  //
//          Class that handles the stock            //
//                     prices                       //
//                                                  //
//                  Imanol Perez                    //
//                  January 2017                    //
//                                                  //
//////////////////////////////////////////////////////

#include <cmath>
#include "Exception.hpp"//  This class throws errors using the class "error"
#include "Quote.hpp"

class Stock;

class Stock
{
private:
   // member variables
   std::string mName; // name of the stock
   Quote* mData; // historical data
   int mSize, mFilled;

public:
   Stock();//constructor
   Stock(std::string, int); // constructor
   std::string getName(void); // get stock's name
   int getFilled(void); // returns mFilled
   Quote getData(int); // returns mFilled
   void addData(Quote); // add historical data
   void popLeft(void); // delete first historical data
   double mean(void); // calculates mean of the prices
   Stock sample(int, int);// Returns a sample of the historical data
   //output
   friend std::ostream& operator<<(std::ostream&, Stock&);


};


#endif
