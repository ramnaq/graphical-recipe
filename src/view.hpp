#include <gtk/gtk.h>
#include <string>

#include "drawer.hpp"
#include "viewport.hpp"
#include "window.hpp"

#ifndef VIEW_HPP
#define VIEW_HPP

using namespace std;

class View {

private:
  GtkBuilder *builder;

  GtkWidget *gtkWindow;
  GtkWidget *addObjectWindow;
  GtkWidget *drawAreaViewPort;

  /*! Entries for parameters of GraphicalObjects to be futher created */
  GtkEntry *entryPontoX;
  GtkEntry *entryPontoY;
  GtkEntry *entryLineX1;
  GtkEntry *entryLineY1;
  GtkEntry *entryLineX2;
  GtkEntry *entryLineY2;
  GtkEntry *entryPolygonX;
  GtkEntry *entryPolygonY;
  GtkEntry *objectName;
  GtkEntry *entryPasso;

  GtkListBox *objectsListBox;    //!< shows the name of the objects drawn
  GtkListBox *listCoordPolygon;  //!< shows the coordinates added when creating a polygon

  GtkNotebook *notebookObjects;  //!< GtkNotebook to create different graphical objects (e.g Points, Polygons)

  Drawer* drawer;
  Window* window;
  ViewPort* viewPort;
public:
  View() {
    drawer = new Drawer();
  }

  //! Startup the user interface: initiates GTK, creates all graphical elements and runs gtk_main();
  void initializeGtkWindow(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "windows.glade", NULL);

    gtkWindow = GTK_WIDGET(gtk_builder_get_object(builder, "mainWindow"));
    addObjectWindow = GTK_WIDGET(gtk_builder_get_object(builder, "windowInserirCoord"));
    drawAreaViewPort = GTK_WIDGET(gtk_builder_get_object(builder, "drawAreaViewPort"));

    entryPontoX = GTK_ENTRY(gtk_builder_get_object(builder, "entryPontoX"));
    entryPontoY = GTK_ENTRY(gtk_builder_get_object(builder, "entryPontoY"));
    objectName = GTK_ENTRY(gtk_builder_get_object(builder, "entryNovoObjeto"));
    entryLineX1 = GTK_ENTRY(gtk_builder_get_object(builder, "entryRetaX"));
    entryLineY1 = GTK_ENTRY(gtk_builder_get_object(builder, "entryRetaY"));
    entryLineX2 = GTK_ENTRY(gtk_builder_get_object(builder, "entryRetaX1"));
    entryLineY2 = GTK_ENTRY(gtk_builder_get_object(builder, "entryRetaY1"));
    entryPolygonX = GTK_ENTRY(gtk_builder_get_object(builder, "entryPoligonoX"));
    entryPolygonY = GTK_ENTRY(gtk_builder_get_object(builder, "entryPoligonoY"));
    entryPasso = GTK_ENTRY(gtk_builder_get_object(builder, "inputPasso"));

    objectsListBox = GTK_LIST_BOX(gtk_builder_get_object(builder, "listaObjetos"));
    listCoordPolygon = GTK_LIST_BOX(gtk_builder_get_object(builder, "listbox2"));

    notebookObjects = GTK_NOTEBOOK(gtk_builder_get_object(GTK_BUILDER(builder), "notebookObjects"));

    gtk_builder_connect_signals(builder, NULL);
    g_object_unref(G_OBJECT(builder));
    gtk_widget_show(gtkWindow);
    gtk_main();
  }

  ~View() {}

  /**
   * Creates the two main structures responsible for drawing elements in the screen:
   * Window (window) and ViewPort (viewPort). Their sizes are based on
   * 'drawAreaViewPort' GtkWidget.
   */
  void initializeWindowViewPort() {
    double xMax = (double) gtk_widget_get_allocated_width(drawAreaViewPort);
    double yMax = (double) gtk_widget_get_allocated_height(drawAreaViewPort);
    window = new Window(1, 1, xMax, yMax);
    viewPort = new ViewPort(xMax, yMax, window);
  }

  void clear_surface() {
    drawer->clear_surface();
    gtk_widget_queue_draw((GtkWidget*) drawAreaViewPort);
  }

  void create_surface(GtkWidget *widget) {
    drawer->create_surface(widget);
  }

  void draw(cairo_t *cr) {
    drawer->draw(cr);
  }

  void openAddObjectWindow() {
    gtk_widget_show(addObjectWindow);
  }

  void drawNewPoint(GraphicObject* obj) {
    transform(obj);
    drawer->drawPoint(obj->getCoordinates().front());
    gtk_widget_queue_draw((GtkWidget*) drawAreaViewPort);
  }

  void drawNewLine(GraphicObject* obj) {
    transform(obj);
    drawer->drawLine(obj->getCoordinates().front(), obj->getCoordinates().back());
    gtk_widget_queue_draw((GtkWidget*) drawAreaViewPort);
  }

  void drawNewPolygon(GraphicObject* obj) {
    transform(obj);
    vector<Coordinate*> polygonPoints = obj->getCoordinates();
    vector<Coordinate*>::iterator it;
    for(it = polygonPoints.begin(); it != polygonPoints.end()-1; it++) {
        drawer->drawLine(*it , *(std::next(it,1)));
    }
    gtk_widget_queue_draw((GtkWidget*) drawAreaViewPort);
  }

  void insertIntoListBox(GraphicObject* obj, string tipo) {
    GtkWidget* row = gtk_list_box_row_new();
    GtkWidget* label = gtk_label_new((obj->getObjectName() + " (" + tipo + ")").c_str());

    gtk_container_add((GtkContainer*) objectsListBox, label);
    gtk_widget_show_all((GtkWidget*) objectsListBox);
  }

  //! Removes the selected element in GtkListBox
  /*!
   * @return The index of the removed element
   */
  int removeSelectedObject() {
    GtkListBoxRow* row = gtk_list_box_get_selected_row(objectsListBox);
    int index = gtk_list_box_row_get_index(row);

    gtk_container_remove((GtkContainer*) objectsListBox, (GtkWidget*) row);
    return index;
  }

  void insertCoordPolygonList() {
    string coordX = gtk_entry_get_text(entryPolygonX);
    string coordY = gtk_entry_get_text(entryPolygonY);
    string name = "Coordenada: (" + coordX + " , " + coordY + ")";

    GtkWidget* row = gtk_list_box_row_new();
    GtkWidget* label = gtk_label_new(name.c_str());

    gtk_container_add((GtkContainer*) listCoordPolygon, label);
    gtk_widget_show_all((GtkWidget*) listCoordPolygon);
  }

  int removeFromCoordPolygonList() {
    GtkListBoxRow* row = gtk_list_box_get_selected_row(listCoordPolygon);
    int index = gtk_list_box_row_get_index(row);

    gtk_container_remove((GtkContainer*) listCoordPolygon, (GtkWidget*) row);
    return index;
  }

  void updateWindow(double passo, int isZoomIn) {
    switch (isZoomIn) {
      case 0: {
        this->window->zoomIn(passo);
        break;
      } case 1: {
        this->window->zoomOut(passo);
        break;
      } case 2: {
        this->window->goRight(passo);
        break;
      } case 3: {
        this->window->goLeft(passo);
        break;
      } case 4: {
        this->window->goUp(passo);
        break;
      } case 5: {
        this->window->goDown(passo);
        break;
      } case 6: {
        this->window->goUpLeft(passo);
        break;
      } case 7: {
        this->window->goUpRight(passo);
        break;
      } case 8: {
        this->window->goDownLeft(passo);
        break;
      } case 9: {
        this->window->goDownRight(passo);
        break;
      }
    }
  }

  //! Calls ViewPort::transformation() depending on 'object's type
  /*!
   * @param object The GraphicObject that its coordinates will be transformed to
   * 	corresponding ViewPort coordinates.
   */
  void transform(GraphicObject *object) {
    switch (object->getType()) {
      case POINT: {
        viewPort->transformation(object->getCoordinates().front());
        break;
      }
      case LINE: {
        viewPort->transformation(object->getCoordinates().front());
        viewPort->transformation(object->getCoordinates().back());
        break;
      }
      case POLYGON: {
        vector<Coordinate*> polygonPoints = object->getCoordinates();
        vector<Coordinate*>::iterator it;
        for(it = polygonPoints.begin(); it != polygonPoints.end(); it++) {
            viewPort->transformation(*it);
        }
        break;
      }
    }
  }


  ///
  /// Get methods
  ///

  double getEntryPontoX() {
    return stod(gtk_entry_get_text(entryPontoX));
  }

  double getEntryPontoY() {
    return stod(gtk_entry_get_text(entryPontoY));
  }

  double getEntryLineX1() {
    return stod(gtk_entry_get_text(entryLineX1));
  }

  double getEntryLineY1() {
    return stod(gtk_entry_get_text(entryLineY1));
  }

  double getEntryLineX2() {
    return stod(gtk_entry_get_text(entryLineX2));
  }

  double getEntryLineY2() {
    return stod(gtk_entry_get_text(entryLineY2));
  }

  double getEntryPolygonX() {
    return stod(gtk_entry_get_text(entryPolygonX));
  }

  double getEntryPolygonY() {
    return stod(gtk_entry_get_text(entryPolygonY));
  }

  double getPasso() {
    return stod(gtk_entry_get_text(entryPasso));
  }

  string getObjectName() {
    return gtk_entry_get_text(objectName);
  }

  int getCurrentPage () {
    return gtk_notebook_get_current_page(notebookObjects);
  }

};

#endif

