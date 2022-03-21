#include "hittable.h"

#include <math.h>

/**
 * @brief Create a new triangle
 * 
 * @param _a Vertex A
 * @param _b Vertex B
 * @param _c Vertex C
 * @return triangle_t Created triangle 
 */
triangle_t new_triangle(vector_t _a, vector_t _b, vector_t _c, colour_t _colour) {
  triangle_t out;
  out.a = _a;
  out.b = _b;
  out.c = _c;
  out.colour = _colour;
  return out;
}

/**
 * @brief Returns a hit record of a ray and a sphere
 * 
 * @param triangle Triangle 
 * @param origin Ray origin
 * @param direction Ray direction
 * @return hit_record_t Resulting hit record (if hit_record.hit == false, then other data members are invalid)
 */
hit_record_t check_hit_triangle(triangle_t* triangle, vector_t origin, vector_t direction) {
  hit_record_t out;
  out.hit = false;
  return out;
}

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
hit_record_t check_hit_sphere(sphere_t* sphere, vector_t origin, vector_t direction) {
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

/**
 * @brief check_hit is the function called by the main render function. It calls the appropriate function
 *        based on the type of the hittable object
 *
 * @param hittable hittable object to unwrap to check for hit with the ray
 * @param origin ray origin
 * @param direction ray direction
 * @return hit_record_t 
 */
hit_record_t check_hit(hittable_t hittable, vector_t origin, vector_t direction) {
  hit_record_t out;
  switch (hittable.type) {
    case TRIANGLE:
      out = check_hit_triangle(&hittable.obj.triangle, origin, direction);
      break;
    case SPHERE:
      out = check_hit_sphere(&hittable.obj.sphere, origin, direction);
      break;
  }
  return out;
}