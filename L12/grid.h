
#ifndef GRID_INCLUDED
#define GRID_INCLUDED 1

#include <SFML/System.hpp>
//#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <SFML/Window.hpp> 
#include <initializer_list>
#include <iostream>
#include <vector>
#include "figure.h"


class grid 
{
   struct cell {
      bool s0; // Current state.
      bool s1; // Next state.	

      cell( )
	: s0( false ),
	  s1( false ) {}
   };

   unsigned int xsize;
   unsigned int ysize;
public:   cell* c;

public:
   // Points in the grid are indexed in the computer graphics way, 
   // not in the matrix way.

   // Points are indexed in the computer graphics way, not in
   // the matrix way.
   //
   //  (0,ysize-1)   .....     (xsize-1,ysize-1)     
   //      .                          .
   //      .                          .       
   //    (0,0)       .....        (xsize-1,0)


   struct wrongchar
   {
      char c;                 // Character that we didn't like.
      unsigned int x;         // Its position.
      unsigned int y;


      wrongchar( char c, unsigned int x, unsigned int y )
         : c{c}, x{x}, y{y}
      { }
   };

   inline bool isonchar( char c ) { return c == 'X' || c == '#' || 
                                           c == 'O' || c == '0'; }

   inline bool isoffchar( char c ) { return c == '.'; } 


   grid( unsigned int xsize, unsigned int ysize )
	: xsize( xsize ),
	  ysize( ysize ),
      c( new cell [xsize * ysize] )
	{ }

   grid( const grid& g ) 
      : xsize( g.xsize ),
        ysize( g.ysize ),
        c( g.c)  
   {}

   grid( grid&& g)
      : xsize( std::move(g.xsize) ),
        ysize( std::move(g.ysize) ),
        c( std::move(g.c) )  
   {}



   void operator = ( const grid& g ) {
      xsize = g.xsize;
      ysize = g.ysize;
      c = g.c;

   }
   void operator = ( grid&& g ) {
      xsize = std::move(g.xsize);
      ysize = std::move(g.ysize);
      c     = std::move(g.c);
   }


   ~grid( ) {
      delete c;
   }

   cell* operator [] ( unsigned int x ) { return c + x * ysize; }
   const cell* operator [] ( unsigned int x ) const { return c + x * ysize; }

   void plot( sf::RenderWindow *window, unsigned int windowsizex, unsigned int windowsizey ) const ;

   void clear( );

   void addfigure( unsigned int x, unsigned int y,
                   std::initializer_list< const char* > p );
 
   void addfigure( unsigned int x, unsigned int y, const figure& f ); 

   void nextgeneration( );

   unsigned int numberOfAliveNeighbours(unsigned int x, unsigned int y);
   friend std::ostream& operator << ( std::ostream& stream, const grid& g );


   public:
       unsigned int castToX(unsigned int i);
       unsigned int castToY(unsigned int j);
       unsigned int castToC(unsigned int x, unsigned int y) const;

};

std::ostream& operator << ( std::ostream& stream, const grid& g);
std::ostream& operator << ( std::ostream& stream, const grid::wrongchar& w ); 

#endif 

