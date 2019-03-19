#pragma once
#include <gtk/gtk.h>

extern GtkWidget *drawAreaViewPort;

static void clear_surface();
static gboolean draw(GtkWidget *widget, cairo_t *cr, gpointer data);
static gboolean create_surface(GtkWidget *widget, GdkEventConfigure *event, gpointer data);

extern "C" G_MODULE_EXPORT void on_btn_clicked_in();
extern "C" G_MODULE_EXPORT void on_btn_clicked_out();
extern "C" G_MODULE_EXPORT void on_btn_clicked_dir();
extern "C" G_MODULE_EXPORT void on_btn_clicked_esq();
extern "C" G_MODULE_EXPORT void on_btn_clicked_cima();
extern "C" G_MODULE_EXPORT void on_btn_clicked_baixo();

