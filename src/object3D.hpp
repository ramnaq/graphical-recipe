#ifndef Object3D_HPP
#define Object3D_HPP

#include "graphicObject.hpp"
#include "segment.hpp"

/*! Structures a representation and behavior of a "line segment" */

class Object3D: public GraphicObject {
private:
  vector<Segment*> segmentList;

public:
	Object3D(string name, vector<Segment*> &segmentList) :
		GraphicObject(name, OBJECT3D) {
      this->segmentList = segmentList;
    }

  ~Object3D() {
    vector<Segment*>::iterator it;
    for(it = segmentList.begin(); it != segmentList.end(); it++) {
      delete *it;
    }
  }

  vector<Segment*> getSegmentList() {
    return this->segmentList;
  }

};

#endif
