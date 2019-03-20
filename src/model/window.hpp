#ifndef WINDOW_HPP
#define WINDOW_HPP

class Window {
  public:
	Window(Point origin, double weight, double height):
		origin_(origin), weight_(weight), height_(height) {}
	
  protected:
	Point origin_ = DEFAULT_ORIGIN;
	double weight_ = DEFAULT_SIZE;
	double height_ = DEFAULT_SIZE;

  private:
	static const auto DEFAULT_ORIGIN = new Point(0, 0);
	static const auto DEFAULT_SIZE = 10u;
	
};
