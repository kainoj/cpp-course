#include "tree.h"
#include <utility> 

tree::tree( const tree& t )					// Copy Constructor
            : pntr( t.pntr ) {
            t.pntr -> refcnt++;
}

tree::~tree() {								// Destructor
	if(--pntr->refcnt==0)
		delete pntr;
}

void tree::operator = ( tree&& t ) {		// R-value assignment
	std::swap(pntr, t.pntr);
}

void tree::operator = ( const tree& t ) {	// Assignment const
	*this = std::move(tree(t));
}

void tree::operator = ( std::string s) {
	pntr -> f = s;
	pntr -> refcnt = 1;
}

const std::string& tree::functor( ) const {// Task 3
	return pntr->f;
}

const tree& tree::operator[] (size_t i) const {
	return pntr-> subtrees[i];
}

size_t tree::nrsubtrees() const {
	return pntr -> subtrees.size();
}
														// Task 4
std::ostream& operator << ( std::ostream &stream, const tree &t ) {
	stream << t.functor()  << " ";
	for(size_t i=0; i<t.nrsubtrees(); i++)
		stream << t[i] << " ";
	return stream;
}

void tree::ensure_not_shared( ) {			// Task 5
	if( pntr -> refcnt == 1 )
		return;
	pntr -> refcnt--;
	pntr = new trnode( pntr->f, pntr->subtrees, 1);
}

std::string& tree::functor( ) {				
	ensure_not_shared();
	return pntr->f;
}

tree& tree::operator [ ] ( size_t i ) {
   ensure_not_shared();
	pntr -> subtrees[i].ensure_not_shared();
	return pntr -> subtrees[i];
}

													// Task 6
tree subst(const tree& t, const std::string& var, const tree& val) {
	
	if( t.nrsubtrees() == 0 ) {
		if( t.functor() == var) 
			return val;
		else
			return t;
	}

	std::vector <tree> sbtrees;
	for(size_t i=0; i<t.nrsubtrees(); i++)
		sbtrees.push_back( std::move(subst( t[i], var, val)) );
		
	return tree(t.functor(), std::move(sbtrees)  );
}

													
size_t tree::getaddress( ) const {				// Task 7
	return reinterpret_cast< size_t > ( pntr );
}

void tree::replacesubtree( size_t i, const tree& t ) const{
	pntr -> subtrees[i] = std::move(t);
}

void tree::replacefunctor( const std::string& f ) const{
	pntr -> f = f;
}


tree subst2(const tree& t, const std::string& var, const tree& val) {	
	if( t.nrsubtrees() == 0 ) {
		if( t.functor() == var) {
			return val;		
		}
		return t;
	}

	for(size_t i=0; i<t.nrsubtrees(); i++)
		t.replacesubtree(i , subst2(t[i], var, val) );	
	return t;
}



//##################################
//          LIST 07 TASK 01
//##################################

bool operator == (tree t1, tree t2) {
	std::vector<std::pair<tree, tree> > s;
	std::pair<tree, tree> t(t1,t2);
	s.push_back(t);
	while ( !s.empty() ) {
		t1 = s[s.size()-1].first;
		t2 = s[s.size()-1].second;
		s.pop_back();
		//std::cout << "sprawdzam: " << t1 << "\t\t" << t2 << "\n";

		if( t1.nrsubtrees() != t2.nrsubtrees() )
			return false;
		if( t1.functor() != t2. functor() )
			return false;

		for( size_t i=0; i< t1.nrsubtrees(); i++ )
			s.push_back(std::make_pair(t1[i], t2[i]));

	}

	return true;	
}


bool operator != (tree t1, tree t2) {
	return !(t1 == t2);


}


