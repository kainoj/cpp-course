#include "fifteen.h"

// TASK 1
fifteen::fifteen() {
	size_t val = 1, i, j;
	for(i=0; i<dimension; i++)
		for(j=0; j<dimension; j++)
			table[i][j] = val++;
	table[--i][--j] = 0;
	open_i = i;
	open_j = j;
}

fifteen::fifteen( std::initializer_list< std::initializer_list< size_t >> init ) {
	size_t n=0, m=0;
	for( auto i: init) {
		for( auto j: i)  {
			if(j==0) {
				open_i=n;
				open_j=m;
			}
			table[n][m++] = j;
		}
		n++;
		m=0;
	}
}

std::ostream& operator << ( std::ostream& stream, const fifteen& f ) {

	for(size_t i=0; i< f.dimension; i++) {
		for(size_t j=0; j< f.dimension; j++)
			stream << std::setw(3) << f.table[i][j] << " ";
		stream << "\n";
	}
	return stream;
}


// TASK 2
fifteen::position fifteen::solvedposition( size_t val ) {
	if ( val == 0 ) return {dimension-1 , dimension-1};
	return { (val-1)/dimension, (val-1)%dimension};
}

size_t fifteen::hashvalue() const {
	unsigned int sum=0;
	for (int i=0; i< dimension; i++)
		for (int j=0; j<dimension; j++)
			sum= sum*100+ table[i][j];
	//      ^ works only for small dimensions
	return std::hash<unsigned int>()(sum);
}


bool fifteen::equals( const fifteen& other ) const {
	for(size_t i=0; i<dimension; i++) 
	 	for(size_t j=0; j<dimension; j++)
			if(table[i][j] != other.table[i][j]) 
				return false;
	return true;
}


void fifteen::makemove(move m) {
	
	size_t i = open_i, j = open_j;

	switch( m ) {
		case move::up:
			if( i == 0) throw illegalmove(m);
			std::swap(table[i][j], table[i-1][j]);
			open_i--;
			break;
		case move::down:
			if( i == dimension-1 ) throw illegalmove(m);
			std::swap(table[i][j], table[i+1][j]);
			open_i++;
			break;
		case move::left:
			if( j==0 ) throw illegalmove(m);
			std::swap(table[i][j], table[i][j-1] );
			open_j--;
			break;
		case move::right:
			if( j==dimension-1 ) throw illegalmove(m);
			std::swap(table[i][j], table[i][j+1] );
			open_j++;
			break;
	};
}


bool fifteen::issolved( ) const {
	fifteen f;
	return (*this).equals(f);
}

size_t fifteen::distance( ) const {
	size_t d =0;
	for(size_t i=0; i<dimension; i++)
		for(size_t j=0; j<dimension; j++)
			d += distance( solvedposition(table[i][j]), {i,j} );
	return d;
}
