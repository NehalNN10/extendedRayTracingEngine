#include "Shadow.hpp"
#include "../world/World.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../utilities/Ray.hpp"
#include "../materials/Material.hpp"
#include "../lights/Light.hpp" 

RGBColor Shadow::trace_ray(const Ray& ray, int depth) const {
    // Check recursion depth limit
    if (depth > world_ptr->max_depth) {
        return RGBColor(0.0f, 0.0f, 0.0f);  // black
    }
    
    ShadeInfo sr = world_ptr->hit_objects(ray);
    sr.depth = depth;
    sr.ray = ray;
    
    if (sr.hit) {
        // --- FIX 1: INVERTED NORMALS ---
        // If the normal points in the same direction as the camera ray, flip it outward!
        if (sr.normal * ray.d > 0.0) {
            sr.normal = -sr.normal;
        }

        RGBColor final_color(0.0);

        // Loop through all lights
        for (Light* light : world_ptr->lights) {
            
            Vector3D wi = light->get_direction(sr.hit_point);
            float ndotwi = sr.normal * wi; 

            if (ndotwi > 0.0) {
                
                bool in_shadow = false;
                double d = light->get_distance(sr.hit_point);

                // --- FIX 2: SHADOW ACNE ---
                // Replace kEpsilon with a massive offset so it completely clears the 800x scaled triangles
                float shadow_offset = 2.0f; 
                Ray shadow_ray(sr.hit_point + sr.normal * shadow_offset, wi);
                
                ShadeInfo shadow_sr = world_ptr->hit_objects(shadow_ray);

                // Check if the ray hit something AND that something is closer than the light
                if (shadow_sr.hit && shadow_sr.t < d) {
                    in_shadow = true;
                }

                if (!in_shadow) {
                    final_color += sr.material_ptr->shade(sr) * light->get_color() * ndotwi; 
                }
            }
        }
        
        return final_color;

    } else {
        return world_ptr->bg_color;
    }
}