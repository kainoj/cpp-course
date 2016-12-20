Flags = -Wreturn-type -Wall -std=c++11
CPP   = g++ 


nr08 : Makefile main.o nr08.o
	$(CPP) $(Flags) -o nr08  nr08.o main.o 



nr08.o : Makefile     nr08.cpp   nr08.h
	$(CPP) -c $(Flags) nr08.cpp -o  nr08.o


main.o : Makefile main.cpp nr08.h
	$(CPP) -c $(Flags) main.cpp -o main.o