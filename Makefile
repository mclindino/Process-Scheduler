main: main.o Processo.o
	g++ main.o Processo.o -o main

main.o: main.cpp
	g++ -c main.cpp

Units.o: Processo.cpp Processo.h
	g++ -c Processo.cpp

clean:
	rm *.o main