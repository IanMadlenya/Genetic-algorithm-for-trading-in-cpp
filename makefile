all: main
#For debugging
OPT=-g
#For optimistaion
#OPT=-O
#All objects (except main) come from cpp and hpp 
%.o:	%.cpp %.hpp
	g++ ${OPT} -c -o $@ $<
#use_vectors relies on objects which rely on headers

main:	main.cpp global.o Population.o Organism.o Stock.o Quote.o Exception.o
		g++ ${OPT} -o main main.cpp global.o Population.o Organism.o Stock.o Quote.o Exception.o
clean:
	rm -f *.o *~ main