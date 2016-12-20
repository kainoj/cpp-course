Flags =  -Wreturn-type -pedantic -pedantic-errors -Wundef -std=c++11 -O 
CPP = g++

main : Makefile  main.o surface.o
	$(CPP) $(Flags) main.o surface.o -o main


main.o: Makefile main.cpp
	$(CPP) -c $(Flags) main.cpp -o main.o

surface.o: Makefile surface.h surface.cpp
	$(CPP) -c $(Flags) surface.cpp -o surface.o


