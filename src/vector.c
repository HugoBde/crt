#include "vector.h"

#include "math.h"

/**
 * @brief Add two vectors together
 * 
 * @param v Vector 1
 * @param u Vector 2
 * @return vector_t Sum of vector 1 and vector 2
 */
vector_t add(vector_t v, vector_t u) {
  vector_t out;
  out.x = v.x + u.x;
  out.y = v.y + u.y;
  out.z = v.z + u.z;  
  return out;
}

/**
 * @brief Subtract two vectors together
 * 
 * @param v Vector 1
 * @param u Vector 2
 * @return vector_t Difference of vector 1 and vector 2
 */
vector_t sub(vector_t v, vector_t u) {
  vector_t out;
  out.x = v.x - u.x;
  out.y = v.y - u.y;
  out.z = v.z - u.z;  
  return out;
}

/**
 * @brief Multiply a vector by a factor k
 * 
 * @param v Vector 
 * @param k Factor
 * @return vector_t Product of V and K 
 */
vector_t scalar_multiply(vector_t v, float k) {
  vector_t out;
  out.x = v.x * k;
  out.y = v.y * k;
  out.z = v.z * k;
  return out;
}

/**
 * @brief Dot product of two vectors
 * 
 * @param v Vector 1
 * @param u Vector 2
 * @return float Dot product of vector 1 and 2
 */
float dot_product(vector_t v, vector_t u) {
  return v.x * u.x + v.y * u.y + v.z * u.z;
}

/**
 * @brief Cross product of two vectors
 * 
 * @param v Vector 1
 * @param u Vector 2
 * @return vector_t Cross product of vector 1 and vector 2
 */
vector_t cross_product(vector_t v, vector_t u) {
  vector_t out;
  out.x = v.y * u.z - v.z * u.y;
  out.y = v.z * u.x - v.x * u.z;
  out.z = v.x * u.y - v.y * u.x;
  return out;
}

/**
 * @brief Magnitude of a vector
 * 
 * @param v Vector 1
 * @return float Magnitude of vector 1
 */
float magnitude(vector_t vec) {
  return sqrtf(powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2));
}

/**
 * @brief Turn a vector into a unit vector
 * 
 * @param vec Vector to normalize
 */
void normalize(vector_t* vec) {
  float mag = magnitude(*vec);
  vec->x /= mag;
  vec->y /= mag;
  vec->z /= mag;
}