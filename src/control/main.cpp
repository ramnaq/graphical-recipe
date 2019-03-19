#include <gtk/gtk.h>

static cairo_surface_t *surface = NULL;

static void clear_surface ()
{
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

GtkWidget       *drawAreaViewPort;
int x_in = 300;
int y_in = 200;
int x_fi = 200;
int y_fi = 100;

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

int main(int argc, char *argv[])
{
    GtkBuilder      *builder;
    GtkWidget       *window;
    GtkWidget       *btnIn;
    GtkWidget       *btnOut;
    GtkWidget       *btnDir;
    GtkWidget       *btnEsq;
    GtkWidget       *btnCima;
    GtkWidget       *btnBaixo;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "src/view/windows.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "mainWindow"));
    gtk_builder_connect_signals(builder, NULL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    drawAreaViewPort = GTK_WIDGET(gtk_builder_get_object(builder, "drawAreaViewPort"));
    g_signal_connect(drawAreaViewPort, "draw", G_CALLBACK(draw), NULL);
    g_signal_connect(drawAreaViewPort, "configure-event", G_CALLBACK(create_surface), NULL);

    btnIn = GTK_WIDGET(gtk_builder_get_object(builder, "btnZooIn"));
    btnOut = GTK_WIDGET(gtk_builder_get_object(builder, "btnZoomOut"));
    btnDir = GTK_WIDGET(gtk_builder_get_object(builder, "btnDireita"));
    btnEsq = GTK_WIDGET(gtk_builder_get_object(builder, "btnEsquerda"));
    btnCima = GTK_WIDGET(gtk_builder_get_object(builder, "btnBaixo"));
    btnBaixo = GTK_WIDGET(gtk_builder_get_object(builder, "btnCima"));

    g_object_unref(G_OBJECT(builder));

    gtk_widget_show(window);
    gtk_main();

    return 0;
}
