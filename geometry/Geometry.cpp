#include "Geometry.hpp"
#include "../utilities/BBox.hpp"
#include "../utilities/Ray.hpp"
#include "../utilities/ShadeInfo.hpp"

Geometry::Geometry(): material_ptr(nullptr) {}

Material* Geometry::get_material() const {
    return material_ptr;
}

void Geometry::set_material(Material *mPtr)
{
    material_ptr = mPtr;
}