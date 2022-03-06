#include "sphere.h"

#include <stdio.h>

#include "math.h"
#include "vector.h"

/**
 * @brief Create a new sphere
 *
 * @param _radius Sphere radius
 * @param _center Sphere center
 * @param _colour Sphere colour
 * @return sphere_t Created sphere
 */
sphere_t new_sphere(float _radius, vector_t _center, colour_t _colour) {
  sphere_t out;
  out.radius = _radius;
  out.center = _center;
  out.colour = _colour;
  return out;
}

/**
 * @brief Returns a hit record of a ray and a sphere
 *
 * @param sphere Sphere
 * @param origin Ray origin
 * @param direction Ray direction (does not need to be normalized)
 * @return hit_record_t Resulting hit record (can be invalid: hit_record.hit = false)
 */
hit_record_t check_hit(sphere_t* sphere, vector_t origin, vector_t direction) {
  hit_record_t out;

  normalize(&direction);
  vector_t oc                = sub(sphere->center, origin);
  float projected_distance   = dot_product(oc, direction);
  vector_t projected_vector  = scalar_multiply(direction, projected_distance);
  vector_t projecting_vector = sub(sphere->center, projected_vector);
  float squared_vector       = dot_product(projecting_vector, projecting_vector);
  if (squared_vector > powf(sphere->radius, 2)) {
    out.hit = false;
    return out;
  } else {
    out.hit      = true;
    float offset = sqrtf(powf(sphere->radius, 2) - squared_vector);
    if (projected_distance - offset < 0) {
      if (projected_distance + offset < 0) {
        out.hit = false;
        return out;
      } else {
        out.pos = add(origin, scalar_multiply(direction, projected_distance + offset));
      }
    } else {
      out.pos = add(origin, scalar_multiply(direction, projected_distance - offset));
    }
    vector_t normal = sub(out.pos, sphere->center);
    normalize(&normal);
    float shading_coefficient = (normal.y + 1.0f) / 2.0f;
    out.colour                = sphere->colour;
    out.colour.r *= shading_coefficient;
    out.colour.g *= shading_coefficient;
    out.colour.b *= shading_coefficient;
    return out;
  }
}