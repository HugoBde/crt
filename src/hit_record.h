#ifndef HIT_RECORD_H
#define HIT_RECORD_H

#include "stdbool.h"

#include "colour.h"
#include "vector.h"

typedef struct {
  bool hit;
  colour_t colour;
  vector_t  pos;
} hit_record_t;

#endif