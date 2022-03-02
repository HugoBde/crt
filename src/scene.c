#include "scene.h"

#include <errno.h>
#include <stdlib.h>

#include "utils.h"

/**
 * @brief Reads config file to initialise scene_t struct
 *
 * @param config_file Pointer to opened config file to read
 * @param scene Pointer to scene_t struct to initialise
 */
void parse_config(FILE* config_file, scene_t* scene) {
  fscanf(config_file, "%d", &scene->nb_sphere);
  // printf("Config:\nnumber of spheres in scene: %d\n", scene->nb_sphere);

  scene->spheres = (sphere_t*)malloc(sizeof(sphere_t) * scene->nb_sphere);
  if (scene->spheres == NULL) {
    print_error("failed to allocate memory for the scene");
    errno = 1;
  }

  for (int i = 0; i < scene->nb_sphere; i++) {
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