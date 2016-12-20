
#include "varchain.h"
#include "polynomial.h"
#include "bigint.h"
#include "rational.h"

#define WLASNETESTY   1


template< typename N >
polynomial< N > exptaylor( unsigned int n )
{
   varchain v;

   N fact = 1;

   polynomial< N > result;
   for( unsigned int i = 0; i < n; ++ i )
   {
      result[v] += fact;
      v = v * powvar( "x" );
      fact = fact / (i+1);
   }

   return result;
}

int main( int argc, char* argv [] )
{

#if WLASNETESTY 

   varchain v1 = { {std::string("z"), 3},
                   {std::string("y"), 2},
                   {std::string("y"), -2},
                   {std::string("x")}
                  };
    std::cout << v1 << " \n";

    // test 1
    polynomial <int> p, p2;

    p[  varchain( { {"x",3}, {"y", 5} } )  ] = 2;
    p[ varchain( {{"x"}}) ] = 1;

    p2[ varchain( {{ "x" }} ) ] = 1;
 
   // std::cout << "p:\t" << p << "\np2:\t" << p2 <<  "\n";
   // std::cout << "p * p2 = \t" << p *p2 << "\n\n----\n"; 
    






    // test 2
    polynomial <int> p3 ;
    p3[ {} ] = 1;
    p3[ {{"x",3 }} ] = 1;
    polynomial <int> p3res = 1;

    //varchain vvv =  {{"x", 3}};
    //std::cout<< "vvv= " << vvv << " \n";




    std:: cout << "(p3 = " << p3 << "\n\n";
    std:: cout << "(x^3+1)^3 = " << p3*p3*p3 << "\n\n";
    

  // std:: cout << "Przed:\np3:\t" << p3 << "\np3res:\t" << p3res << "\n\n";
    for(int i =0; i<10; i++)
        p3res = p3res* p3;
  // std:: cout << "Po:\np3:\t" << p3 << "\np3res:\t" << p3res << "\n\n";












// testy wykładowcy



#else 

    polynomial< rational > pol;

   int N = 50;

   pol[ { } ] = 1;
   pol[ { "x" } ] = rational( 1, N ); 

   
   polynomial< rational > res = 1;
 
   for( int i = 0; i < N; ++ i )
      res = res * pol;

   std::cout << "rsult = " << res << "\n\n";

   std::cout << " taylor expansion = " << exptaylor<rational>(20) << "\n";

   std::cout << "difference = " ;  
   std::cout << res - exptaylor<rational> ( 40 ) << "\n";


#endif
  

   return 0;
}




















/*
    polynomial< rational > pol;

    int N = 50;

    pol[ { } ] = 1;  
    pol[ { "x" } ] = rational( 1, N ); 


    #if 0
    polynomial< rational > res = 1;

    for( int i = 0; i < N; ++ i )
        res = res * pol;

    std::cout << "rsult = " << res << "\n";

    std::cout << " taylor expansion = " << exptaylor<rational>(20) << "\n";

    std::cout << "difference = " ;  
    std::cout << res - exptaylor<rational> ( 40 ) << "\n";
    #endif



 */
