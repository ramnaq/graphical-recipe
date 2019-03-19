#include <gtk/gtk.h>

static cairo_surface_t *surface = NULL;

GtkWidget *drawAreaViewPort;
int x_in = 300;
int y_in = 200;
int x_fi = 200;
int y_fi = 100;


static void clear_surface () {
  cairo_t *cr;

  cr = cairo_create (surface);

  cairo_set_source_rgb (cr, 1, 1, 1);
  cairo_paint (cr);

  cairo_destroy (cr);
}

static gboolean draw(GtkWidget *widget, cairo_t *cr, gpointer data) {
  cairo_set_source_surface(cr, surface, 0, 0);
  cairo_paint(cr);
  return FALSE;
}

static gboolean create_surface(GtkWidget *widget, GdkEventConfigure *event, gpointer data) {
  if (surface)
    cairo_surface_destroy(surface);

  surface = gdk_window_create_similar_surface(gtk_widget_get_window(widget),
              CAIRO_CONTENT_COLOR, gtk_widget_get_allocated_width(widget),
              gtk_widget_get_allocated_height(widget));
  clear_surface();
  return TRUE;
}

extern "C" G_MODULE_EXPORT void on_btn_clicked_in(){
  cairo_t *cr;

  x_in += 20;
  y_in += 20;
  x_fi -= 15;
  y_fi -= 15;
  clear_surface();
  cr = cairo_create (surface);
  cairo_move_to(cr, x_in, y_in);
  cairo_line_to(cr, x_fi, y_fi);
  cairo_stroke(cr);

  gtk_widget_queue_draw(drawAreaViewPort);
}

extern "C" G_MODULE_EXPORT void on_btn_clicked_out(){
  cairo_t *cr;

  x_in -= 20;
  y_in -= 20;
  x_fi += 15;
  y_fi += 15;

  clear_surface();

  cr = cairo_create (surface);
  cairo_move_to(cr, x_in, y_in);
  cairo_line_to(cr, x_fi, y_fi);
  cairo_stroke(cr);

  gtk_widget_queue_draw(drawAreaViewPort);
}


extern "C" G_MODULE_EXPORT void on_btn_clicked_dir(){
  cairo_t *cr;

  x_in -= 20;
  x_fi -= 20;

  clear_surface();

  cr = cairo_create (surface);
  cairo_move_to(cr, x_in, y_in);
  cairo_line_to(cr, x_fi, y_fi);
  cairo_stroke(cr);

  gtk_widget_queue_draw(drawAreaViewPort);
}

extern "C" G_MODULE_EXPORT void on_btn_clicked_esq(){
  cairo_t *cr;

  x_in += 20;
  x_fi += 20;

  clear_surface();

  cr = cairo_create (surface);
  cairo_move_to(cr, x_in, y_in);
  cairo_line_to(cr, x_fi, y_fi);
  cairo_stroke(cr);

  gtk_widget_queue_draw(drawAreaViewPort);
}

extern "C" G_MODULE_EXPORT void on_btn_clicked_cima(){
  cairo_t *cr;

  y_in -= 20;
  y_fi -= 20;

  clear_surface();

  cr = cairo_create (surface);
  cairo_move_to(cr, x_in, y_in);
  cairo_line_to(cr, x_fi, y_fi);
  cairo_stroke(cr);

  gtk_widget_queue_draw(drawAreaViewPort);
}


extern "C" G_MODULE_EXPORT void on_btn_clicked_baixo(){
  cairo_t *cr;

  y_in += 20;
  y_fi += 20;

  clear_surface();

  cr = cairo_create (surface);
  cairo_move_to(cr, x_in, y_in);
  cairo_line_to(cr, x_fi, y_fi);
  cairo_stroke(cr);

  gtk_widget_queue_draw(drawAreaViewPort);
}


