#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <stdexcept>
#include <iostream>

#include "bezierCurve.hpp"
#include "bezierSurface.hpp"
#include "bspline.hpp"
//#include "bsplineSurface.hpp"
#include "clipping.hpp"
#include "displayFile.hpp"
#include "enum.hpp"
#include "line.hpp"
#include "objectTransformation.hpp"
#include "objDescriptor.hpp"
#include "object3D.hpp"
#include "point.hpp"
#include "polygon.hpp"
#include "view.hpp"

/*! Representation of the Controller (or Control) module of the MVC (Model, View, Control) architecture */

class Controller {
private:
  View view;
  DisplayFile display;
  Clipping clipping;
  vector<Coordinate*> pointsForPolygon;
  vector<Coordinate*> pointsForCurve;
  vector<vector<Coordinate*>> pointsForSurface;
  vector<Segment*> segmentsForObject3D;
  Coordinate cop = Coordinate(0, 0, -100);

public:
  Controller() {
  }

  ~Controller() {
  }

  void run(int argc, char* argv[]) {
    view.initializeGtkWindow(argc, argv);
  }

  //! Creates an instance of a Graphical Object and asks 'view' to draw it.
  /*!
   * Uses information from 'view' to create Coordinates, instantiate a type of
   * GraphicObject and then sends this instance to 'view' to be drawn).
   */
  void createObject() {
    int currentPage = view.getCurrentPage();
    string name = view.getObjectName();
    string objType;
    GraphicObject* obj;

    switch (currentPage) {
     case POINT: {
        vector<Coordinate*> pointCoordinate = {new Coordinate(view.getEntryPointX(), view.getEntryPointY(), view.getEntryPointZ())};
        obj = new Point(name, pointCoordinate);
        objType = "PONTO";

        break;
     }
     case LINE: {
        vector<Coordinate*> lineCoordinate = {new Coordinate(view.getEntryLineX1(), view.getEntryLineY1(), view.getEntryLineZ1()),
                                               new Coordinate(view.getEntryLineX2(), view.getEntryLineY2(), view.getEntryLineZ2())};
        obj = new Line(name, lineCoordinate);
        objType = "LINHA";

        break;
      }
      case POLYGON: {
        try {
          if (pointsForPolygon.size() < 3) {
            throw std::runtime_error("Cannot create polygon without at least three points!");
          }
          obj = new Polygon(name, pointsForPolygon, view.getCheckBtnState());
          objType = "POLIGONO";

          pointsForPolygon.clear();
          view.clearPolygonEntry();
        } catch(const std::runtime_error& e) {
          std::cout << "[ERROR] " << e.what() << std::endl;
          view.logError("Pontos insuficientes para criação de polígono.\n");
        }
        break;
      }
      case CURVE: {
        try {
          if (pointsForCurve.size() < 4) {
            throw std::runtime_error("Cannot create a curve without at least 4 points!");
          }

          if (view.isCheckBtnSplineChecked()) {
            obj = new BSpline(name, pointsForCurve, view.getDelta());
          } else {
            obj = new BezierCurve(name, pointsForCurve);
          }
          objType = "CURVA";

          pointsForCurve.clear();
          view.clearCurveEntry();
        } catch(const std::runtime_error& e) {
          std::cout << "[ERROR] " << e.what() << std::endl;
          view.logError("Pontos insuficientes para criação de curva.\n");
        }
        break;
      }
      case OBJECT3D: {
        obj = new Object3D(name, segmentsForObject3D);
        objType = "OBJETO 3D";

        segmentsForObject3D.clear();
        view.clearObjet3DEntry();
        break;
      }
      case SURFACE: {
        try {
          if (pointsForSurface.size() < 4) {
            throw std::runtime_error(
                "Cannot create a surface without at least 16 points!");
          }

          if (view.isCheckBtnSplineSurfaceChecked()) {
            //obj = new BSplineSurface(name, pointsForSurface);
          } else {
            obj = new BezierSurface(name, pointsForSurface);
          }
          objType = "SUPERFICIE";

          pointsForSurface.clear();
          view.clearSurfaceEntry();
        } catch(const std::runtime_error& e) {
          std::cout << "[ERROR] " << e.what() << std::endl;
          view.logError("Pontos insuficientes para criação de Superfície.\n");
        }
        break;
      }
    }

    display.insert(obj);
    view.insertIntoListBox(*obj, objType);
    updateDrawScreen();
  }

  void createObjectsFromFile() {
    string fileName = view.chooseFile();
    ObjDescriptor od;

    vector<GraphicObject*> objs = od.read(fileName);
    for (int i = 0; i < objs.size(); ++i) {
      display.insert(objs[i]);
      showObjectIntoView(objs[i]);
    }

    updateDrawScreen();
  }

  void saveWorldToFile() {
    string fileName = view.getFileToSaveWorld();

    ObjDescriptor od;
    od.write(display.getObjs(), fileName);

    view.clearSaveWorldFile();
  }

  void showObjectIntoView(GraphicObject* gobj) {
    switch (gobj->getType()) {
      case POINT:
        view.insertIntoListBox(*gobj, "PONTO");
        break;
      case LINE:
        view.insertIntoListBox(*gobj, "LINHA");
        break;
      case POLYGON:
        view.insertIntoListBox(*gobj, "POLIGONO");
        pointsForPolygon.clear();
        break;
     case OBJECT3D:
        view.insertIntoListBox(*gobj, "OBJ_3D");
        segmentsForObject3D.clear();
        break;
    }
  }

  //! Changes an object position through translation, scaling or rotation.
  /*!
   * Takes the selected object in the object list and applies a transformation.
   */
  void executeObjectTransformation() {
    int currentPage = view.getCurrentPageTransformation();
    int currentObjectIndex = view.getCurrentObjectIndex();
    GraphicObject* obj = display.getElementoNoIndice(currentObjectIndex);

    switch (currentPage) {
      case TRANSLATION: {
        Coordinate translationVector(view.getEntryTranslationX(), view.getEntryTranslationY(), view.getEntryTranslationZ());

        if (obj->getType() != OBJECT3D && obj->getType() != SURFACE) {
          ObjectTransformation::translation(static_cast<GraphicObject2D*>(obj)->getCoordinates(), &translationVector);
        } else {
          ObjectTransformation::translation(static_cast<Object3D*>(obj)->getAllCoord(), &translationVector);
        }
        break;
      }
      case SCALING: {
        Coordinate scalingVector(view.getEntryScalingX(), view.getEntryScalingY(), view.getEntryScalingZ());
        Coordinate objCenter = obj->getGeometricCenter();

        if (obj->getType() != OBJECT3D && obj->getType() != SURFACE) {
          ObjectTransformation::scaling(static_cast<GraphicObject2D*>(obj)->getCoordinates(), &objCenter, &scalingVector);
        } else {
          ObjectTransformation::scaling(static_cast<Object3D*>(obj)->getAllCoord(), &objCenter, &scalingVector);
        }
        break;
      }
      case ROTATION: {
        int radioBtnChosen = view.getRotationRadioButtonState();
        int whichAxis = view.getObjRotateBtnState();
        double angle = view.getAngle();
        Coordinate* reference;

        if (radioBtnChosen == 1) {
          reference = new Coordinate(0,0,0);
        } else if (radioBtnChosen == 2) {
          Coordinate tmp = obj->getGeometricCenter();
          reference = new Coordinate(tmp.getX(), tmp.getY(), tmp.getZ());
        } else {
          reference = new Coordinate(view.getEntryRotationX(), view.getEntryRotationY(), view.getEntryRotationZ());
        }

        if (obj->getType() != OBJECT3D && obj->getType() != SURFACE) {
          ObjectTransformation::rotation(static_cast<GraphicObject2D*>(obj)->getCoordinates(), angle, reference, whichAxis);
        } else {
          ObjectTransformation::rotation(static_cast<Object3D*>(obj)->getAllCoord(), angle, reference, whichAxis);
        }

        delete reference;
        break;
      }
    }

    updateDrawScreen();
  }

  void openAddObjectWindow() {
    view.openAddObjectWindow();
  }

  void openEditObjectWindow() {
    view.openEditObjectWindow();
  }

  void create_surface(GtkWidget *widget) {
    view.create_surface(widget);
  }

  void draw(cairo_t *cr) {
    view.draw(cr);
  }

  void initializeWindowViewPort() {
    view.initializeWindowViewPort();
  }

  //! Calls View::removeSelectedObject() and updates the screen with updateDrawScreen().
  void removeSelectedObject() {
    int index = view.removeFromList(view.getListObj());

    display.remove(index);
    updateDrawScreen();
  }

  void removeFromCoordPolygonList() {
    int index = view.removeFromList(view.getListCoordPolygon());

    if (index > -1) {
      pointsForPolygon.erase(pointsForPolygon.begin() + index);
    }
  }

  void removeFromCoordCurveList() {
    int index = view.removeFromList(view.getListCoordCurve());

    if (index > -1) {
      pointsForCurve.erase(pointsForCurve.begin() + index);
    }
  }

  void removeFromCoordSurfaceList() {
    int index = view.removeFromList(view.getListCoordSurface());

    if (index > -1) {
      pointsForSurface.erase(pointsForSurface.begin() + index);
    }
  }

  void removeFromCoordObject3DList() {
    int index = view.removeFromList(view.getListSegment());

    if (index > -1) {
        segmentsForObject3D.erase(segmentsForObject3D.begin() + index);
    }
  }

  /*!
   * Gets (x, y) from view to create a new Coordinate and then add a new line
   * to a Polygon which is being created.
   */
  void addNewLineForPolygon() {
    double x = view.getEntryPolygonX();
    double y = view.getEntryPolygonY();
    double z = view.getEntryPolygonZ();
    Coordinate* c = new Coordinate(x, y, z);

    pointsForPolygon.push_back(c);
    view.insertCoordList(view.getListCoordPolygon(), x, y, z);
  }

  /*!
   * Gets (x, y, z) from view to create a new Coordinate, to further add it
   * to a Curve which is being created.
   */
  void addNewPointForCurve() {
    double x = view.getEntryCurveX();
    double y = view.getEntryCurveY();
    double z = view.getEntryCurveZ();
    Coordinate* c = new Coordinate(x, y, z);

    pointsForCurve.push_back(c);
    view.insertCoordList(view.getListCoordCurve(), x, y, z);
  }

  /*!
   * Gets (x, y, z) from view to create a new Coordinate, to further add it
   * to a Surface which is being created.
   */
  void addNewPointForSurface() {
    //double x = view.getEntrySurfaceX();
    //double y = view.getEntrySurfaceY();
    //double z = view.getEntrySurfaceZ();
    //Coordinate* c = new Coordinate(x, y, z);

    //pointsForSurface.push_back(c);
    //view.insertCoordList(view.getListCoordSurface(), x, y, z);
    /*
    Coordinate* c1 = new Coordinate(0,0,0);
    Coordinate* c2 = new Coordinate(0,30,40);
    Coordinate* c3 = new Coordinate(0,60,30);
    Coordinate* c4 = new Coordinate(0,100,0);
    */
    Coordinate* c1 = new Coordinate(0,0,0);
    Coordinate* c2 = new Coordinate(0,30,40);
    Coordinate* c3 = new Coordinate(0,60,30);
    Coordinate* c4 = new Coordinate(0,100,0);
    vector<Coordinate*> v1;
    v1.push_back(c1);
    v1.push_back(c2);
    v1.push_back(c3);
    v1.push_back(c4);
    Coordinate* c5 = new Coordinate(30,25,20);
    Coordinate* c6 = new Coordinate(20,60,50);
    Coordinate* c7 = new Coordinate(30,80,50);
    Coordinate* c8 = new Coordinate(40,0,20);
    vector<Coordinate*> v2;
    v2.push_back(c5);
    v2.push_back(c6);
    v2.push_back(c7);
    v2.push_back(c8);
    Coordinate* c9 = new Coordinate(60,30,20);
    Coordinate* c10 = new Coordinate(80,60,50);
    Coordinate* c11 = new Coordinate(70,100,45);
    Coordinate* c12 = new Coordinate(60,0,25);
    vector<Coordinate*> v3;
    v3.push_back(c9);
    v3.push_back(c10);
    v3.push_back(c11);
    v3.push_back(c12);
    Coordinate* c13 = new Coordinate(100,0,1);
    Coordinate* c14 = new Coordinate(110,30,40);
    Coordinate* c15 = new Coordinate(110,60,30);
    Coordinate* c16 = new Coordinate(100,90,1);
    vector<Coordinate*> v4;
    v4.push_back(c13);
    v4.push_back(c14);
    v4.push_back(c15);
    v4.push_back(c16);

    pointsForSurface.push_back(v1);
    pointsForSurface.push_back(v2);
    pointsForSurface.push_back(v3);
    pointsForSurface.push_back(v4);
  }

  void addNewSegmentForObject3D() {
    double x1 = view.getEntry3DX1();
    double y1 = view.getEntry3DY1();
    double z1 = view.getEntry3DZ1();
    double x2 = view.getEntry3DX2();
    double y2 = view.getEntry3DY2();
    double z2 = view.getEntry3DZ2();

    Coordinate* a = new Coordinate(x1, y1, z1);
    Coordinate* b = new Coordinate(x2, y2, z2);
    Segment* s = new Segment(a, b);

    segmentsForObject3D.push_back(s);
    view.insertCoordList(view.getListSegment(), x1, y1, z1, x2, y2, z2);
  }

  //! Changes the visualization window (of type Window) according the op code.
  /*!
   * @param op The operation to be done on the Window (@see View::updateWindow()).
   */
  void changeWindow(int op) {
    try {
      view.updateWindow(view.getStep(), op);
    } catch (int e) {
      view.logWarning("Passo do zoom acima do limite!\n");
    }
    updateDrawScreen();
  }

  void rotateCamera(GraphicObject* element) {
      Window* window = view.getWindow();

      double angleX = window->getAngleX();
      double angleY = window->getAngleY();
      double angleZ = window->getAngleZ();

      Coordinate geoCenter = element->getGeometricCenter();

      if (element->getType() != OBJECT3D && element->getType() != SURFACE) {
        ObjectTransformation::cameraRotation(
            static_cast<GraphicObject2D*>(element)->getCoordinates(),
            &geoCenter,
            angleX,
            angleY,
            angleZ
        );
      } else {
        ObjectTransformation::cameraRotation(
            static_cast<Object3D*>(element)->getAllCoord(),
            &geoCenter,
            angleX,
            angleY,
            angleZ
        );
      }
  }

  void updateObjRotateBtnState(int newState) {
    view.updateObjRotateBtnState(newState);
  }

  void updateRadioBtnState(int newState) {
    view.updateRadioBtnState(newState);
  }

  void updateClippingRadioBtnState(int newState) {
    view.updateClippingRadioBtnState(newState);
  }

  void updateCheckBtnState() {
    view.updateCheckBtnState();
  }

  void updateCheckBtnSpline() {
    view.updateCheckBtnSpline();
  }

  void updateCheckBtnSplineSurface() {
    view.updateCheckBtnSplineSurface();
  }

  void updateProjectionState(int newState) {
    view.updateProjectionBtnState(newState);
    updateDrawScreen();
  }

  void updateCOP() {
    cop.setZ(-view.getNewCOP());
    updateDrawScreen();
  }

  void updateWindowAngle(int whichAxis) {
    double angle = view.getAngleRotateWindow();

    view.updateWindow(angle, whichAxis);
    updateDrawScreen();
  }

  //! Calls 'view' to (re)drawn all elements in 'displayFile'.
  void updateDrawScreen() {
    view.clear_surface();

    // Step 1 and 2 (Both projections) - Translate COP and compute θx e θy
    view.computeAngleForProjection(&cop);

    Elemento<GraphicObject*>* nextElement = display.getHead();
    while (nextElement != NULL) {
      GraphicObject* element = nextElement->getInfo();

      rotateCamera(element);

      view.transformProjection(element, &cop);
      view.transformSCN(element);

      switch (element->getType()) {
        case POINT: {
          Point* point = static_cast<Point*>(element);

          if (clipping.pointClipping(point->getCoordinates()[0])) {
            view.transform(point);
            view.drawNewPoint(point);
          }
          break;
        }
        case LINE: {
          Line* line = static_cast<Line*>(element);

          if (clipping.lineClipping(line->getCoordinates(), view.getLineClippingAlgorithm())) {
            view.transform(line);
            view.drawNewLine(line);
          }
          break;
        }
        case POLYGON: { // TODO Fix visibility
          Polygon* polygon = static_cast<Polygon*>(element);

          clipping.polygonClipping(polygon);
          if (polygon->isVisible()) {
            view.transform(polygon);
            view.drawNewPolygon(polygon, polygon->fill());
          }
          break;
        }
        case CURVE: { // TODO Fix visibility
          Curve* curve = static_cast<Curve*>(element);

          clipping.curveClipping(curve);
          if (curve->isVisible()) {
            view.transform(curve);
            view.drawNewCurve(curve);
          }
          break;
        }
        case OBJECT3D: { // TODO Fix visibility
          Object3D* obj3D = static_cast<Object3D*>(element);

          vector<Segment*> segments = obj3D->getSegmentList();
          vector<Segment*>::iterator segment;
          for(segment = segments.begin(); segment != segments.end(); segment++) {
              vector<Coordinate*> tmp = (*segment)->getCoordinates();
              (*segment)->setVisibility(clipping.lineClipping(tmp, 1));
          }

          view.transform(obj3D);
          view.drawNewObject3D(obj3D);

          break;
        }
        case SURFACE: {
          Surface* surface = static_cast<Surface*>(element);
          vector<Curve*> curves = surface->getCurves();
          vector<Curve*>::iterator c;
          for(c = curves.begin(); c != curves.end(); ++c) {
              clipping.curveClipping(*c);
              view.transform(*c);
              view.drawNewCurve(*c);
          }
          break;
        }
      }
      nextElement = nextElement->getProximo();
    }
    view.drawViewPortArea();
  }

};

#endif
