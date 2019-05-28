#ifndef SEGMENT_HPP
#define SEGMENT_HPP

#include "coordinate.hpp"

/*! Structures a representation and behavior of a polygon */

class Segment {
private:
  vector<Coordinate*> pair;
  bool visible;
public:
	Segment(Coordinate* a, Coordinate* b) {
    this->pair.push_back(a);
    this->pair.push_back(b);
    this->visible = true;
	}

  ~Segment() {
    delete this->pair.front();
    delete this->pair.back();
  }

  vector<Coordinate*> getCoordinates() {
    return this->pair;
  }

  bool isVisible() {
		return this->visible;
	}

	void setVisibility(bool updateVisibility) {
		this->visible = updateVisibility;
	}

};

#endif
