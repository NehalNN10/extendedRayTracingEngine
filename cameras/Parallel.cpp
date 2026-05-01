#include "Parallel.hpp"
#include "Camera.hpp"
#include "../utilities/Vector3D.hpp"
#include "../utilities/Point3D.hpp"

Parallel::Parallel() : dir(0.0f, 0.0f, -1.0f) {}

Parallel::Parallel(float c) : dir(c, c, c) {
    dir.normalize();
}
Parallel::Parallel(float x, float y, float z) : dir(Vector3D(x, y, z)) {
    dir.normalize();
}

Parallel::Parallel(const Vector3D &direction) : dir(direction) {
    dir.normalize(); 
}

Parallel::Parallel(const Parallel &other) : Camera(other), dir(other.dir) {}

Parallel& Parallel::operator=(const Parallel &other) {
    if (this == &other)
    {
        return *this;
    }
    // best practice to call overloaded operator
    Camera::operator=(other);
    dir = other.dir;
    return *this;
}

Vector3D Parallel::get_direction(const Point3D &p) const {
    return dir;
}