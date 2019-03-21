#include <math.h>
#include "graphicObject.hpp"

#ifndef DRAWER_HPP
#define DRAWER_HPP

static cairo_surface_t *surface = NULL;

class Drawer {
private:

public:
	Drawer() {}
	~Drawer() {}

  void clear_surface () {
    cairo_t *cr = cairo_create (surface);

    cairo_set_source_rgb (cr, 1, 1, 1);
    cairo_paint (cr);

    cairo_destroy (cr);
  }

  void create_surface(GtkWidget* widget) {
    if (surface)
      cairo_surface_destroy(surface);

    surface = gdk_window_create_similar_surface(gtk_widget_get_window(widget),
                CAIRO_CONTENT_COLOR, gtk_widget_get_allocated_width(widget)-10,
                gtk_widget_get_allocated_height(widget)-10);
    clear_surface();
  }

  void draw(cairo_t *cr) {
		cairo_set_source_surface(cr, surface, 0, 0);
	  cairo_paint(cr);
  }

	void drawPoint(Coordenada* coord) {
		cairo_t *c = cairo_create (surface);

		cairo_move_to(c, coord->getX(), coord->getY());
		cairo_arc(c,coord->getX(), coord->getY(), 1.0, 0.0, 2*M_PI);
		cairo_fill(c);

		cairo_stroke(c);
	}

	void drawLine(Coordenada* coordIn, Coordenada* coordFin) {
		cairo_t *cr = cairo_create (surface);

		cairo_move_to(cr, coordIn->getX(), coordIn->getY());
	  cairo_line_to(cr, coordFin->getX(), coordFin->getY());
	  cairo_stroke(cr);

		cairo_stroke(cr);
	}

};

#endif
