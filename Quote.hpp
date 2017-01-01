#ifndef QUOTEDEF
#define QUOTEDEF

//////////////////////////////////////////////////////
//                                                  //
//          Class that handles the quotes           //
//       of a certain stock in a certain date       //
//                                                  //
//                  Imanol Perez                    //
//                  January 2017                    //
//                                                  //
//////////////////////////////////////////////////////

#include <cmath>
#include "Exception.hpp"//  This class throws errors using the class "error"
#include <ctime>

class Quote;

class Quote
{
private:
   // member variables
   double mPrice;   // price of the stock
   std::string mName; // name of the stock
   std::string mDate; // date of the quote

public:
   Quote(); // constructor
   Quote(std::string, double, std::string); // constructor
   std::string getName(void); // Get stock's name
   double getPrice(void); // Get stock's price
   void setPrice(double); // Set stock's price
   std::string getDate(void); // Get stock's date
   void setDate(std::string); // Set stock's date
   void increasePrice(double); // Increase stock's price
   void addReturn(double); // Add return (in percentage terms)
   bool isNull(void); // Returns true if the quote is null


   //output
   friend std::ostream& operator<<(std::ostream&, Quote&);


};


#endif
