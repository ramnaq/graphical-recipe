#ifndef CLIPPING_HPP
#define CLIPPING_HPP

/*! Clipping methods. */

#include <bitset>
#include <iostream>

class Clipping {
private:
  vector<Coordinate*> wCoord;

public:
  Clipping() {
    this->wCoord = {new Coordinate(-1,-1), new Coordinate(1,1)};
  }

  ~Clipping() {
    delete this->wCoord.front();
    delete this->wCoord.back();
  }

  void pointClipping(GraphicObject* point) {
    Coordinate* pc = point->getCoordinates().front();

    if (pc->getXns() < wCoord.front()->getX() || pc->getXns() > wCoord.back()->getX())
      point->setVisibility(false);
    else if (pc->getYns() < wCoord.front()->getY() || pc->getYns() > wCoord.back()->getY())
      point->setVisibility(false);
    else
      point->setVisibility(true);
  }

  bitset<4> generateRegionCode(Coordinate* coord) {
    bitset<4> rg(0000);

    if (coord->getYns() < wCoord.front()->getY())
      rg[3] = 1; // Fundo
    if (coord->getYns() > wCoord.back()->getY())
      rg[2] = 1; // Topo
    if (coord->getXns() > wCoord.back()->getX())
      rg[1] = 1; // Direita
    if (coord->getXns() < wCoord.front()->getX())
      rg[0] = 1; // Esquerda

    return rg;
  }

  int verify(bitset<4> rgMin, bitset<4> rgMax) {
    if (rgMin.none() && rgMax.none()) // Fully inside the window
      return 1;
    else if ((rgMin & rgMax).any()) // Fully out of the window
      return 2;
    else {
      // Parcially inside the window
      if (!rgMin.none() && rgMax.none())
        return 3;
      else if (rgMin.none() && !rgMax.none()) // coordMin is out of the window
        return 4;
      else
        return 5; // Both are out of the window
    }
  }

  void lineClipping(GraphicObject* line, int chosenAlgorithm) {
    Coordinate* coordMin = line->getCoordinates().front();
    Coordinate* coordMax = line->getCoordinates().back();
    bitset<4> rgMin = generateRegionCode(coordMin);
    bitset<4> rgMax = generateRegionCode(coordMax);

    int op = verify(rgMin, rgMax);
    switch (op) {
      case 1:
        line->setVisibility(true);
        break;
      case 2:
        line->setVisibility(false);
        break;
      default:
        line->setVisibility(true);
        if (chosenAlgorithm)
          csClipping(line, op, rgMin, rgMax);
        else
          lbClipping(line);
        break;
    }
  }

  void csClipping(GraphicObject* line, int op, bitset<4> rgMin, bitset<4> rgMax) {
    Coordinate* coordMin = line->getCoordinates().front();
    Coordinate* coordMax = line->getCoordinates().back();

    // Coefficient
    double m = (coordMax->getYns() - coordMin->getYns()) / (coordMax->getXns() - coordMin->getXns());

    if (op == 3) {
      computeNewCoordinates(coordMin, rgMin, m);
    } else if (op == 4) {
      computeNewCoordinates(coordMax, rgMax, m);
    } else {
      computeNewCoordinates(coordMin, rgMin, m);
      computeNewCoordinates(coordMax, rgMax, m);
    }
  }

  void computeNewCoordinates(Coordinate* coord, bitset<4> rg, double m) {
    if (rg[0]) {
      double y_xe = m * (wCoord.front()->getX() - coord->getXns()) + coord->getYns();
      coord->setYns(y_xe);
      coord->setXns(wCoord.front()->getX());
    } if (rg[1]) {
      double y_xd = m * (wCoord.back()->getX() - coord->getXns()) + coord->getYns();
      coord->setYns(y_xd);
      coord->setXns(wCoord.back()->getX());
    } if (rg[2]) {
      double x_yt =  coord->getXns() + (1/m) * (wCoord.back()->getY() - coord->getYns());
      coord->setXns(x_yt);
      coord->setYns(wCoord.back()->getY());
    } if (rg[3]) {
      double x_yf = coord->getXns() + (1/m) * (wCoord.front()->getY() - coord->getYns());
      coord->setXns(x_yf);
      coord->setYns(wCoord.front()->getY());
    }
  }

  void lbClipping(GraphicObject* line) {
    Coordinate* coordMin = line->getCoordinates().front();
    Coordinate* coordMax = line->getCoordinates().back();

  }

};

#endif  //!< CLIPPING_HPP
