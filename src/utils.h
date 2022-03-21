#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <stddef.h>

#include "colour.h"
#include "scene.h"

/**
 * @brief Various configuration option
 *
 */
typedef struct {
  char* config_filename;
  bool live_rendering_on;
} config_t;

/**
 * @brief Log error with colour coding
 *
 * @param message Error message to display
 */
void print_error(char* message);

/**
 * @brief Log success with colour coding
 *
 * @param message Message to display
 */
void print_success(char* message);

/**
 * @brief Parses command line arguments for config file and potential switches
 *
 * @param argc Number of arguments provided
 * @param argv Array of arguments provided
 */
void parse_command_line(int argc, char* argv[], config_t* config);

/**
 * @brief Write image buffer to ppm file
 *
 * @param image_buffer image buffer
 * @param scene scene config containing image size and output filename
 */
void write_buffer_to_file(colour_t* image_buffer, scene_t scene);

/**
 * @brief Compares two double numbers
 * 
 * @param a 
 * @param b 
 * @return int 0 if both numbers are equal, -1 if a is smaller than b, 1 if a is greater than b
 */
int comp_double(double a, double b);

#endif