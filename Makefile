all: PDC.o 
	g++ -g -Wall PDC.o -o conversion

PDC.o:
	g++ -g -c PDC.cpp

clean:
	rm -f *.o *.out
