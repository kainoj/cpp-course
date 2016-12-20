
#include <fstream>
#include <iostream>
#include <chrono> 
#include <random>

#include "listtest.h"
#include "vectortest.h"

int main( int argc, char* argv [] )
{
   std::vector< std::string > vect;

	// Task 1
	std::ifstream input("testfile.txt", std::ifstream::in);
	vect = vectortest::readfile(input);


//   std::cout << vect << "\n";
	
	// Task 4
	size_t nr=15000, s=10;
	std::cout << "> Task 4\n\n";
	vect = vectortest::randomstrings(nr, s);


   auto t1 = std::chrono::high_resolution_clock::now( ); 						// O( n*n )
   vectortest::sort_move( vect );
   auto t2 = std::chrono::high_resolution_clock::now( );
   std::chrono::duration< double > d = ( t2 - t1 );
   std::cout << "Vector moving-assignment sort took:\t" << d. count( ) << " seconds\n";

	t1 = std::chrono::high_resolution_clock::now( ); 								// O( n*n )
   vectortest::sort_assign( vect );
   t2 = std::chrono::high_resolution_clock::now( );
   d = ( t2 - t1 );
   std::cout << "Vector usual-assignment sort took:\t" << d. count( ) << " seconds\n";

	t1 = std::chrono::high_resolution_clock::now( ); 								// O( n*log(n) )
   vectortest::sort_std( vect );
   t2 = std::chrono::high_resolution_clock::now( );
   d = ( t2 - t1 );
   std::cout << "Vector std sort took:\t\t\t" << d. count( ) << " seconds\n\n\n\n";


	// Sorting lists
	std::list<std::string> l;
	l = listtest::vector2list(vect);

	t1 = std::chrono::high_resolution_clock::now( ); 								
   listtest::sort_move( l );
   t2 = std::chrono::high_resolution_clock::now( );
   d = ( t2 - t1 );
   std::cout << "List moving assignment took:\t\t" << d. count( ) << " seconds\n";


	t1 = std::chrono::high_resolution_clock::now( ); 								
   listtest::sort_assign( l );
   t2 = std::chrono::high_resolution_clock::now( );
   d = ( t2 - t1 );
   std::cout << "List usual assignment took:\t\t" << d. count( ) << " seconds\n";
	std::cout << "No std::sort list avalibe :( \n";
	std::cout << "\n\n summary: \n\tIn general sorting that uses usual assignment is faster than using moving assignment.\n\tstd::sort is the fastest algorithm\n\tTurning on -O3 -flto almost halves the sorting time.\n\n";


   return 0;
}









