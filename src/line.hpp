#ifndef LINE_HPP
#define LINE_HPP

class Line {
private:
  Ponto a;
  Ponto b;
public:
	Line(Coordernada a, Coordenada b) {
    a(a.x, a.y);
    b(b.x, b.y);
  }

	virtual ~Line() {}

};
