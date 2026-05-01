#include "ShadeInfo.hpp"
#include "Constants.hpp"

// set default values for a ray that hasn't hit anything yet
ShadeInfo::ShadeInfo(const World &wr)
    : hit(false),
      material_ptr(nullptr),
      hit_point(),
      normal(),
      ray(),
      depth(0),
      t(0.0f),
      w(&wr)
{}