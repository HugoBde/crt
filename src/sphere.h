#ifndef SPHERE_H
#define SPHERE_H

#include "colour.h"
#include "hit_record.h"
#include "vector.h"

/**
 * @brief Represents a single sphere
 *
 */
typedef struct {
  float radius;
  vector_t center;
  colour_t colour;
} sphere_t;

/**
 * @brief Create a new sphere
 * 
 * @param _radius Sphere radius
 * @param _center Sphere center
 * @param _colour Sphere colour
 * @return sphere_t Created sphere 
 */
sphere_t new_sphere(float _radius, vector_t _center, colour_t _colour);

/**
 * @brief Returns a hit record of a ray and a sphere
 * 
 * @param sphere Sphere
 * @param origin Ray origin
 * @param direction Ray direction (does not need to be normalized)
 * @return hit_record_t Resulting hit record (can be invalid aka hit_record.hit = false)
 */
hit_record_t check_hit(sphere_t sphere, vector_t origin, vector_t direction);

#endif