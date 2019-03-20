#include "view.hpp"
#include "point.hpp"
#include "displayFile.hpp"

#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

class Controller {

private:
  View* view;
  DisplayFile *display;

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
    double x = view->getEntryPontoX();
    double y = view->getEntryPontoY();
    string name = view->getObjectName();

    Point* p = new Point(name, x, y);
    display->insereGraphicObject(p);

    view->insertList(p);
    view->drawNewObject(p);
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
