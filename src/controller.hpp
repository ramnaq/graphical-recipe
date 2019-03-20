#include <iostream>
#include "view.hpp"
#include "point.hpp"
#include "line.hpp"
#include "polygon.hpp"
#include "displayFile.hpp"

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
    int teste = 3;
    double x, y, x1, y1;
    string name;
    switch (teste) {
     case 1: {
        x = view->getEntryPontoX();
        y = view->getEntryPontoY();
        name = view->getObjectName();

        Point* p = new Point(name, x, y);
        display->insereGraphicObject(p);
        view->insertList(p);
        view->drawNewPoint(p);

        break;
     }
     case 2: {
        x = view->getEntryLineX();
        y = view->getEntryLineY();

        x1 = view->getEntryLineX1();
        y1 = view->getEntryLineY1();

        name = view->getObjectName();

        Coordenada* a = new Coordenada(x, y);
        Coordenada* b = new Coordenada(x1, y1);

        Line* line = new Line(name, a, b);
        display->insereGraphicObject(line);
        view->insertList(line);
        view->drawNewLine(line);

        break;
      }
      case 3: {
        Polygon *polygon = new Polygon("Nome", pointsForPolygon);
        display->insereGraphicObject(polygon);
        view->insertList(polygon);
        view->drawNewPolygon(polygon);

        break;
      }
    }
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

};

#endif

// Coordenada* coordenada = new Coordenada(100, 5);
// Coordenada* coordenada2 = new Coordenada(200, 5);
// Coordenada* coordenada3 = new Coordenada(200, 100);
// Coordenada* coordenada4 = new Coordenada(100, 100);
// Coordenada* coordenada5 = new Coordenada(100, 5);
