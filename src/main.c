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

#include <stdio.h>
#include <stdlib.h>

#include "scene.h"
#include "sphere.h"
#include "utils.h"

void init(int argc, char* argv[], config_t* config, scene_t* scene);
void clean_up(scene_t* scene);

int main(int argc, char* argv[]) {
  config_t config;
  scene_t scene;

  // INIT
  init(argc, argv, &config, &scene);

  // RUN
  // render(&scene);

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