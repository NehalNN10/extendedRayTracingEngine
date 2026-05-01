#include "Sphere.hpp"
#include "Geometry.hpp"
#include "../utilities/BBox.hpp"
#include "../utilities/Point3D.hpp"
#include "../utilities/Vector3D.hpp"
#include "../utilities/Ray.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../utilities/Constants.hpp"
#include <cmath>
#include <string>

Sphere::Sphere() : c(Point3D(0, 0, 0)), r(0.0f) {}

Sphere::Sphere(const Point3D &center, float radius) : c(center), r(radius) {}

Sphere::Sphere(const Sphere &object) : Geometry(object), c(object.c), r(object.r) {}

Sphere &Sphere::operator=(const Sphere &rhs) {
    if (this == &rhs) {
        return *this;
    }
    // base class operator overload
    Geometry::operator=(rhs);
    c = rhs.c;
    r = rhs.r;
    return *this;
}

std::string Sphere::to_string() const {
    return "Sphere(" + c.to_string() + ", " + std::to_string(r) + ")";
}

BBox Sphere::getBBox() const {
    // must be a cube with side length 2r
    return BBox(Point3D(c.x - r, c.y - r, c.z - r), Point3D(c.x + r, c.y + r, c.z + r));
}

bool Sphere::hit(const Ray &ray, float &t, ShadeInfo &s) const {
    // (O + tD - C)^2 = r^2
    // solving this quadratic equation
    // replace O-C with temp to make things easier
    Vector3D temp = ray.o - c; // vector from sphere center to ray origin
    // (tD + V) * (tD + V) = r^2
    
    double a = ray.d * ray.d; 
    double b = 2.0 * (temp * ray.d);
    double c_val = (temp * temp) - (r * r); 
    
    // calculate discriminant i.e. b^2 - 4ac
    double discriminant = (b * b) - (4.0 * a * c_val);
    
    // if negative, no real roots => ray missed
    if (discriminant < 0.0) {
        return false;
    }
    
    // find the roots
    double e = std::sqrt(discriminant);
    double denom = 2.0 * a;
    
    // check smaller root first
    t = (-b - e) / denom;
    if (t > kEpsilon) { // if infront of camera then it's a hit
        s.t = t;
        s.normal = (temp + ray.d * t) / r; // normal points out from center
        s.hit_point = ray.o + ray.d * t;
        s.material_ptr = material_ptr;
        return true;
    }
    
    // condition for points inside sphere
    t = (-b + e) / denom;
    if (t > kEpsilon) {
        s.t = t;
        s.normal = (temp + ray.d * t) / r;
        s.hit_point = ray.o + ray.d * t;
        s.material_ptr = material_ptr;
        return true;
    }
    
    return false;
}