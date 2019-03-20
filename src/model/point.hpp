#ifndef POINT_HPP
#define POINT_HPP

class Point : public Vector {
  public:
	Point() : Vector{0, 0, 1} {}

	Point(double x, double y, double z = 1) : Vector{x, y, z} {}

	virtual ~Point() {}

};
