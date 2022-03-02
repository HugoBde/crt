#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <stddef.h>

/**
 * @brief filename of config file
 *
 */
char* g_config_filename = NULL;

/**
 * @brief whether program is running in live rendering with SDL
 *
 */
bool g_live_rendering_on = false;

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
void parse_command_line(int argc, char* argv[]);

#endif