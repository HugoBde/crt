#include "utils.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Log error with colour coding
 *
 * @param message Error message to display
 */
void print_error(char* message) {
  fputs("\x1b[31mERROR: \x1b[0m", stdout);
  puts(message);
}

/**
 * @brief Log success with colour coding
 *
 * @param message Message to display
 */
void print_success(char* message) {
  fputs("\x1b[32mDONE: \x1b[0m", stdout);
  puts(message);
}

/**
 * @brief Parses command line arguments for config file and potential switches
 *
 * @param argc Number of arguments provided
 * @param argv Array of arguments provided
 */
void parse_command_line(int argc, char* argv[], config_t* config) {
  if (argc < 2) {
    print_error("usage: ./bin/ray_tracer <config file> [-l]");
    exit(EINVAL);
  }

  config->config_filename = argv[1];
  config->live_rendering_on = false;

  if (argc == 3) {
    if (strcmp(argv[2], "-l")) {
      print_error("usage: ./bin/ray_tracer <config file> [-l]");
      exit(EINVAL);
    } else {
      print_error("-l: live rendering is not supported yet");
      config->live_rendering_on = true;
      exit(1);
    }
  }
}