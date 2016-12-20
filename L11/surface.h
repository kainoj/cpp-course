#include <iostream>
#include <vector>
#include <math.h>

struct surf {
	virtual double area( ) const = 0;
	virtual double circumference( ) const = 0;
	virtual surf* clone( ) const & = 0;
	virtual surf* clone( ) && = 0;
	virtual void print( std::ostream& ) const = 0;
	virtual ~surf( );
};


struct rectangle : public surf {
	double x1, y1;
	double x2, y2;
	double area( ) const override {
		return abs(x1-x2)*abs(y1-y2);
	}
	double circumference( ) const override {
		return 2*abs(x1-x2)+2*abs(y1-y2);
	}
	rectangle* clone( ) const & override;
	rectangle* clone( ) && override;
	void print( std::ostream& stream) const override {
		std:: cout << stream;
	}


	rectangle(double x1, double y1, double x2, double y2)
	 : x1{x1}, y1{y1}, x2{x2}, y2{y2}
	{}
};



struct triangle : public surf {
	double x1, y1; // Positions of corners.
	double x2, y2;
	double x3, y3;
	double area( ) const override;
	double circumference( ) const override;
	triangle* clone( ) const & override;
	triangle* clone( ) && override;
	void print( std::ostream& ) const override;

	triangle(double x1, double y1, double x2, double y2, double x3, double y3)
	 : x1{x1}, y1{y1}, x2{x2}, y2{y2}, x3{x3}, y3{y3}
	 {}
};


struct circle : public surf {
	double x; // Position of center.
	double y;
	double radius;
	double area( ) const override {
		return radius*radius*M_PI;
	}
	double circumference( ) const override {
		return 2*M_PI*radius;
	}
	circle* clone( ) const & override;
	circle* clone( ) && override;
	void print( std::ostream& ) const override;

	circle(double x, double y, double radius)
		: x{x}, y{y}, radius{radius} 
		{}

};