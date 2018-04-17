#Simon Owens
#CS 215 Don Roberts
#MP 4
#Makefile

project3: sweeper.o sweepergrid.o sweepercell.o
	clang++ -Wall -o sweeper sweeper.o sweepergrid.o sweepercell.o

sweeper.o: sweeper.cpp sweepergrid.h
	clang++ -Wall -c sweeper.cpp

sweepergrid.o: sweepergrid.h sweepergrid.cpp
	clang++ -Wall -c sweepergrid.cpp

sweepercell.o: sweepercell.h sweepercell.cpp
	clang++ -Wall -c sweepercell.cpp

clean:
	rm *.o
	rm sweeper
	rm *.tar
