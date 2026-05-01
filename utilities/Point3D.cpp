#include "Point3D.hpp"
#include "Vector3D.hpp"
#include <cmath>
#include <string>
#include <algorithm> // for std::min and std::max

Point3D::Point3D() : x(0.0f), y(0.0f), z(0.0f) {}

Point3D::Point3D(float c): x(c), y(c), z(c) {}

Point3D::Point3D(float x, float y, float z): x(x), y(y), z(z) {}

std::string Point3D::to_string() const {
    return "Point3D("
        + std::to_string(x) + ", "
        + std::to_string(y) + ", "
        + std::to_string(z) + 
    ")";
}

// unary minus
Point3D Point3D::operator-() const {
    return Point3D(-x, -y, -z);
}

Vector3D Point3D::operator-(const Point3D &p) const {
    return Vector3D(x - p.x, y - p.y, z - p.z);
}

Point3D Point3D::operator+(const Vector3D &v) const {
    return Point3D(x + v.x, y + v.y, z + v.z);
}

Point3D Point3D::operator-(const Vector3D &v) const {
    return Point3D(x - v.x, y - v.y, z - v.z);
}

// scale the point by a factor, s.
Point3D Point3D::operator*(const float s) const {
    return Point3D(x * s, y * s, z * s);
}

float Point3D::d_squared(const Point3D &p) const {
    return (x - p.x) * (x - p.x) + (y - p.y) * (y - p.y) + (z - p.z) * (z - p.z);
}
    
float Point3D::distance(const Point3D &p) const {
    return std::sqrt(d_squared(p));
}

Point3D operator*(const float a, const Point3D &pt) {
    return Point3D(a * pt.x, a * pt.y, a * pt.z);
}

Point3D min(const Point3D& a, const Point3D& b) {
    return Point3D(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
}

Point3D max(const Point3D& a, const Point3D& b) {
    return Point3D(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));
}