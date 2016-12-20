#include "tree.h"
#include "matching.h"
#include "rewrite_system.h"

int main( int argc, char* argv [ ] )
{
	tree t_a = "a" ;
    tree t_b( std::string( "b" )); 
    tree t_X( std::string( "_X"));
    tree t_Y( std::string( "_Y" ));
    std:: cout << (t_a == t_b) << "\n";
	
    tree t_fa = tree( std::string( "f" ), { t_a } );  
    tree t_fb = tree( std::string( "f" ), { t_b } );

    tree t1 = tree( std::string("f"), { t_X, t_Y } );
    tree t2 = tree( std::string("f"), { t_a, t_b } );
    std::cout << t1 << "\n" << t2 << "\n\n";
    

    matching mat = match(t1, t2).front();
    std::cout<< "Test: " << mat(t1) << "\n koniec.\n";
   

   test();

}













  /*



   tree t1( std::string( "a" ));
   tree t2( std::string( "b" )); 

	tree tt(std::string("A"));

	
	   tree t33 = tree( std::string( "f" ), { t1, t2 } ); 
		tree t34 = t33;
		std::cout << ">>>>>>>>>>> " << t33 << "\n" <<t34 << "\n\n";
		t33[0].functor() = "C";
		std::cout << ">>>>>>>>>>> " << t33 << "\n" <<t34 << "\n\n";

   tree t3 = tree( std::string( "f" ), { t1, t2 } ); 

   std::vector< tree > arguments = { t1, t2, t3 };
   tree t4 = tree( "F", std::move( arguments ));

   t2 = t4;
	std::cout<< "\nt2: \n"<< t2 <<"\n";  
   t2 = std::move(t4);
	std::cout<< t2 << "\n";  

	std::cout<< "\ntask5\n";
	t1.functor() = "hallo";
	std::cout << "t1 = " << t1 << "\nt2 = " << t2 << "\n";
	

	// Zadanie 6 - wywolac subst
	// Zadanie 9 - wywolac subst2
	std::cout << "\ntask6/7\n" << " \n";
	t2  = subst2(t2, "a", t1);
	std::cout<< t2 << "\n" << " \n";
       


  */