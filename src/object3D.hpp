#ifndef Object3D_HPP
#define Object3D_HPP

#include "graphicObject.hpp"
#include "segment.hpp"

/*! Structures a representation and behavior of a "line segment" */

// TODO Review public/private scopes

class Object3D: public GraphicObject {
private:
  vector<Segment*> segmentList;
  vector<Coordinate*> allCoord;

  void storeAllCoord() {
    vector<Segment*>::iterator segment;
    for(segment = segmentList.begin(); segment != segmentList.end(); segment++) {
        vector<Coordinate*> segmentCoord = (*segment)->getCoordinates();
        allCoord.insert(allCoord.end(), segmentCoord.begin(), segmentCoord.end());
    }
  }

public:
  Object3D(string name) : GraphicObject(name, OBJECT3D) {}

	Object3D(string name, vector<Segment*> &segmentList) :
		GraphicObject(name, OBJECT3D) {
      this->segmentList = segmentList;
      computeGeometricCenter();
      storeAllCoord();
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

  vector<Coordinate*> getAllCoord() {
    return this->allCoord;
  }

  void computeGeometricCenter() {
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

  void addCoordinate(Coordinate* c) {
    int size = allCoord.size();
    if (size % 2 == 1) {
      // the last Coordinate in allCoord now can form a Segment
      segmentList.push_back(new Segment(allCoord[size-1], c));
    }

    allCoord.push_back(c);
  }

};

#endif
