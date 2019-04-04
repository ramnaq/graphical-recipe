#ifndef COORDINATE_HPP
#define COORDINATE_HPP


/*! The cartesian coordinate. The number of parameters in the constructor indicates the dimention */

class Coordinate {
private:
  double x;   /*! World coordinates. */
  double y;
  double xvp; /*! ViewPort coordinates. */
  double yvp;

public:
	Coordinate(double x, double y) {
    this->x = x;
    this->y = y;
  }

	~Coordinate() {}

  void setX(double x) {
    this->x = x;
  }

  void setY(double y) {
    this->y = y;
  }

  double getX() const {
    return this->x;
  }

  double getY() const {
    return this->y;
  }

  void setXvp(double x) {
    this->xvp = x;
  }

  void setYvp(double y) {
    this->yvp = y;
  }

  double getXvp() const {
    return this->xvp;
  }

  double getYvp() const {
    return this->yvp;
  }

};

#endif  //!< COORDINATE_HPP
