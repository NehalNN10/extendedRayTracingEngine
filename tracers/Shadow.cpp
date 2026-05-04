#include "Shadow.hpp"
#include "../world/World.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../utilities/Ray.hpp"
#include "../materials/Material.hpp"
#include "../lights/Light.hpp" 

Shadow::Shadow(World* w_ptr) : Tracer(w_ptr) {}

RGBColor Shadow::trace_ray(const Ray& ray, int depth) const {
    // Check recursion depth limit
    if (depth > world_ptr->max_depth) {
        return RGBColor(0.0f, 0.0f, 0.0f);  // black
    }
    
    ShadeInfo sr = world_ptr->hit_objects(ray);
    sr.depth = depth;
    sr.ray = ray;
    
    if (sr.hit) {
        RGBColor final_color(0.0);

        // 2. Loop through all lights your partner created
        for (Light* light : world_ptr->lights) {
            
            // FIX 1: Pass the specific hit_point, not the whole ShadeInfo
            Vector3D wi = light->get_direction(sr.hit_point);
            
            float ndotwi = sr.normal * wi; 

            if (ndotwi > 0.0) {
                
                bool in_shadow = false;
                
                // Ask your partner's code how far away the light is
                double d = light->get_distance(sr.hit_point);

                Ray shadow_ray(sr.hit_point + sr.normal * kEpsilon, wi);
                ShadeInfo shadow_sr = world_ptr->hit_objects(shadow_ray);

                // Check if the ray hit something AND that something is closer than the light
                if (shadow_sr.hit && shadow_sr.t < d) {
                    in_shadow = true;
                }

                if (!in_shadow) {
                    // FIX 2: Use get_color() instead of L()
                    final_color += sr.material_ptr->shade(sr) * light->get_color() * ndotwi; 
                }
            }
        }
        
        return final_color;

    } else {
        return world_ptr->bg_color;
    }
}
