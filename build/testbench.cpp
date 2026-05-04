#include "../cameras/Parallel.hpp"
#include "../cameras/Perspective.hpp"

#include "../geometry/Plane.hpp"
#include "../geometry/Sphere.hpp"
#include "../geometry/Triangle.hpp"

#include "../materials/Matte.hpp"
#include "../materials/Phong.hpp"
#include "../materials/Reflective.hpp"

#include "../samplers/Simple.hpp"
#include "../samplers/Jittered.hpp"

#include "../lights/Light.hpp"
#include "../lights/PointLight.hpp"
#include "../lights/SpotLight.hpp"

#include "../tracers/Basic.hpp"
#include "../tracers/Shadow.hpp"

#include "../utilities/Constants.hpp"

#include "../acceleration/bvh.hpp"

#include "../world/World.hpp"
#include "../utilities/PLYReader.hpp"

#include <iostream>

// make a scene with a flat, reflective plane, and 3 spheres on top of it, one matte, one glossy, and one reflective. add a spotlight above the spheres pointing downwards. add toggle for jittered sampling. add toggle for BVH acceleration. add toggle for shadows.

void
World::build(void) 
{
  // toggles
  use_acceleration = true;
  bool use_jittering = true;
  int n = 4;
  bool use_shadows = true;

  // View plane  .
  vplane.top_left.x = -10;
  vplane.top_left.y = 10;
  vplane.top_left.z = 10;
  vplane.bottom_right.x = 10;
  vplane.bottom_right.y = -10;
  vplane.bottom_right.z = 10;
  vplane.hres = 400;
  vplane.vres = 400;

  // sampler

  // Background color.  
  bg_color = black;
  ambient_color = white;
  ambient_intensity = 0.2f;
  
  // Camera and sampler.
  set_camera(new Perspective(0, 0, 40));
  if (use_jittering) 
  {
      sampler_ptr = new Jittered(camera_ptr, &vplane, n);
  } 
  else {
      sampler_ptr = new Simple(camera_ptr, &vplane);
  }
	
  if (use_shadows) {
      tracer_ptr = new Shadow(this);
  } else {
      tracer_ptr = new Basic(this);
  }

  // sphere 1
  Sphere* sphere_ptr = new Sphere(Point3D(-5, 2, 0), 2); 
  sphere_ptr->set_material(new Matte(RGBColor(1.0f, 0.0f, 0.0f)));  // red
  add_geometry(sphere_ptr);

  // sphere 2
  Sphere* sphere_ptr2 = new Sphere(Point3D(5, 2, 0), 2); 
  sphere_ptr2->set_material(new Phong(0.25f, 0.75f, 0.5f, 32.0f, RGBColor(0.0f, 0.0f, 1.0f)));  // blue
  add_geometry(sphere_ptr2);

  // sphere 3
  Sphere* sphere_ptr3 = new Sphere(Point3D(0, 2, -3), 2); 
  sphere_ptr3->set_material(new Reflective(0.25f, 0.75f, 0.5f, 32.0f, 0.5f, RGBColor(1.0f, 1.0f, 1.0f))); // green
  add_geometry(sphere_ptr3);  

  // light
//   Light* spotlight_ptr = new SpotLight(Point3D(0, 5, 0), RGBColor(1.0f), 1.0, 0.0, 0.0, Vector3D(0, -1, 0), 60.0, 5.0); // white spotlight pointing downwards
//   spotlight_ptr->set_intensity(3.0f);
//   add_light(spotlight_ptr);

  Light* point_light_ptr = new PointLight(Point3D(0, 5, 0), RGBColor(1.0f), 1.0, 0.0, 0.0); // white point light
  point_light_ptr->set_intensity(3.0f);
  add_light(point_light_ptr);

  // plane
  Plane* plane_ptr = new Plane(Point3D(0,-0.5,0), Vector3D(0, 10, 2)); 
  plane_ptr->set_material(new Matte(RGBColor(0.5f, 0.2f, 0.1f)));  // brown
  add_geometry(plane_ptr);

  if (use_acceleration) 
  {
      bvh_ptr = new BVHNode(geometry, 0, geometry.size());
  }
}
