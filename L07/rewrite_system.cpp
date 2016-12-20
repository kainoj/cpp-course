
#include "rewrite_system.h"
#include "matching.h" 


std::ostream& 
operator << ( std::ostream& out, const rewrite_system::rule& r )
{
   out << r. left << " ==> " << r. right;
   return out;
}


std::ostream& operator << ( std::ostream& out, 
                            const rewrite_system& rewr )
{
   out << "rewrite system:\n";
   for( const auto& rule: rewr. rules ) 
      out << "   " << rule << "\n";
   return out; 
}


tree rewrite_system::one_pass( tree t ) const 
{
  // std::cout << "\tone pass : " << t <<"\n";
   for( const auto& r: rules )
   {
     // std::cout << "\t\t" << r << " -> " << t << "\n";
      auto m = match( r. left, t );
      if( m. size( ))
      {
        // std::cout << "matched: " << m. front( ) << "\n";
         t = m. front( )( r. right );
        // std::cout << "   result = " << t << "\n";
      }
   }

   for( size_t i = 0; i != t. nrsubtrees( ); ++ i )
      t. replacesubtree( i, one_pass( t[i] ));

   return t;
}
    

tree rewrite_system::normalize( tree t1 ) const 
{
   tree t2 = one_pass( t1 );

   while( t1 != t2 )
   {
      t1 = t2;
      t2 = one_pass( t2 );
   }

   return t1;
}


void test( )
{
   std::cout << "TEST\n\n";
 
   tree p1 = { std::string("+"), { std::string("_X"), std::string("0") }};

   tree p2 = "_X";
 #if 1
   tree q1 = { std::string("+"), { std::string("_X"), { std::string("S"), { std::string("_Y") }}}};
   tree q2 = tree( std::string("S"), { tree( std::string("+"), { std::string("_X"), std::string("_Y") } ) } );

   rewrite_system rewr = 
   std::vector< rewrite_system::rule > 
   {
      { p1, p2 },
      { q1, q2 },
   
      { tree( std::string("*"), { tree( std::string("_X") ), tree( std::string("0") ) } ),
        tree( "0" ) },

      { tree( std::string("*"), { tree( std::string("_X") ), tree(std::string( "S"), { tree( std::string("_Y") ) } ) } ),
        tree( std::string("+"), { tree( std::string("*") , { tree( std::string("_X") ), tree( std::string("_Y") ) } ), 
                     tree( std::string("_X") ) } ) },
      { tree( std::string("E"), { tree( std::string("_X") ), tree( std::string("_X") ) } ), tree( std::string("T") ) }
   };

   std::cout << "aasdasd\n" << rewr << "\n";

   std::vector< tree > nat;
   nat. push_back( tree( std::string("0") ));

   // Generate (almost) all natural numbers:

   for( size_t i = 1; i < 10; ++ i )
   {
      tree next = tree( std::string("S"), { nat. back( ) } );
      nat. push_back( next );
   }
  

   tree t1 = tree( std::string("*"), { tree( std::string("*"), { nat[2], nat[3] } ), nat[2] } );
   tree t2 = tree( std::string("*"), { nat[2], tree( std::string("*"), { nat[2], nat[3] } ) } );

   std::cout << rewr. normalize( tree( std::string("E")  , { t1, t2 } )) << "\n";
      // Should be 't'.     
   std::cout << "\n\nend of cout\n";
   #endif
}

 

