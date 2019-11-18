main: main.o Units.o
	g++ main.o Units.o -o main

main.o: main.cpp
	g++ -c main.cpp

Units.o: Units.cpp Units.h
	g++ -c Units.cpp

clean:
	rm *.o main