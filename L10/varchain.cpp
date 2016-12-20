
#include "varchain.h"
#include <algorithm>


std::ostream& operator << ( std::ostream& out, const powvar & p )
{
   if( p.n == 0 )
   {
      out << "1X"; // Should not happen, but we still have to print something.
      return out;
   }

   out << p.v;
   if( p.n == 1 )
      return out;

   if( p.n > 0 )
      out << "^" << p.n;
   else
      out << "^{" << p.n << "}";
   return out;
}


std::ostream& operator << ( std::ostream& out, const varchain& c )
{
   if( c. isunit( ))
   {
      out << "1";
      return out;
   }

   for( auto p = c. repr. begin( ); p != c. repr. end( ); ++ p )
   {
      if( p != c. repr. begin( ))
         out << ".";
      out << *p;
   }

   return out;
}


int varchain::power( ) const 
{
   int p = 0;
   for( auto pv : repr )
      p += pv. n;
   return p;
}


bool cmpPowvars(powvar p1, powvar p2) {
    return (p1.v < p2.v);
}

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////




void varchain::normalize() {
        if(repr.size() == 0) return;

        // 1. Sort the representation by variable. 
        std::sort( repr.begin(), repr.end(), cmpPowvars );

        // 2. Merge powvars with identical variable.
        std::vector<powvar> new_repr;

        std::string s = repr[0].v;
        int    n = 0; //repr[0].n;

        for (auto  p : repr) {
            if( p.v != s) {
                if( n != 0 )
                    // 3. Remove powvars with n == 0.
                    new_repr.push_back( {s, n} );
                n = 0;
                s = p.v;
            } 
            n += p.n;
        }
        if( n != 0 )
            new_repr.push_back( {s, n} );
        repr = std::move(new_repr); ///////////////////
}

int varchain::compare(const varchain& c1, const varchain& c2 ) {
    size_t m = std::min(c1.size(), c2.size());

    for( size_t i=0; i < m ; i++) {
        if(c1[i].v < c2[i].v) return -1;
        if(c1[i].v > c2[i].v) return  1;
        if(c1[i].n < c2[i].n) return -1;
        if(c1[i].n > c2[i].n) return  1;
    }

    if(c1.size() > m ) return  1;
    if(c2.size() > m ) return -1;

    //  0     c1 = c2
    // -1     c1 < c2
    //  1     c1 > c2

    return 0;
}


varchain operator * ( varchain c1, const varchain& c2 ) {
    std::vector<powvar> c1c2 = c1.repr;
    for(auto c : c2.repr) 
      c1c2.push_back(c);
    return varchain(c1c2);
}


