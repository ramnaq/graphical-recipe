#ifndef CLIPPING_HPP
#define CLIPPING_HPP

/*! Clipping methods. */

#include <bitset>
#include <iostream>

class Clipping {
private:
  vector<Coordinate*> vpCoord;

public:
  Clipping(vector<Coordinate*> vpCoord) {
    this->vpCoord = vpCoord;
  }

  ~Clipping() {}

  void pointClipping(GraphicObject* point) {
    Coordinate* pc = point->getCoordinates().front();

    if (pc->getXvp() < vpCoord.front()->getX() || pc->getXvp() > vpCoord.back()->getX())
      point->setVisibility(false);
    else if (pc->getYvp() < vpCoord.front()->getY() || pc->getYvp() > vpCoord.back()->getY())
      point->setVisibility(false);
    else
      point->setVisibility(true);
  }


  bitset<4> generateRegionCode(Coordinate* coord) {
    bitset<4> rg(0000);

    if (coord->getYvp() > vpCoord.back()->getY())
      rg[2] = 1; // Topo
    if (coord->getYvp() < vpCoord.front()->getY())
      rg[3] = 1; // Fundo
    if (coord->getXvp() > vpCoord.back()->getX())
      rg[1] = 1; // Direita
    if (coord->getXvp() < vpCoord.front()->getX())
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

    cout << "X min " << coordMin->getXvp() << endl;
    cout << "Y min " << coordMin->getYvp() << endl;

    cout << "X max " << coordMax->getXvp() << endl;
    cout << "X max " << coordMax->getYvp() << endl;

    cout << vpCoord.back()->getX() << endl;
    cout << vpCoord.back()->getY() << endl;

    cout << vpCoord.front()->getX() << endl;
    cout << vpCoord.front()->getY() << endl;

    // Coefficient
    double m = (coordMax->getYvp() - coordMin->getYvp()) / (coordMax->getXvp() - coordMin->getXvp());

    cout << "M " << m << endl;
    cout << "OP " << op << endl;
    if (op == 3) {
      computeNewCoordinates(coordMin, rgMin, m);
    } else if (op == 4) {
      computeNewCoordinates(coordMax, rgMax, m);
    } else {
      computeNewCoordinates(coordMin, rgMin, m);
      computeNewCoordinates(coordMax, rgMax, m);
    }
  }

  void computeNewCoordinates(Coordinate* coord, bitset<4> rg, int m) {
    cout << "RG " << rg << endl;
    cout << "-------" << endl;
    if (rg[0]) {
      double y_xe = m * (vpCoord.front()->getX() - coord->getXvp()) + coord->getYvp();
      coord->setYvp(y_xe);
      coord->setXvp(vpCoord.front()->getX());
    } if (rg[1]) {
      double y_xd = m * (vpCoord.back()->getX() - coord->getXvp()) + coord->getYvp();
      coord->setYvp(y_xd);
      coord->setXvp(vpCoord.back()->getX());
    } if (rg[2]) {
      double x_yt =  coord->getXvp() + (1/m) * (vpCoord.back()->getY() - coord->getYvp());
      coord->setXvp(x_yt);
      coord->setYvp(vpCoord.back()->getY());
    } if (rg[3]) {
      double x_yf = coord->getXvp() + (1/m) * (vpCoord.front()->getY() - coord->getYvp());
      coord->setXvp(x_yf);
      coord->setYvp(vpCoord.front()->getY());
    }
  }

  void lbClipping(GraphicObject* line) {
    Coordinate* coordMin = line->getCoordinates().front();
    Coordinate* coordMax = line->getCoordinates().back();

  }

};

#endif  //!< CLIPPING_HPP
