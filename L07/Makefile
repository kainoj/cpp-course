
# Automatically generated Makefile
# Makefile-generator programmed by Hans de Nivelle, 2002


Flags = -Wall -Wextra -pedantic -std=c++11 -Wno-unused-parameter -g -std=c++11
CPP = g++


main : Makefile  rewrite.o main.o tree.o matching.o 
	$(CPP) $(Flags) -o main   main.o tree.o matching.o rewrite.o

main.o : Makefile   main.cpp  rewrite_system.cpp rewrite_system.h tree.h matching.h 
	$(CPP) -c $(Flags) main.cpp -o  main.o


tree.o : Makefile   tree.cpp   tree.h 
	$(CPP) -c $(Flags) tree.cpp -o  tree.o


matching.o : Makefile   matching.cpp   matching.h tree.h 
	$(CPP) -c $(Flags) matching.cpp -o  matching.o

rewrite.o: Makefile main.cpp  rewrite_system.cpp rewrite_system.h
	$(CPP) -c $(Flags) rewrite_system.cpp -o rewrite.o

