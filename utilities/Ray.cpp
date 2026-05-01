#include "Ray.hpp"
#include "Point3D.hpp"
#include "Vector3D.hpp"
#include <string>

Ray::Ray() : o(Point3D(0, 0, 0)), d(Vector3D(0, 0, 0)), w(1.0f) {}

Ray::Ray(const Point3D &origin, const Vector3D &dir): o(origin), d(dir), w(1.0f) {}

std::string Ray::to_string() const {
    return "Ray(" + o.to_string() + ", " + d.to_string() + ", " + std::to_string(w) + ")";
}