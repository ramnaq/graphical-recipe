#ifndef COORDINATE_HPP
#define COORDINATE_HPP

/*! The cartesian coordinate. The number of parameters in the constructor indicates the dimention */

class Coordinate {
private:
  double x;   /*! World coordinates. */
  double y;
  double xvp; /*! ViewPort coordinates. */
  double yvp;
  double xns; /*! Window coordinates. */
  double yns;

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

  double getXns() {
    return this->xns;
  }

  double getYns() {
    return this->yns;
  }

  void setXns(double xns) {
    this->xns = xns;
  }

  void setYns(double yns) {
    this->yns = yns;
  }

  static Coordinate* newWindowCoordinate(double x, double y) {
    Coordinate* w = new Coordinate(0, 0);
    w->setXns(x);
    w->setYns(y);
    return w;
  }

};

#endif  //!< COORDINATE_HPP
