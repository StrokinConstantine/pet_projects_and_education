#ifndef PIXEL_H
#define PIXEL_H

#include <stdint.h>

struct pixel
{
  uint8_t b;
  uint8_t g;
  uint8_t r;
} __attribute__ ((packed));

#endif // PIXEL_H
