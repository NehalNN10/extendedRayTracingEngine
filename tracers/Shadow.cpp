#include "Shadow.hpp"
#include "../world/World.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../utilities/Ray.hpp"
#include "../materials/Material.hpp"

RGBColor Shadow::trace_ray(const Ray& ray, int depth) const {
    // Check recursion depth limit
    if (depth > world_ptr->max_depth) {
        return RGBColor(0.0f, 0.0f, 0.0f);  // black
    }
    
    ShadeInfo sr = world_ptr->hit_objects(ray);
    sr.depth = depth;
    sr.ray = ray;
    
    if (sr.hit) {
        return sr.material_ptr->shade(sr);
    } else {
        return world_ptr->bg_color;
    }
}
