#include <iostream>
#include "Quote.hpp"
#include "Stock.hpp"
#include <ctime>
#include <cstring>
//////////////////////////////////////////////////////
//                                                  //
//          Class that handles the stock            //
//                     prices                       //
//                                                  //
//                  Imanol Perez                    //
//                  January 2017                    //
//                                                  //
//////////////////////////////////////////////////////

Stock::Stock() {

}

Stock::Stock(std::string name, int size) // Creates class with historical data of the stock, with a fixed size
{
  if (size<1) throw Exception("Error in size", "The size of historical data must be at least equal to 1");
  mName=name;
  mData=new Quote[size];
  mSize = size;
  mFilled=0;

  // We fill in the array mData with objects of class Quote.
  for (int i=0; i<mSize; i++)
  {
    mData[i] = Quote(name, 0.0, "0000/00/00"); // Quotes with date 0000/00/00 are considered as Null
  }

}


std::string Stock::getName(void) {
  return mName;
}

int Stock::getFilled(void) {
  /*

  Returns the number of spaces in the class Stock.

  */

  return mFilled;
}

std::ostream& operator<<(std::ostream& output, Stock& q) {
  /*

  Allows to output an object of class Stock.

  */

  std::string name = q.getName();
  output<<"Stock name: "<<name<<"\n";
  if (!q.mData[0].isNull()) {
    output<<"Start date: "<<q.mData[0].getDate()<<"\n";
    output<<"End date: "<<q.mData[q.mFilled-1].getDate()<<"\n";  
  }
  output<<"Length of available data: "<<q.mFilled<<"\n\n";
  
  output<<"  Date\t\t Price\n ------\t\t-------\n\n";
  for (int i=0; i<q.mSize; i++) {
    if (q.mData[i].isNull()) continue;
    output<<q.mData[i].getDate()<<"\t "<<q.mData[i].getPrice()<<"\n";
  }

  return output;
}

void Stock::popLeft(void) {
  /*

  Deletes the first quote, and moves the rest of the quotes to the left.

  */

  if (mSize==1) {
    mData[0]=Quote(mName, 0.0, "0000/00/00");
    mFilled=0;
    return;
  }
  if (mFilled==0) return;
  for (int i=1; i<mFilled; i++) {
    mData[i-1]=mData[i];
  }
  mData[mFilled-1]=Quote(mName, 0.0, "0000/00/00");
  mFilled--;
}

void Stock::addData(Quote q) {
  /*

  Adds new data to the stock's historical prices.

  */

  // We add the quote q to the historical data.- If historical data is full, throw exception
  if (mFilled==mSize) throw Exception("Data size limit reached", "There is no space to store more historical data");

  // If Quote name doesn't match Stock name, throw exception
  if (q.getName()!=mName) throw Exception("Invalid name", "Quote's name does not match stock's name");
  


  // Sort quotes. Notice that the elements from 0 to mFilled-1 are already sorted.
  if (mFilled==0) {
    mData[0]=q;
    mFilled++;
    return;
  }


  for (int i=0; i<mFilled; i++) {
  {  
  if (mData[i].getDate()>q.getDate()) {
    mData[mFilled]=mData[i];
    mData[i]=q;
    break;
  }
  if (i==mFilled-1) {

    mData[mFilled]=q;
  }
  }
  }



  mFilled++; 
}

double Stock::mean(void) {
  /*

  Calculates the mean of the stock prices.

  */

  if (mFilled==0) return 0.0;
  double m=0.0;
  for (int i=0; i<mFilled; i++) {
    m+=mData[i].getPrice();
  }

  return m/mFilled;
}

Stock Stock::sample(int start, int end) {
  /*

  Returns a sample of the historical data. That is,
  it returns an object of class Stock with data from
  the start-th to the end-th positions, in the historical
  data of our stock.

  */

  if (start>end || start<0 || end>=mFilled) {
    std::cout<<start<<" "<<end<<"\n";
    throw Exception("Error in the indices", "There has been an error with the provided indices");
  } 
  Stock S(mName, end-start+1);
  for (int i=start; i<=end; i++) {
    S.addData(mData[i]);
  }
  return S;
}

Quote Stock::getData(int i) {
  /*

  Returns the quote in position i.

  */
  
  if (i<0 || i>=mSize)  throw Exception("Out of bound", "The index is out of bound");
  return mData[i];
}
