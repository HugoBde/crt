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

/**
 * @brief Write image buffer to ppm file
 * 
 * @param buffer image buffer 
 * @param scene scene config containing image size and output filename
 */
void write_buffer_to_file(colour_t* image_buffer, scene_t scene) {
  FILE* output_file = fopen(scene.filename, "w");
  if (output_file == NULL) {
    print_error("could not open output file");
    return;
  }

  // File header data:
  // P6
  // <width> <height>
  // <max value for colour>
  fprintf(output_file, "P6\n%d %d\n255\n", scene.width, scene.height);

  char* write_buffer = (char*) malloc(sizeof(char) * scene.width * scene.height * 3);
  for (int i = 0; i < scene.height; i++) {
    int height_offset = i * scene.width;
    for (int j = 0; j < scene.width; j++) {
      write_buffer[(height_offset + j) * 3 + 0] = image_buffer[height_offset + j].r;
      write_buffer[(height_offset + j) * 3 + 1] = image_buffer[height_offset + j].g;
      write_buffer[(height_offset + j) * 3 + 2] = image_buffer[height_offset + j].b;
    }
  }
  fwrite(write_buffer, sizeof(char), scene.height * scene.width * 3, output_file);
  free(write_buffer);



  fclose(output_file);
}