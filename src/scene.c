#include "scene.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "colour.h"
#include "hittable.h"
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

  scene->buffer = (colour_t*)malloc(sizeof(colour_t) * scene->width * scene->height);

  if (scene->buffer == NULL) {
    print_error("failed to allocate memory for image buffer");
    errno = 1;
    return;
  }

  fscanf(config_file, "%d", &scene->nb_hittables);

  scene->hittables = (hittable_t*)malloc(sizeof(hittable_t) * scene->nb_hittables);

  if (scene->hittables == NULL) {
    print_error("failed to allocate memory for the scene");
    errno = 1;
    return;
  }

  for (int i = 0; i < scene->nb_hittables; i++) {
    hittable_t* curr = scene->hittables + i;
    char type;
    fscanf(config_file, "%c", &type);
    switch (type) {
      curr->type = TRIANGLE;
      fscanf(config_file, "%f %f %f %f %f %f %f %f %f %d %d %d", &curr->obj.triangle.a.x, &curr->obj.triangle.a.y, &curr->obj.triangle.a.z, &curr->obj.triangle.b.x, &curr->obj.triangle.b.y, &curr->obj.triangle.b.z, &curr->obj.triangle.c.x, &curr->obj.triangle.b.y, &curr->obj.triangle.b.z, (int*)&curr->obj.triangle.colour.r, (int*)&curr->obj.triangle.colour.g, (int*)&curr->obj.triangle.colour.b);
      break;
      case 'S':
      curr->type = SPHERE;
      fscanf(config_file, "%f %f %f %f %d %d %d", &curr->obj.sphere.radius, &curr->obj.sphere.center.x, &curr->obj.sphere.center.y, &curr->obj.sphere.center.z, (int*)&curr->obj.sphere.colour.r, (int*)&curr->obj.sphere.colour.g, (int*)&curr->obj.sphere.colour.b);
      break;
      case 'T':
      default:
      print_error("unknow object type");
      errno = 1;
      return;
    }
  }

  printf("Output file: %s\nImage size: %dx%d\nNumber of hittables: %d\n", scene->filename, scene->width, scene->height, scene->nb_hittables);
  for (int i = 0; i < scene->nb_hittables; i++) {
    hittable_t curr = scene->hittables[i];
    switch(curr.type) {
      case TRIANGLE:
      printf("Hittable %d: TRIANGLE\n\tA: [%.2f, %.2f, %.2f]\n\tB: [%.2f, %.2f, %.2f]\n\tC: [%.2f, %.2f, %.2f]\n\tColour: (%d, %d, %d)\n\n", i, scene->hittables[i].obj.triangle.a.x, scene->hittables[i].obj.triangle.a.y, scene->hittables[i].obj.triangle.a.z, scene->hittables[i].obj.triangle.b.x, scene->hittables[i].obj.triangle.b.y, scene->hittables[i].obj.triangle.b.z,scene->hittables[i].obj.triangle.c.x, scene->hittables[i].obj.triangle.c.y, scene->hittables[i].obj.triangle.c.z,scene->hittables[i].obj.triangle.colour.r, scene->hittables[i].obj.triangle.colour.g, scene->hittables[i].obj.triangle.colour.b);
      break;
      case SPHERE:
      printf("Hittable %d: SPHERE\n\tRadius: %.2f\n\tCenter: [%.2f, %.2f, %.2f]\n\tColour: (%d, %d, %d)\n\n", i, scene->hittables[i].obj.sphere.radius, scene->hittables[i].obj.sphere.center.x, scene->hittables[i].obj.sphere.center.y, scene->hittables[i].obj.sphere.center.z, scene->hittables[i].obj.sphere.colour.r, scene->hittables[i].obj.sphere.colour.g, scene->hittables[i].obj.sphere.colour.b);
      break;
    }
  }
}

/**
 * @brief Cleans up dynamically allocated memory
 *
 * @param scene Pointer to scene struct to clean up
 */
void scene_cleanup(scene_t* scene) {
  free(scene->hittables);
}