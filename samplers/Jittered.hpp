#pragma once

#include "Sampler.hpp"

class Jittered : public Sampler {
protected:
  float pixel_size_x;
  float pixel_size_y;
  int n; 
  float sub_pixel_size_x;
  float sub_pixel_size_y;

public:
  // Constructors.
  Jittered() = default;                      // initializes members to NULL.
  Jittered(Camera *c_ptr, ViewPlane *v_ptr, int n); // set members.

  // Copy constuctor and assignment operator.
  Jittered(const Jittered &camera);
  Jittered &operator=(const Jittered &other);

  // Desctructor.
  virtual ~Jittered() = default;

  // Shoot n^2 rays of weight 1/n^2
  std::vector<Ray> get_rays(int px, int py) const override;
};
