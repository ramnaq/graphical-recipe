#ifndef OBJDESCRIPTOR_HPP
#define OBJDESCRIPTOR_HPP

#include <vector>
#include <fstream>
#include <sstream>

#include "graphicObject.hpp"


class ObjDescriptor {
  public:
	void write(GraphicObject& obj) {
	}

    vector<GraphicObject*> read(string fileName) {
      vector<GraphicObject*> objects;

      vector<Coordinate*> vertices;
      std::string c, line;
      double x, y;  //!< vertices (e.g `v 3.45 6 10` is a point/vertex in R³)
      bool readingFaces = false;  //!< used to detect a new vertix list.

      std::ifstream infile(fileName);
      while (infile >> c) {
        if (c == "v") {
            if (readingFaces) {
              vertices.clear();
              readingFaces = false;
            }
            infile >> x >> y;
            vertices.push_back(new Coordinate(x, y));
        } else if (c == "f") {
            readingFaces = true;
            int i = 0;
            vector<int> vindexes;
            std::getline(infile, line);
            std::istringstream ssin(line);
            while (ssin.good()) {
              int k; ssin >> k;
              vindexes.push_back(k - 1);
              ++i;
            }
            objects.push_back(instantiateGraphicObject(vindexes, vertices));
        } else if (c == "#") {
            std::getline(infile, line);  //!< it's a commentary, ignore line.
        }
      }

      return objects;
    }

    GraphicObject* instantiateGraphicObject(vector<int> indexes, vector<Coordinate*> vertices) {
      GraphicObject* gobject;
      switch (indexes.size()) {
        case 0: {
          gobject = NULL;
          break;
        }
        case 1: {
          vector<Coordinate*> point;
          point.push_back(vertices.at(indexes[0]));
          gobject = new Point("", point);
          break;
        }
        case 2: {
          vector<Coordinate*> linePoints;
          linePoints.push_back(vertices.at(indexes[0]));
          linePoints.push_back(vertices.at(indexes[1]));
          gobject = new Line("", linePoints);
          break;
        }
        default: {
          vector<Coordinate*> polygonPoints;
          int m = indexes.size();
          int n = vertices.size();
          for (int i = 0; i < indexes.size(); ++i)
            polygonPoints.push_back(vertices.at(indexes[i]));
          gobject = new Polygon("", polygonPoints);
          break;
        }
      }

      return gobject;
    }

};

#endif  //!< OBJDESCRIPTOR_HPP

