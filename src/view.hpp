#include <gtk/gtk.h>
#include <string>

#include "drawer.hpp"

#ifndef VIEW_HPP
#define VIEW_HPP

using namespace std;

class View {

private:
  GtkBuilder *builder;

  GtkWidget *window;
  GtkWidget *newObjectWindow;
  GtkWidget *drawAreaViewPort;

  GtkEntry *entryPontoX;
  GtkEntry *entryPontoY;
  GtkEntry *objectName;

  GtkListBox *listObjects;

  Drawer* drawer;
public:
  View() {
    drawer = new Drawer();
  }

  void initializeWindow(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "windows.glade", NULL); // TODO ATUALIZAR LOCAL DIRETORIO

    window = GTK_WIDGET(gtk_builder_get_object(builder, "mainWindow"));
    newObjectWindow = GTK_WIDGET(gtk_builder_get_object(builder, "windowInserirCoord"));
    drawAreaViewPort = GTK_WIDGET(gtk_builder_get_object(builder, "drawAreaViewPort"));

    entryPontoX = GTK_ENTRY(gtk_builder_get_object(builder, "entryPontoX"));
    entryPontoY = GTK_ENTRY(gtk_builder_get_object(builder, "entryPontoY"));
    objectName = GTK_ENTRY(gtk_builder_get_object(builder, "entryNovoObjeto"));

    listObjects = GTK_LIST_BOX(gtk_builder_get_object(builder, "listaObjetos"));

    gtk_builder_connect_signals(builder, NULL);
    g_object_unref(G_OBJECT(builder));
    gtk_widget_show(window);
    gtk_main();
  }

  ~View() {}

  void create_surface(GtkWidget *widget) {
    drawer->create_surface(widget);
  }

  void draw(cairo_t *cr) {
    drawer->draw(cr);
  }

  void openNewObjectWindow() {
    gtk_widget_show(newObjectWindow);
  }

  void insertList(GraphicObject* obj) {
    string name = "Teste";

    GtkWidget* row = gtk_list_box_row_new();
    GtkWidget* label = gtk_label_new(name.c_str());

    gtk_container_add((GtkContainer*) listObjects, label);
    gtk_widget_show_all((GtkWidget*) listObjects);
  }

  void drawNewObject(GraphicObject* obj) {
    drawer->drawObject(obj->getCoordenada());
    gtk_widget_queue_draw((GtkWidget*) drawAreaViewPort);
  }

  // Gets
  double getEntryPontoX() {
    return stod(gtk_entry_get_text(entryPontoX));
  }

  double getEntryPontoY() {
    return stod(gtk_entry_get_text(entryPontoY));
  }

  string getObjectName() {
    return gtk_entry_get_text(objectName);
  }
};

#endif
