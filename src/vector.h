#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
  float x;
  float y;
  float z;
} vector_t;

/**
 * @brief Add two vectors together
 *
 * @param v Vector 1
 * @param u Vector 2
 * @return vector_t Sum of vector 1 and vector 2
 */
vector_t add(vector_t v, vector_t u);

/**
 * @brief Subtract two vectors together
 *
 * @param v Vector 1
 * @param u Vector 2
 * @return vector_t Difference of vector 1 and vector 2
 */
vector_t sub(vector_t v, vector_t u);

/**
 * @brief Multiply a vector by a factor k
 *
 * @param v Vector
 * @param k Factor
 * @return vector_t Product of V and K
 */
vector_t scalar_multiply(vector_t v, float k);

/**
 * @brief Dot product of two vectors
 *
 * @param v Vector 1
 * @param u Vector 2
 * @return float Dot product of vector 1 and 2
 */
float dot_product(vector_t v, vector_t u);

/**
 * @brief Cross product of two vectors
 *
 * @param v Vector 1
 * @param u Vector 2
 * @return vector_t Cross product of vector 1 and vector 2
 */
vector_t cross_product(vector_t v, vector_t u);

/**
 * @brief Magnitude of a vector
 *
 * @param v Vector 1
 * @return float Magnitude of vector 1
 */
float magnitude(vector_t v);

/**
 * @brief Turn a vector into a unit vector
 *
 * @param vec Vector to normalize
 */
void normalize(vector_t* vec);

#endif