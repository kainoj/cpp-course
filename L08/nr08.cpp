#include <map>

#include "nr08.h"

std::map< std::string, unsigned int, case_insensitive> frequencytable( const std::vector< std::string > & text ) {
	std::map <std::string, unsigned int, case_insensitive> counter;

	for( size_t i=0; i< text.size(); i++)
		counter[text[i]]++;

	return counter;
}

std::ostream& operator << ( std::ostream& stream, const std::map< std::string, unsigned int, case_insensitive > & freq ) {
	
	for(auto it : freq)
		stream << it.first << "\t\t" << it.second <<"\n";
	return stream;
}

bool case_insensitive::operator( ) ( const std::string& s1, const std::string& s2 ) const {
	//std::cout << "Comparing: " << s1 << " " << s2 << "\n";
	//if( s1.length() < s2.length() ) return true;

	size_t minlen = std::min(s1.length(), s2.length()), i=0;
	while(i <minlen && ((s1[i]>='a' ? s1[i]+'A'-'a' : s1[i])   ==   (s2[i]>='a' ? s2[i]+'A'-'a' : s2[i])   )) { 
		//std::cout << (s1[i]>='a' ? s1[i]+'A'-'a' : s1[i])   <<  " " <<(s2[i]>='a' ? s2[i]+'A'-'a' : s2[i]) <<"\n";
		i++;
	}
	if( s1.length()== i) return true;
	if( s2.length()==i) return false;
	return    (s1[i]>='a' ? s1[i]+'A'-'a' : s1[i])   <  (s2[i]>='a' ? s2[i]+'A'-'a' : s2[i])   	;
}


/////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
///////////////////////// HASZE ///////////////////////////////////////////
////////////////////////////////////////////////////////////////////////// 
/////////////////////////////////////////////////////////////////////////

size_t case_insensitive_hash::operator ( ) ( const std::string& s ) const {
	
/*
	http://www.cse.yorku.ca/~oz/hash.html
*/

	size_t hasz = 5381;
	for (size_t i=0; i<s.length(); i++) {
		hasz = ((hasz<<5)+hasz) + (s[i]>='a' ? s[i]+'A'-'a' : s[i]);
	}
	return hasz;
}


bool case_insensitive_equality::operator ( ) ( const std::string& s1, const std::string& s2 ) const {
	if(s1.length()!=s1.length())
		return true;
	for( size_t i=0; i< s1.length(); i++) {
		if( (s1[i]>='a' ? s1[i]+'A'-'a' : s1[i]) != (s2[i]>='a' ? s2[i]+'A'-'a' : s2[i]) )
			return false;
	}	
	return true;
}




std::ostream& operator << ( std::ostream& stream, const std::unordered_map< std::string, unsigned int,case_insensitive_hash,case_insensitive_equality > & freq ) {
	for(auto it : freq)
		stream << it.first << "\t\t" << it.second <<"\n";
	return stream;
}


std::unordered_map< std::string, unsigned int, case_insensitive_hash,case_insensitive_equality> hashed_frequencytable( std::vector<std::string> &text){
	std::unordered_map< std::string, unsigned int, case_insensitive_hash,case_insensitive_equality > counter;

	for( size_t i=0; i< text.size(); i++)
		counter[text[i]]++;
	return counter;

}











/*

ize_t minlen = std::min(s1.length(), s2.length());
	bool grd = true;
	for(size_t i=0; i< minlen; i++)
		if( (s1[i]>='a' ? s1[i]+'A'-'a' : s1[i])   !=   (s2[i]>='a' ? s2[i]+'A'-'a' : s2[i])   )
			return false;

		return true;
	//return ! ( s1.length() < s2.length());
}

*/