#include <iostream>
#include <string> 
#include <vector>
#include <utility>

#include "nr08.h"

int main() {

	std::vector<std::string> text = { "AA", "aA", "Aa", "this", "THIS", "o" };
	std::map< std::string, unsigned int, case_insensitive> cntr = frequencytable(text);

	std:: cout << cntr;

	case_insensitive c;
	std::cout << c( "aa", "aaaa" ) << c( "a","b" ) << c( "A", "b" ) << "\n";




	case_insensitive_hash h;
	std::cout << "hasze:\n" << h( "xxx" ) << " " << h( "XXX" ) << "\n";
	std::cout << h( "Abc" ) << " " << h( "abC" ) << "\n";
	case_insensitive_equality e;
    std::cout << e( "xxx", "XXX" ) << "\n";

    std::vector<std::string> text2 =  { "aa", "AA", "bb", "BB" } ;
    	std::unordered_map< std::string, unsigned int,case_insensitive_hash,case_insensitive_equality >	hsz_fqtb = hashed_frequencytable(text2 ) ;

    std::cout  << hsz_fqtb << "\n";

	return 0;
}