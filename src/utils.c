#include "utils.h"

#include <stdio.h>

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