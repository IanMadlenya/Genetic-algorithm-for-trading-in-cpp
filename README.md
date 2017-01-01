# Genetic algorithms for trading

This code tries to show how to use genetic algorithms to create a simple trading strategy. It is intended as a proof of concept, rather than trying to provide a ready-to-use strategy. The historical data used is the following: [SP500.dat](https://github.com/imanolperez/Genetic-algorithm-for-trading/blob/master/SP500.dat). It is the closing prices of S&P 500 from 2006/12/18 to 2016/06/15, so almost 10 years.

## Genetic algorithms

Genetic algorithms simulate the evolution of a species. It starts with a random population of organisms, which represent algorithms. Then, after many generations the strongest algorithms survive. In general, genetic algorithms possess the following structure:

1. Generate a random population of organisms
2. Select the top performers, acording to a certain criteria (a fitness function is usually required here).
3. Perform a crossover of the outperformers to produce new children.
4. Apply a random mutation to some of the children. This way, we end up with a new generation of organisms.
5. Repeat step 2, until the desired number of generations is achieved.

## The code

The organisms of our population will be trading strategies that have two parameters: two Moving Averages (MA1 and MA2). The strategy is the following: for any trading day, calculate the two moving averages MA1 and MA2. If the first moving average is larger than the second one, buy the S&P 500. Otherwise, short the S&P 500.

The code generates an initial population of organisms, asigning random values to MA1 and MA2 in each organism. Then, it applyes the fitness function to select the top 20% performers.

The fitness function picks a random time interval from the available data, and calculates the returns of the trading strategy. The objective of picking a random time interval instead of the whole available data is to obtain organisms that fit well to any given time period, for the available data.

After selecting the top 20% of the organisms, the code performs a crossover. It selects two random organisms, which will be the parents, and they produce a child. The child will inherit MA1 from a parent, and MA2 from the other parent. This process is repeated, selecting random parents each time, until the desired population is reached.

Then, the mutation process takes place. Some random children will be mutated. The mutation consists of selecting MA1 or MA2 and changing it for a random value. This is done with a certain probability, the probability of creating a mutation.

This process is repeated until we reach the number of generations we wanted.

The code possesses several classes: the class Quote stores data of the stock, in a certain day. The class Stock saves all available historical data, where each particular day is stored as an object of class Quote. Then, there is the class Organism, which is a particular organism (in our case, trading strategy). Finally, we have the class Population, which stores all organisms that form our populatin.

## The results

The parameters used in the simulation are the following:

- **Population size:** 100
- **Maximum value of the Moving Average allowed**: 50
- **Number of generations**: 1000
- **Time interval used in the fitness function**: 60 days
- **Probability to have a mutation**: 0.3 (that is, a probability of 30%).

The 60% of the available data was used to run the genetic algorithm to select the appropriate trading strategy, and the 40% of the available data was used to test the strategy. After running the simulation, the trading strategy that was obtained was (39, 24). That is, the first moving average is 39, and the second one 24.

The return of the algorithm in the training data (from 2007/03/02 to 2012/08/24) was 22%. In the same period, the return of the S&P 500 was -1%.

When running the trading strategy with out-of-sample data, the return of the strategy was 64%, while the S&P 500 only returned 47% in the same period. The following plot shows the evolution of the earnings of the strategy, when started with an initial capital of 1000$:

![plot](https://raw.githubusercontent.com/imanolperez/Genetic-algorithm-for-trading/master/results/returns_out_of_sample.jpg)

The beta of the strategy for the out-of-sample data is 0.01, so it has the advantage of being market-neutral.


## Conclusions

The objective of this experiment is to see how one could use genetic algorithms to find trading strategies. A lot of improvement can be done, of course. For example, more complex strategies can be used, in order to obtain a richer final algorithm. Moreover, the fitness function could be improved as well, to include features you want the algorithm to have.
