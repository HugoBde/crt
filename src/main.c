/**
 * @file main.c
 * @author Hugo Bouderlique (bouderliqueh@gmail.com)
 * @brief Small real-time ray tracer made for demonstration purposes for Fundamentals of C Programming 48430 @ University of Technolgy Sydney
 * @version 0.1
 * @date 2022-03-01
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "colour.h"
#include "hit_record.h"
#include "scene.h"
#include "sphere.h"
#include "utils.h"
#include "vector.h"

void init(int argc, char* argv[], config_t* config, scene_t* scene);
void clean_up(scene_t* scene);
void render(scene_t* scene);

int main(int argc, char* argv[]) {
  config_t config;
  scene_t scene;

  // INIT
  init(argc, argv, &config, &scene);

  // RUN
  render(&scene);

  // CLEAN UP
  clean_up(&scene);

  return 0;
}

void init(int argc, char* argv[], config_t* config, scene_t* scene) {
  parse_command_line(argc, argv, config);

  FILE* config_file = fopen(config->config_filename, "r");
  if (config_file == NULL) {
    print_error("config could not be opened");
    exit(1);
  }

  parse_config(config_file, scene);
  print_success("Parsed config file");

  if (fclose(config_file)) {
    print_error("failed to close config file");
  }

  if (config->live_rendering_on) {
    // Init SDL2
  }
}

void clean_up(scene_t* scene) {
  scene_cleanup(scene);
  // clean up SDL
  print_success("Completed clean up");
}

void render(scene_t* scene) {
  colour_t* image_buffer = (colour_t*)malloc(sizeof(colour_t) * scene->width * scene->height);
  if (image_buffer == NULL) {
    print_error("failed to allocate memory for image buffer");
    exit(1);
  }

  const vector_t origin = {
      .x = 0.0f,
      .y = 0.0f,
      .z = 0.0f,
  };

  float FOV          = M_PI_2;
  float vertical_FOV = M_PI_2 * (float)scene->height / (float)scene->width;

  for (int y = 0; y < scene->height; y++) {
    float ray_y_coord = -(2.0f * ((float)y / (float)scene->height - 0.5f) * tanf(vertical_FOV / 2.0f));
    for (int x = 0; x < scene->width; x++) {
      float ray_x_coord = 2.0f * ((float)x / (float)scene->width - 0.5f) * tanf(FOV / 2.0f);
      vector_t ray      = {
               .x = ray_x_coord,
               .y = ray_y_coord,
               .z = -1.0f,
      };

      hit_record_t closest_hr = {
          .hit    = false,
          .colour = {
              .r = 128,
              .g = 128,
              .b = 128,
          },
      };

      for (int i = 0; i < scene->nb_sphere; i++) {
        hit_record_t hr = check_hit(scene->spheres + i, origin, ray);
        if (hr.hit) {
          if (!closest_hr.hit || magnitude(sub(hr.pos, origin)) < magnitude(sub(closest_hr.pos, origin))) {
            closest_hr = hr;
          }
        }
      }

      image_buffer[y * scene->width + x] = closest_hr.colour;
    }
  }

  write_buffer_to_file(image_buffer, *scene);

  free(image_buffer);
}