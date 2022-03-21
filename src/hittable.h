#ifndef HITTABLE_H
#define HITTABLE_H

#include "colour.h"
#include "hit_record.h"
#include "vector.h"

/**
 * @brief Represents a triangle.
 *        The outside face of the triangle is the one such that
 *        the cross product of AB and AC point in the direction of that face
 *
 */
typedef struct {
  vector_t a;
  vector_t b;
  vector_t c;
  colour_t colour;
} triangle_t;

/**
 * @brief Create a new triangle
 *
 * @param _a Vertex A
 * @param _b Vertex B
 * @param _c Vertex C
 * @return triangle_t Created triangle
 */
triangle_t new_triangle(vector_t _a, vector_t _b, vector_t _c, colour_t _colour);

/**
 * @brief Returns a hit record of a ray and a sphere
 *
 * @param triangle Triangle
 * @param origin Ray origin
 * @param direction Ray direction
 * @return hit_record_t Resulting hit record (if hit_record.hit == false, then other data members are invalid)
 */
hit_record_t check_hit_triangle(triangle_t* triangle, vector_t origin, vector_t direction);

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
 * @return hit_record_t Resulting hit record (if hit_record.hit == false, then other data members are invalid)
 */
hit_record_t check_hit_sphere(sphere_t* sphere, vector_t origin, vector_t direction);

/**
 * @brief Types of possible hittable objects.
 *        It is used to determine which attribute to use in the hittable_object union,
 *       and which function to use to check for a hit
 *
 */
typedef enum {
  TRIANGLE,
  SPHERE
} hittable_type;

/**
 * @brief Union storing the actual hittable object
 *        The purpose of the union is to have a variable of constant size no matter what
 *        hittable object is wrapped inside hittable_t. This means that they can be neatly stored in an array
 *
 */
typedef union {
  triangle_t triangle;
  sphere_t sphere;
} hittable_object;

/**
 * @brief hittable_t wraps a hittable object (currently triangle_t and sphere_t) in a union
 *        and contains a hittable_type enum to determine the type of hittable object that is actually stored
 *
 */
typedef struct {
  hittable_type type;
  hittable_object obj;
} hittable_t;

/**
 * @brief check_hit is the function called by the main render function. It calls the appropriate function
 *        based on the type of the hittable object
 *
 * @param hittable hittable object to unwrap to check for hit with the ray
 * @param origin ray origin
 * @param direction ray direction
 * @return hit_record_t
 */
hit_record_t check_hit(hittable_t hittable, vector_t origin, vector_t direction);

#endif