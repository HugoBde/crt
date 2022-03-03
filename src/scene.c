#include "scene.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "colour.h"
#include "utils.h"
#include "vector.h"

/**
 * @brief Reads config file to initialise scene_t struct
 *
 * @param config_file Pointer to opened config file to read
 * @param scene Pointer to scene_t struct to initialise
 */
void parse_config(FILE* config_file, scene_t* scene) {
  fscanf(config_file, "%s", scene->filename);

  fscanf(config_file, "%d", &scene->width);
  fscanf(config_file, "%d", &scene->height);

  scene->buffer = (colour_t*) malloc(sizeof(colour_t) * scene->width * scene->height);

  if (scene->buffer == NULL) {
    print_error("failed to allocate memory for image buffer");
    errno = 1;
  }

  fscanf(config_file, "%d", &scene->nb_sphere);

  scene->spheres = (sphere_t*)malloc(sizeof(sphere_t) * scene->nb_sphere);
  
  if (scene->spheres == NULL) {
    print_error("failed to allocate memory for the scene");
    errno = 1;
  }

  for (int i = 0; i < scene->nb_sphere; i++) {
    sphere_t* curr = scene->spheres + i;
    fscanf(config_file, "%f %f %f %f %d %d %d", &curr->radius, &curr->center.x, &curr->center.y, &curr->center.z, (int*)&curr->colour.r, (int*)&curr->colour.g, (int*)&curr->colour.b);
  }

  printf("Output file: %s\nImage size: %dx%d\nNumber of spheres: %d\n", scene->filename, scene->width, scene->height, scene->nb_sphere);
  for (int i = 0; i < scene->nb_sphere; i++) {
    printf("Sphere %d:\n\tRadius: %.2f\n\tCenter: [%.2f, %.2f, %.2f]\n\tColour: (%d, %d, %d)\n\n", i, scene->spheres[i].radius, scene->spheres[i].center.x, scene->spheres[i].center.y, scene->spheres[i].center.z, scene->spheres[i].colour.r, scene->spheres[i].colour.g, scene->spheres[i].colour.b);
  }
}

/**
 * @brief Cleans up dynamically allocated memory
 *
 * @param scene Pointer to scene struct to clean up
 */
void scene_cleanup(scene_t* scene) {
  free(scene->spheres);
}