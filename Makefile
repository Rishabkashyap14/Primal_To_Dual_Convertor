all: PDC.o 
	g++ -g -Wall PDC.o -o a.out

PDC.o:
	g++ -g -c PDC.cpp

clean:
	rm -f *.o *.out
