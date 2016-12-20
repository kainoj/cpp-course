
#include "listtest.h"

#include <random>
#include <chrono>
#include <algorithm>

#include <iostream>

//								    TASK 2b
std::ostream& operator << ( std::ostream& out , const std::list<std::string > & mylist) {
	out << "( ";
	for( auto i:  mylist)
		out << i << " ";
	out << ")";
	return out;
}


//									Task 5
std::list<std::string> listtest::vector2list(std::vector<std::string> &v)  {
	std::list<std::string> mylist;	
	for( auto i: v)
		mylist.push_front(i);
	return mylist;
}


void listtest::sort_move( std::list< std::string > & v ) {
	// below: `auto` instead of ` std::list<std::string>::iterator `
	for(auto j=v.begin(); j!=v.end(); ++j) 
		for(auto i=v.begin(); i!=j; ++i) 
			if( *i > *j )
				std::swap( *i, *j);
}

void listtest::sort_assign( std::list< std::string > & v ) {

	for(auto j=v.begin(); j!=v.end(); ++j) 
		for(auto i=v.begin(); i!=j; ++i) 
			if( *i > *j ) {
				std::string s = *i;
				*i = *j;
				*j=s;
			}
}


#if 0
void listtest::vectortest::sort_std( std::vector< std::string > & v) {
	

}
#endif











