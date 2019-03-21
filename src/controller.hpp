#include <iostream>
#include "view.hpp"
#include "point.hpp"
#include "line.hpp"
#include "polygon.hpp"
#include "displayFile.hpp"
#include "objectType.hpp"

#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

class Controller {

private:
  View* view;
  DisplayFile *display;
  vector<Coordenada*> pointsForPolygon; // TODO Remover na refatoracao, serve para o poligono

public:
  Controller() {
    view = new View();
    display = new DisplayFile();
  }

  ~Controller() {}

  void run(int argc, char *argv[]) {
    view->initializeWindow(argc, argv);
  }

  void createObject() {
    int currentPage = view->getCurrentPage();
    double x, y, x1, y1;
    string name = view->getObjectName();;
    switch (currentPage) {
     case POINT: {
        x = view->getEntryPontoX();
        y = view->getEntryPontoY();

        Point* p = new Point(name, x, y);
        display->insereGraphicObject(p);
        view->insertList(p, "POINT");
        view->drawNewPoint(p);

        break;
     }
     case LINE: {
        x = view->getEntryLineX();
        y = view->getEntryLineY();

        x1 = view->getEntryLineX1();
        y1 = view->getEntryLineY1();

        Coordenada* a = new Coordenada(x, y);
        Coordenada* b = new Coordenada(x1, y1);

        Line* line = new Line(name, a, b);
        display->insereGraphicObject(line);
        view->insertList(line, "LINE");
        view->drawNewLine(line);

        break;
      }
      case POLYGON: {
        Polygon *polygon = new Polygon(name, pointsForPolygon);
        display->insereGraphicObject(polygon);
        view->insertList(polygon, "POLYGON");
        view->drawNewPolygon(polygon);

        break;
      }
    }
  }

  void removeFromList() {
    int listPos = view->removeFromList();
    display->deletarElemento(listPos);
    view->clear_surface();
    updateDrawScreen();
  }

  void removeFromCoordPolygonList() {
    int index = view->removeFromCoordPolygonList();
    pointsForPolygon.erase(pointsForPolygon.begin() + index);
  }

  void addNewLineForPolygon() {
    double x = view->getEntryPolygonX();
    double y = view->getEntryPolygonY();
    Coordenada* coordenada = new Coordenada(x, y);
    pointsForPolygon.push_back(coordenada);
    view->insertCoordPolygonList();
  }

  void openNewObjectWindow() {
    view->openNewObjectWindow();
  }

  void create_surface(GtkWidget *widget) {
    view->create_surface(widget);
  }

  void draw(cairo_t *cr) {
    view->draw(cr);
  }

  void initializeWindowViewPort() {
    view->initializeWindowViewPort();
  }

  // TODO REFATORAR ESSE POVO TOD0, fazer um único método que recebe
  // como parâmetro o tipo de modificação (zoomIn, goRight...) a partir dos callbacks
  // Desde zoomIn até goDownRight
  void zoomIn() {
    double passo = view->getPasso();
    view->updateWindow(passo, 0);
    updateDrawScreen();
  }

  void zoomOut() {
    double passo = view->getPasso();
    view->updateWindow(passo, 1);
    updateDrawScreen();
  }

  void goRight() {
    double passo = view->getPasso();
    view->updateWindow(passo, 2);
    updateDrawScreen();
  }

  void goLeft() {
    double passo = view->getPasso();
    view->updateWindow(passo, 3);
    updateDrawScreen();
  }

  void goUp() {
    double passo = view->getPasso();
    view->updateWindow(passo, 4);
    updateDrawScreen();
  }

  void goDown() {
    double passo = view->getPasso();
    view->updateWindow(passo, 5);
    updateDrawScreen();
  }

  void goUpLeft() {
    double passo = view->getPasso();
    view->updateWindow(passo, 6);
    updateDrawScreen();
  }

  void goUpRight() {
    double passo = view->getPasso();
    view->updateWindow(passo, 7);
    updateDrawScreen();
  }

  void goDownLeft() {
    double passo = view->getPasso();
    view->updateWindow(passo, 8);
    updateDrawScreen();
  }

  void goDownRight() {
    double passo = view->getPasso();
    view->updateWindow(passo, 9);
    updateDrawScreen();
  }

  void updateDrawScreen() {
    Elemento<GraphicObject*>* nextElement = display->getHead(); // primeiro elemento da display file
    view->clear_surface();
    while (nextElement != NULL) {
    	GraphicObject* element = nextElement->getInfo();
    	switch (element->getType()) {
    		case POINT: {
    				view->drawNewPoint(element);
            break;
    		} case LINE: {
    				view->drawNewLine(element);
            break;
    		} case POLYGON: {
            view->drawNewPolygon(element);
            break;
        }
      }
      nextElement = nextElement->getProximo();
    }
  }

};

#endif
