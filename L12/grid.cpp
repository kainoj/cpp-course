#include "grid.h"


std::ostream& operator << ( std::ostream& stream, const grid& g) {

	size_t k = 0;
	for( unsigned int i=0; i< g.xsize; i++) {
		for( unsigned int j=0; j<g.ysize; j++) {
			stream << g.c[k++].s0? "0": ".";
		}
		stream << "\n";
			
	}
	return stream;	
}


void grid::clear() {
	size_t k=0;
	for(size_t k=0; k<xsize*ysize; k++)
		c[k].s0 = c[k].s1 = false;

}


std::ostream& operator << ( std::ostream& stream, const grid::wrongchar& w ) {

	stream << "The char that we don't like: " << w.c << " It's at posiotion: (" << w.x << ", " << w.y << " )\n";
	return stream;
}


unsigned int grid::castToX(unsigned int i) {
	return i % xsize;
}

unsigned int grid::castToY(unsigned int j) {
	return j / xsize;
}

unsigned int grid::castToC(unsigned int x, unsigned int y) const{
	return x*xsize+y; //ok
}



void grid::addfigure( unsigned int x, unsigned int y, const figure& f ) {
	//std::cout<<this -> operator [](4) -> s0 << " \n\n";
	for( unsigned int i=0; i< f.repr.size(); i++ ) {
		for(unsigned int j=0; j< f.repr[i].size(); j++)
			if(!isonchar( f.repr[i][j] ) && !isoffchar( f.repr[i][j])   ) throw wrongchar(f.repr[i][j],i,j);
				else
					if( i+x< xsize && j+y<ysize)
						c[castToC(i+x,j+y)  ].s0 = isonchar( f.repr[i][j]);
	}
}

void grid::addfigure( unsigned int x, unsigned int y,
                   std::initializer_list< const char* > p ) {
	addfigure(x,y, figure(p));


}

unsigned int grid::numberOfAliveNeighbours(unsigned int x, unsigned int y) {
	unsigned int alive = 0;
	//if ( x!=0 && x!=(xsize-1) && y!=0 && y!=(ysize-1) ) { // is not at the grid edge
	alive += x==0? 			0: c[castToC(x-1, y)].s0;
	alive += x==(xsize-1)? 	0: c[castToC(x+1, y)].s0;
	alive += y==0?			0: c[castToC(x, y-1)].s0;
	alive += y==(ysize-1)?  0: c[castToC(x, y+1)].s0;

	alive += (x==0 || y == 0)?						0: c[castToC(x-1,y-1)].s0;
	alive += (x==0 || y == (ysize-1))?				0: c[castToC(x-1, y+1)].s0;
	alive += (x==(xsize-1) || y == 0)?				0: c[castToC(x+1, y-1)].s0;
	alive += (x == (xsize-1) || y == (ysize-1))?	0: c[castToC(x+1, y+1)].s0;
	return alive;

}

void grid::nextgeneration() {
	for (unsigned int i=0; i< xsize; i++) {
		for( unsigned int j=0; j<ysize; j++) {
			unsigned int alive = numberOfAliveNeighbours(i,j);
			unsigned int index = castToC(i,j);
			if( c[index].s0 ) {
				switch( alive) {
					case 2:
					case 3:
						c[index].s1=true;
						break;
					default:
						c[index].s1=false;
						break;
					}
			}
			else{
				c[index].s1 = alive==3? true: false;
			}

		}
	}
	for(int i=0; i<xsize*ysize; i++)
		c[i].s0 = std::move(c[i].s1);
}



void grid::plot(sf::RenderWindow *window, unsigned int windowsizex, unsigned int windowsizey) const{
	//std::cout << "drawing...";
	// http://www.sfml-dev.org/tutorials/1.6/graphics-shape.php
	// http://cpp0x.pl/kursy/Kurs-SFML-1-6-C++/Tworzenie-i-wyswietlanie-sprajtow/333
	float cell_length = windowsizex / xsize;
	float cell_height = windowsizey / ysize;

	 sf::Image img;
     img.Create(cell_length,cell_height, sf::Color::White);
     sf::Sprite spr;
     spr.SetImage(img);

  	for(unsigned int x=0; x < xsize; x++) {
		for(unsigned int y=0; y < ysize; y++) {
			if(c[ castToC(x,y) ].s0 == true) {
			//if( x*y%2==1){
				spr.SetPosition(x*cell_length, y*cell_height);
				window -> Draw(spr);
			}

		}
	}

	//::cout << *this;
	//sf::Shape Rect   =  sf::Shape::Rectangle(0  , 0, windowsizex , windowsizey/2, sf::Color(23 , 11, 255, 200));
	//window -> Draw(Rect);

}     