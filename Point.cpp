#include "Point.h"

namespace Com_Methods
{
	Point::Point(double x = 0, double y = 0, double z = 0) : X(x), Y(y), Z(z) {}
	double Point::x()const { return X; }
	double Point::y()const { return Y; }
	double Point::z()const { return Z; }
}
