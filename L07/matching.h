

#ifndef MATCHING_INCLUDED
#define MATCHING_INCLUDED  1

#include <map>
#include <list>

#include "tree.h"


struct matching
{
   std::map< std::string, tree > subst;


   matching( ) { }

   matching( std::initializer_list< std::pair< std::string, tree >> init )
   { 
      for( const auto& assign : init )
         subst. insert( { assign. first, assign. second } );
   }

   bool isdefined( const std::string& s ) const
   {
       return subst. find(s) != subst. end( );
   }
         // True if variable s is in our domain. 
   
   // True if we consider the string a variable.
   // This is the case when it starts with an underscore.

   static bool isvariable( const std::string& s )
   {
      return s. size( ) >= 2 && s[0] == '_';
   }


   // Exercise : Remove the const here, try to substitute something.
   // Observe what you see..
 
   tree operator( ) ( const std::string& s ) const 
   {
      return subst.at(s); 
   }
   // ######################## TASK 2
   // ################################

   tree operator( ) ( const tree& t ) const {
      
      tree res=t;
      if( isdefined( t.functor() ) )
         res = ::subst(t, t.functor(), subst.at( t.functor() )); 
      //else 
        // res = t;

      for(size_t i = 0; i < res.nrsubtrees(); i++)
           res.replacesubtree(i, this->operator()(res[i]));
      
      return res;
   }



      // Similar to the substitution function that you made already
      // in task 5. 
      // Throws an exception if there is an unknown variable.
    
   bool assign( const std::string& s, const tree& val )
   {
      return subst. insert( { s, val } ). second;
   }

};

std::list< matching > match( tree from, tree into );
   // Try to match (from) into (into). Return a one-element list,
   // on success, and empty list on failure.

std::ostream& operator << ( std::ostream& out, const matching& m );


#endif



/*



 tree operator( ) ( const tree& t ) const {
      tree tmp = t;
      if( isvariable(tmp.functor()) ) 
            return subst.at(tmp.functor());
   
      for (size_t i; i<t.nrsubtrees(); i++)
         tmp.replacesubtree(i, this -> operator () ( t[i]) );

      return tmp;
   }






 if( isvariable(t.functor()) && t.nrsubtrees()==0) 
            return (*this)(t.functor());
      tree tmp = t;
      for (size_t i; i<t.nrsubtrees(); i++)
         tmp.replacesubtree(i, (*this)( t[i]) );

      return tmp;
   */