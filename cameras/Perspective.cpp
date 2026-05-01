#include "Perspective.hpp"
#include "Camera.hpp"
#include "../utilities/Vector3D.hpp"
#include "../utilities/Point3D.hpp"

Perspective::Perspective() : pos(Point3D(0.0f, 0.0f, 0.0f)) {}

Perspective::Perspective(float c) : pos(Point3D(c, c, c)) {}
Perspective::Perspective(float x, float y, float z) : pos(Point3D(x, y, z)) {}

Perspective::Perspective(const Point3D &position) : pos(position) {}

// calling base class to create an instance
Perspective::Perspective(const Perspective &other) : Camera(other), pos(other.pos) {}

Perspective& Perspective::operator=(const Perspective &other) {
    if (this == &other)
    {
        return *this;
    }
    Camera::operator=(other);
    pos = other.pos;
    return *this;
}

Vector3D Perspective::get_direction(const Point3D &p) const {
    Vector3D direction = p - pos;
    direction.normalize();
    return direction;
}