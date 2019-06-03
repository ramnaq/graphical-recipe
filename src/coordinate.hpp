#ifndef COORDINATE_HPP
#define COORDINATE_HPP

/*! The cartesian coordinate. The number of parameters in the constructor indicates the dimention */

class Coordinate {
private:
  double x;   /*! World coordinates. */
  double y;
  double z;
  double xop; /*! Orthogonal projection coordinates. */
  double yop;
  double zop;
  double xvp; /*! ViewPort coordinates. */
  double yvp;
  double xns; /*! Window coordinates. */
  double yns;

public:
  Coordinate(double x, double y, double z = 1) {
    this->x = x;
    this->y = y;
    this->z = z;
  }

  ~Coordinate() {}

  void setX(double x) {
    this->x = x;
  }

  void setY(double y) {
    this->y = y;
  }

  void setZ(double z) {
    this->z = z;
  }

  double get(const int axis) {
    switch(axis) {
      case 0: return this->getX();
      case 1: return this->getY();
      case 2: return this->getZ();
      default: return 3.14159265;
    }
  }

  double getX() const {
    return this->x;
  }

  double getY() const {
    return this->y;
  }

  double getZ() const {
    return this->z;
  }

  double getXop() const {
    return this->xop;
  }

  double getYop() const {
    return this->yop;
  }

  double getZop() const {
    return this->zop;
  }

  void setXop(double xop) {
    this->xop = xop;
  }

  void setYop(double yop) {
    this->yop = yop;
  }

  void setZop(double zop) {
    this->zop = zop;
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
