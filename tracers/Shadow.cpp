#include "Shadow.hpp"
#include "../world/World.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../materials/Material.hpp"
#include "../lights/Light.hpp"

Shadow::Shadow(World* w_ptr) : Tracer(w_ptr) {}

RGBColor Shadow::trace_ray(const Ray& ray) const {
    // primary ray from camera to hit point
    ShadeInfo sr = world_ptr->hit_objects(ray);
    
    if (sr.hit) {
        // black shadow
        RGBColor final_color = RGBColor(0.0);

        for (Light* light : world_ptr->lights) {
            
            // Get the direction TO the light from the hit point
            Vector3D wi = light->get_direction(sr);
            
            // Calculate the cosine of the angle between the normal and the light direction
            float ndotwi = sr.normal * wi; 

            // Only process the light if it is hitting the front of the surface
            if (ndotwi > 0.0) {
                
                // --- THE SHADOW CHECK ---
                bool in_shadow = false;

                // Create a secondary ray starting at the hit point, pointing at the light.
                // We add a tiny offset (kEpsilon) along the normal to prevent "shadow acne" 
                // where the ray accidentally hits the surface it just started from.
                Ray shadow_ray(sr.hit_point + sr.normal * kEpsilon, wi);

                // Ask the world if this shadow ray hits anything on its way to the light
                ShadeInfo shadow_sr = world_ptr->hit_objects(shadow_ray);

                if (shadow_sr.hit) {
                    // We hit something! The point is in shadow for this specific light.
                    in_shadow = true;
                }

                // If not in shadow, add the color contribution from this light
                if (!in_shadow) {
                    // Ask the material how it should look under this light
                    final_color += sr.material_ptr->shade(sr) * light->L(sr) * ndotwi; 
                }
            }
        }
        
        return final_color;

    } else {
        // 4. We missed everything, return the background color
        return world_ptr->bg_color;
    }
}