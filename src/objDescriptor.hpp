#ifndef OBJDESCRIPTOR_HPP
#define OBJDESCRIPTOR_HPP

#include <fstream>
#include <sstream>
#include <vector>

#include "point.hpp"
#include "line.hpp"
#include "polygon.hpp"
#include "segment.hpp"
#include "object3D.hpp"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

class ObjDescriptor {
  public:
    void write(ListaEnc<GraphicObject*>* objs, string fileName) {
      std::ofstream outfile(fileName);
      for (int i = 0; i < objs->getSize(); ++i) {
        vector<Coordinate*> coordinates = static_cast<GraphicObject2D*>(objs->elementoNoIndice(i))->getCoordinates();

        /* vertex list of objs[i] */
        for (int c = 0; c < coordinates.size(); ++c) {
          Coordinate* coord = coordinates[c];
          outfile << "v "
            << coord->getX() << " "
            << coord->getY() << " "
            << coord->getZ() << '\n';
        }

        /* graphic element face */
        outfile << "f";
        for (int c = 0; c < coordinates.size(); ++c) {
          outfile << " " << (c + 1);
        }

        outfile << '\n';
      }

      outfile.close();
    }

    vector<GraphicObject*> read(string fileName) {
      std::string inputfile = fileName;
      tinyobj::attrib_t attrib;
      std::vector<tinyobj::shape_t> shapes_tiny;
      std::vector<tinyobj::material_t> materials;

      vector<Segment*> objectSegments;

      std::string err;
      bool ret = tinyobj::LoadObj(
      &attrib, &shapes_tiny, &materials, &err, inputfile.c_str());

      // `err` may contain warning message.
      if (!err.empty()) {
        std::cerr << err << std::endl;
      }

      if (!ret) {
        return {};
      }

      // Loop over shapes
      for (size_t s = 0; s < shapes_tiny.size(); s++) {
        const std::string shape_name = shapes_tiny[s].name;
        vector<Segment*> facesSegments;

        // Loop over faces(polygon)
        size_t index_offset = 0;
        for (size_t f = 0; f < shapes_tiny[s].mesh.num_face_vertices.size(); ++f) {
          int fv = shapes_tiny[s].mesh.num_face_vertices[f];

          std::vector<Segment*> segments;

          // Loop over vertices in the face.
          for (size_t v = 0; v < fv-1; v++) {
            // access to vertex
            tinyobj::index_t idx = shapes_tiny[s].mesh.indices[index_offset + v];
            tinyobj::real_t vx = attrib.vertices[3*idx.vertex_index+0];
            tinyobj::real_t vy = attrib.vertices[3*idx.vertex_index+1];
            tinyobj::real_t vz = attrib.vertices[3*idx.vertex_index+2];

            int aux = v + 1;
            tinyobj::index_t idx2 = shapes_tiny[s].mesh.indices[index_offset + aux];
            tinyobj::real_t vx2 = attrib.vertices[3*idx2.vertex_index+0];
            tinyobj::real_t vy2 = attrib.vertices[3*idx2.vertex_index+1];
            tinyobj::real_t vz2 = attrib.vertices[3*idx2.vertex_index+2];

            Coordinate* c1 = new Coordinate(vx, vy, vz);
            Coordinate* c2 = new Coordinate(vx2, vy2, vz2);
            segments.push_back(new Segment(c1, c2));
          }


          facesSegments.insert(
              facesSegments.end(), segments.begin(), segments.end());
          index_offset += fv;
        }

        objectSegments.insert(
            objectSegments.end(), facesSegments.begin(), facesSegments.end());
      }
      vector<GraphicObject*> objs;
      objs.push_back(new Object3D("", objectSegments));
      return objs;
    }

    /*
    vector<GraphicObject*> read(string fileName) {
      vector<GraphicObject*> objects;

      vector<Coordinate*> vertices;
      std::string c, line;
      double x, y, z;  //!< vertices (e.g `v 3.45 6 10` is a point/vertex in R³)
      bool readingFaces = false;  //!< used to detect a new vertix list.

      std::ifstream infile(fileName);
      while (infile >> c) {
        if (c == "v") {
            if (readingFaces) {
              vertices.clear();
              readingFaces = false;
            }
            infile >> x >> y >> z;
            vertices.push_back(new Coordinate(x, y, z));
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

      infile.close();

      return objects;
    }
    */

    GraphicObject* instantiateGraphicObject(vector<int> indexes,
		vector<Coordinate*> vertices) {
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
          gobject = new Polygon("", polygonPoints, false);
          break;
        }
      }

	  return gobject;
	}

};

#endif  //!< OBJDESCRIPTOR_HPP
