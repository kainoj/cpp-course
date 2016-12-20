
#ifndef TREE_INCLUDED
#define TREE_INCLUDED  1


#include <iostream>
#include <vector>
#include <string>
#include <initializer_list>


class tree;

// struct trnode should be invisible to the user of tree. This can be 
// obtained by making it a private number of tree. 
// In this exercise, we leave it like this, because it is simpler.
// In real code, trnode should be defined inside tree.


struct trnode 
{
   std::string f;
   std::vector< tree > subtrees;
   
   size_t refcnt;
      // The reference counter: Counts how often this trnode is referred to.

   trnode( const std::string& f, const std::vector< tree > & subtrees, 
           size_t refcnt )
      : f{f},
        subtrees{ subtrees },
        refcnt{ refcnt }
   { }

   trnode( const std::string& f, std::vector< tree > && subtrees,
           size_t refcnt )
      : f{f},
        subtrees{ std::move( subtrees )}, 
        refcnt{ refcnt }
   { }

};


class tree
{
   trnode* pntr;

	public: 
		//tree() = default;
		tree( const std::string& f ) 
		   : pntr( new trnode( f, { }, 1 ))
		{ }
		tree( const char * f)
		: pntr( new trnode( f, { }, 1 ))
		{ }

		tree( const std::string& f, const std::vector< tree > & subtrees )   
		   : pntr( new trnode( f, subtrees, 1 ))
		{ } 
	 
		tree( const std::string& f, std::vector< tree > && subtrees )
		   : pntr( new trnode( f, std::move( subtrees ), 1 ))
		{ }

		/*tree( const std::vector<std::string> s)
			
		{ 
			std::vecotr <tree> vect;
			for( size_t i=0; i< s.size(); i++)
				vect.push_back( tree ( s[i]) );
			pntr = new trnode( std::string("qq"), s, 1);
		}
*/


		// ################## TASK 1 ###########################
		tree( const tree& t ) ;
		   // There is no need to write tree( tree&& t ),
		   // because we cannot improve. 

		void operator = ( tree&& t ); 
		void operator = ( const tree& t ); 
		void operator = ( std::string );

		const std::string& functor( ) const;
		std::string& functor( );

		const tree& operator [ ] ( size_t i ) const;
		tree& operator [ ] ( size_t i );
		size_t nrsubtrees( ) const; 

		~tree( );

		int getRefcnt() const { return pntr -> refcnt; } // For debugging.
		size_t getaddress( ) const;
		void replacesubtree( size_t i, const tree& t ) const;
		void replacefunctor( const std::string& f ) const;
		
	private: 
	//public: 
		// Delete public, when the thing is tested:

		void ensure_not_shared( ); 

	};

std::ostream& operator << ( std::ostream& stream, const tree& t );
   // Doesn't need to be friend, because it uses only functor( ),
   // nrsubtrees( ) and [ ].
tree subst(const tree& t, const std::string& var, const tree& val);
tree subst2(const tree& t, const std::string& var, const tree& val);


//#########################################
//             LIST 07 TASK 1
//#########################################

bool operator == (tree t1, tree t2);
bool operator != (tree t1, tree t2);	


#endif

