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
      compute3DGeometricCenter();
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

  void compute3DGeometricCenter() {
    this->cx = 0;
    this->cy = 0;
    this->cz = 0;
    int qtdCoord = 0;

    vector<Segment*>::iterator segment;
    vector<Coordinate*>::iterator coord;
    for(segment = segmentList.begin(); segment != segmentList.end(); segment++) {
      vector<Coordinate*> tmp = (*segment)->getCoordinates();
      for(coord = tmp.begin(); coord != tmp.end(); coord++) {
        cx += (*coord)->getX();
        cy += (*coord)->getY();
        cz += (*coord)->getZ();
        qtdCoord++;
      }
    }

    this->cx = this->cx / qtdCoord;
    this->cy = this->cy / qtdCoord;
    this->cz = this->cz / qtdCoord;
  }

};

#endif
