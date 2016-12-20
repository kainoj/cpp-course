#ifndef NR08_INCLUDED
#define NR08_INCLUDED   1

#include <list> 
#include <string> 
#include <iostream>
#include <map>
#include <vector>
#include <unordered_map>

struct case_insensitive {
	bool operator( ) ( const std::string& s1, const std::string& s2 ) const;
	// Return true if s1 < s2, ignoring case of the letters.
};


std::map <std::string, unsigned int, case_insensitive> frequencytable(const std::vector< std::string > & text );
std::ostream& operator << ( std::ostream& stream, const std::map< std::string, unsigned int , case_insensitive> & freq );


struct case_insensitive_hash {
	size_t operator ( ) ( const std::string& s ) const;
};


struct case_insensitive_equality {
	bool operator ( ) ( const std::string& s1, const std::string& s2 ) const;
};





std::unordered_map< std::string, unsigned int,case_insensitive_hash,case_insensitive_equality > hashed_frequencytable( std::vector<std::string> &text);


std::ostream& operator << ( std::ostream& stream, const std::unordered_map< std::string, unsigned int,case_insensitive_hash,case_insensitive_equality >	&);

#endif 