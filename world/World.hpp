#pragma once

/**
   This file declares the World class which contains all the information about
   the scene - geometry and materials, lights, viewplane, camera, samplers, and
   acceleration structures.

   It also traces rays through the scene.

   Courtesy Kevin Suffern.
*/

#include <vector>

#include "../utilities/RGBColor.hpp"

#include "ViewPlane.hpp"
#include "../tracers/Tracer.hpp"

class Camera;
class Geometry;
class Ray;
class Sampler;
class ShadeInfo;
class Light;

class World {
public:
  ViewPlane vplane;
  int max_depth;
  RGBColor bg_color;
  std::vector<Geometry *> geometry;
  Camera *camera_ptr;
  Sampler *sampler_ptr;
  std::vector<Light *> lights;
  Tracer *tracer_ptr;
  Geometry *bvh_ptr;
  bool use_acceleration;

public:
  // Constructors.
  World(); // initialize members.
  World(ViewPlane vp, int md, RGBColor bg, Camera *c_ptr, Sampler *s_ptr, Tracer* t_ptr, Geometry* bvh, bool accel);

  // Destructor.
  ~World(); // free memory.

  // Add to the scene.
  void add_geometry(Geometry *geom_ptr);
  void add_light(Light *light_ptr);
  void set_camera(Camera *c_ptr);

  // Build scene - add all geometry, materials, lights, viewplane, camera,
  // samplers, and acceleration structures
  void build();

  // Returns appropriate shading information corresponding to intersection of
  // the ray with the scene geometry.
  ShadeInfo hit_objects(const Ray &ray) const;
};
