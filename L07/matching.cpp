
#include "matching.h"
#include <utility>


std::list< matching > match( tree from, tree into ) //returns singleton
{
    

    matching m;

    std::vector< std::pair< tree, tree >> stack  = { { from, into } };

   while( stack. size( ))
   {
#if 0
std::cout << "matching " << from << " into " << into << "\n";
      for( auto t : stack )
         std::cout << "[  " << t. first << " = " << t. second << "  ]    ";
      std::cout << "\n----\n";

#endif

      std::pair< tree, tree > current = stack. back( );
      stack. pop_back( );

      const std::string f1 = current.first.functor();
      const std::string f2 = current.second.functor();

      tree t = current.second;

      size_t s1 = current.first.nrsubtrees();
      size_t s2 = current.second.nrsubtrees();

      if( matching::isvariable(f1)  && !m.isdefined(f1) ) {

          m.assign(f1, t);
         // std::cout << "nowe podstawienie: \nf1= " << f1 << "f2= " << f2 << "\n";
      }
      else if( matching::isvariable(f1)  && m.isdefined(f1) ) {
        if( !( m(f1) == t)) return { };
      }
      else {
          if( s1 != s2 || f1 != f2  )
              return { };
          for( size_t i=0; i<s1; i++)      
            stack.push_back( std::make_pair(current.first[i], current.second[i]) );
      }
      }


 
 // std::cout << "matching found: " << m << "\n";

   // Success: return { m };
   // Failure: return { } ;
   return { m };
}
 


std::ostream& operator << ( std::ostream& out, const matching& m )
{
   //out << "matching: ";
   for( const auto& p : m.subst )  
   {
      out << p. first << " := " << p. second;
   }
   return out;
}


/*


if( m.isvariable( f1 )  ) {
         if( m.isdefined( f1 ) ) {
            if(  !( (m)(f1) == current.first )  ) {
               //std::cout << "WYCHODZE, BO FUNKTOR JUZ JEST";
               return {};
            }
         }
         else m.assign(f1, current.second);










      if( s1 != s2 ) {
         return { };
      }
      if( f1 != f2  ) {
         return { };
      }

      for( size_t i=0; i<s1; i++)      // 2
            stack.push_back( std::make_pair(current.first[i], current.second[i]) );
            
       
      if( m.isvariable( f1 )  &&  !m.isdefined( f1 ) ) {
            subst.push_back( {f1, p} )
      }


      if( m.isdefined(f1)   )




         */