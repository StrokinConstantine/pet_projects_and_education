#ifndef BMP_HEADER_H
#define BMP_HEADER_H

#include <stdint.h>

struct bmp_header 
{
    uint16_t signature;
    uint32_t file_size;
    uint32_t reserved;
    uint32_t data_offset;
    uint32_t bi_size;
    uint32_t bi_width;
    uint32_t bi_height;
    uint16_t bi_planes;
    uint16_t bi_bit_count;
    uint32_t bi_compression;
    uint32_t bi_size_image;
    uint32_t bi_x_pixels_per_meter;
    uint32_t bi_y_pixels_per_meter;
    uint32_t bi_color_used;
    uint32_t bi_important_colors;

} __attribute__ ((packed));

#endif // BMP_HEADER_H
