#ifndef DRAWER_HPP
#define DRAWER_HPP

#include <math.h>
#include "graphicObject.hpp"

static cairo_surface_t *surface = NULL;

class Drawer {
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

	void drawViewPortArea(Coordinate* vpcoord, int margin) {
		cairo_t *cr = cairo_create (surface);
		cairo_set_source_rgb (cr, 1, 0, 0);

		cairo_move_to(cr, margin, margin);
		cairo_line_to(cr, vpcoord->getX(), margin);
		cairo_line_to(cr, vpcoord->getX(), vpcoord->getY());
		cairo_line_to(cr, margin, vpcoord->getY());
		cairo_close_path(cr);

		cairo_stroke(cr);
	}

	void draw(cairo_t *cr) {
		cairo_set_source_surface(cr, surface, 0, 0);
	  cairo_paint(cr);
	}

	void drawPoint(Coordinate* coord) {
		cairo_t *c = cairo_create (surface);

		cairo_move_to(c, coord->getXvp(), coord->getYvp());
		cairo_arc(c, coord->getXvp(), coord->getYvp(), 1.0, 0.0, 2*M_PI);
		cairo_fill(c);

		cairo_stroke(c);
	}

	void drawLine(Coordinate* coordIn, Coordinate* coordFin) {
		cairo_t* crl = cairo_create (surface);

		cairo_move_to(crl, coordIn->getXvp(), coordIn->getYvp());
		cairo_line_to(crl, coordFin->getXvp(), coordFin->getYvp());
		cairo_stroke(crl);
	}

	void drawPolygon(vector<Coordinate*> polygonPoints, bool fill) {
		cairo_t* cr = cairo_create (surface);
		int end = polygonPoints.size();

		cairo_move_to(cr, polygonPoints[0]->getXvp(), polygonPoints[1]->getYvp());

		// Draws polygon's edges two by two points. The last edge is the segment
		// polygonPoints[end]|polygonPoints[0].
		for (int i = 0; i < end; i++) {
			cairo_line_to(cr, polygonPoints[i]->getXvp(), polygonPoints[(i+1) % end]->getYvp());
		}

		cairo_close_path(cr);
		cairo_stroke_preserve(cr);
		if (fill)
			cairo_fill(cr);
	}

};

#endif
