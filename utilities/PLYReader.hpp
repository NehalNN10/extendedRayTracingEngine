#pragma once

#include <string>

class World;
class Material;
class Vector3D;

class PLYReader {
public:
    static void load_ply(const std::string& filename, World* world, Material* mat, float scale, const Vector3D& offset, double rotate_y_degrees = 0.0);
};