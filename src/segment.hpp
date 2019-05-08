#ifndef SEGMENT_HPP
#define SEGMENT_HPP

#include "coordinate.hpp"

/*! Structures a representation and behavior of a polygon */

class Segment {
private:
  Coordinate *a, *b;
public:
	Segment(Coordinate* a, Coordinate* b) {
    this->a = a;
    this->b = b;
	}

  ~Segment() {
    delete this->a;
    delete this->b;
  }

  Coordinate* getA() {
    return this->a;
  }

  Coordinate* getB() {
    return this->b;
  }

};

#endif
