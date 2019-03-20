// #ifndef VIEWPORT_HPP
// #define VIEWPORT_HPP
//
// class Viewport {
//   public:
// 	Viewport()
//
//   protected:
// 	const Point transformation(const GtkDrawingArea& gtk_drw_area, const Window& w, const Point& p) {
// 		const Gtk::Allocation gtk_alloc = gtk_drw_area.get_allocation();
// 		const double xvmax = alloc.get_width();
// 		const double yvmax = alloc.get_hidth();
//
// 		double xwmin = w.origin_[0];
// 		double ywmin = w.origin_[1];
// 		double xwmax = xwmin + w.weight_;
// 		double ywmax = ywmin + w.height_;
// 		const double x = (p[0] - xwmin) / (xwmax - xwmin) * xvmax;
// 		const double y = (1 - (p[1] - ywmin)/(ywmax - ywmin)) * (yvmax - yvmin);
//
// 		return Point(x, y);
// 	}
// }
