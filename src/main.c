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

#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "sphere.h"
#include "scene.h"
#include "utils.h"


scene_t init(int argc, char* argv[]);


int main(int argc, char* argv[]) {

    // INIT
    scene_t scene = init(argc, argv);

    // RUN
    //render(&scene);

    // CLEAN UP
    scene_cleanup(&scene);
    print_success("Completed clean up");
    return 0;
}

scene_t init(int argc, char* argv[]) {
    //bool live_rendering = false;

    if (argc < 2) {
        print_error("usage: ./bin/ray_tracer <config file> [-l]");
        exit(EINVAL);
    }

    if (argc == 3) {
        if (strcmp(argv[2], "-l")) {
            print_error("usage: ./bin/ray_tracer <config file> [-l]");
            exit(EINVAL);
        } else {
            print_error("-l: live rendering is not supported yet");
            //live_rendering = true;
            exit(1);
        }
    }

    FILE* config_file = fopen(argv[1], "r");
    if (config_file == NULL) {
        print_error("config could not be opened");
        exit(1);
    }

    scene_t scene;

    errno = 0;
    parse_config(config_file, &scene);

    if (errno != 0) {
        switch (errno) {
            case 1:
            print_error("failed to initialise scene");
            default:
            print_error("failed to parse config file");
        }
        exit(1);
    }
    print_success("Parsed config file");
    
    if (fclose(config_file)) {
        print_error("failed to close config file");
    }

    return scene;
}