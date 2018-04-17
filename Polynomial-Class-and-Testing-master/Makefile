#Makefile
#Simon Owens
#CS 215 Don Roberts
#MP
#Makefile

project5: project5.o polynomial.o term.o
	clang++ -Wall -o project5 project5.o polynomial.o term.o

project5.o: project5.cpp polynomial.h
	clang++ -Wall -c project5.cpp

polynomial.o: polynomial.h polynomial.cpp
	clang++ -Wall -c polynomial.cpp

term.o:	term.h term.cpp
	clang++ -Wall -c term.cpp
