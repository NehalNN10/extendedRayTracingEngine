#include "PLYReader.hpp"
#include "../geometry/Triangle.hpp"
#include "../utilities/Point3D.hpp"
#include "../utilities/Vector3D.hpp"
#include "../materials/Material.hpp"
#include "../world/World.hpp"

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

void PLYReader::load_ply(const std::string& filename, World* world, Material* mat, float scale, const Vector3D& offset) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error! Cannot open PLY file: " << filename << "\n";
        return;
    }

    std::string line;
    int num_vertices = 0;
    int num_faces = 0;

    // 1. Parse the PLY Header
    while (std::getline(file, line)) {
        if (line.find("element vertex") != std::string::npos) {
            std::istringstream iss(line);
            std::string s1, s2;
            iss >> s1 >> s2 >> num_vertices;
        } else if (line.find("element face") != std::string::npos) {
            std::istringstream iss(line);
            std::string s1, s2;
            iss >> s1 >> s2 >> num_faces;
        } else if (line == "end_header") {
            break;
        }
    }

    std::vector<Point3D> vertices;
    vertices.reserve(num_vertices);

    // 2. Read the Vertices
    for (int i = 0; i < num_vertices; ++i) {
        std::getline(file, line);
        std::istringstream iss(line);
        float x, y, z;
        iss >> x >> y >> z;
        
        // Apply scaling and translation
        Point3D p(x * scale + offset.x, y * scale + offset.y, z * scale + offset.z);
        vertices.push_back(p);
    }

    // 3. Read the Faces (Triangles) and add them to the World
    for (int i = 0; i < num_faces; ++i) {
        std::getline(file, line);
        std::istringstream iss(line);
        int vertex_count, v0, v1, v2;
        
        iss >> vertex_count >> v0 >> v1 >> v2;
        
        // Ensure it's actually a triangle (3 vertices)
        if (vertex_count == 3) {
            Triangle* tri = new Triangle(vertices[v0], vertices[v2], vertices[v1]);
            tri->set_material(mat);
            world->add_geometry(tri);
        }
    }

    std::cout << "Successfully loaded " << num_faces << " triangles from " << filename << "\n";
}