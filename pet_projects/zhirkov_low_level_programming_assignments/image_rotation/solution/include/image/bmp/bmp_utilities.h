#ifndef BMP_UTILITIES_H
#define BMP_UTILITIES_H

#include <stddef.h>
#include <stdint.h>

uint_fast8_t bmp_image_width_padding_in_bytes( const uint_fast64_t bmp_image_width );

size_t bmp_image_padded_pixel_array_size_in_bytes( const uint32_t bi_width, const uint32_t bi_height );

size_t bmp_image_file_size_in_bytes(uint32_t data_offset, uint32_t bi_width, uint32_t bi_height );

#endif // BMP_UTILITIES_H
