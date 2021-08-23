
Hw1: main.o auxArrayFunctions.o sorting.o
	g++ main.o auxArrayFunctions.o sorting.o -o Hw1
	
main.o: main.cpp
	g++ -c main.cpp

auxArrayFunctions.o: auxArrayFunctions.cpp
	g++ -c auxArrayFunctions.cpp

sorting.o: sorting.cpp
	g++ -c sorting.cpp

clean:
	rm *.o Hw1