#ifndef SCENE_H
#define SCENE_H

#include <stdio.h>

#include "colour.h"
#include "hittable.h"

/**
 * @brief Stores all data related to the scene to render
 *
 */
typedef struct {
  int nb_hittables;
  hittable_t* hittables;
  int width;
  int height;
  char filename[128];
  colour_t* buffer;
} scene_t;

/**
 * @brief Reads config file to initialise scene_t struct
 *
 * @param config_file Pointer to opened config file to read
 * @param scene Pointer to scene_t struct to initialise
 * @return 0 on successful parse, anything else in case of an error
 */
int parse_config(FILE* config_file, scene_t* config);

/**
 * @brief Cleans up dynamically allocated memory
 *
 * @param scene Pointer to scene struct to clean up
 */
void scene_cleanup(scene_t* scene);

#endif