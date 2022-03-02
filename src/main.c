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

scene_t g_scene;

void init(int argc, char* argv[]);
void clean_up();

int main(int argc, char* argv[]) {
  // INIT
  init(argc, argv);

  // RUN
  // render(&scene);

  // CLEAN UP
  clean_up();

  return 0;
}

void init(int argc, char* argv[]) {
  parse_command_line(argc, argv);

  FILE* config_file = fopen(g_config_filename, "r");
  if (config_file == NULL) {
    print_error("config could not be opened");
    exit(1);
  }

  parse_config(config_file, &g_scene);
  print_success("Parsed config file");

  if (fclose(config_file)) {
    print_error("failed to close config file");
  }

  if (g_live_rendering_on) {
    // Init SDL2
  }
}

void clean_up() {
  scene_cleanup(&g_scene);
  // clean up SDL
  print_success("Completed clean up");
}