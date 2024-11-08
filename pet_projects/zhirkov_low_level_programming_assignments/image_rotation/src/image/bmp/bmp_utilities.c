#include "image/bmp/bmp_utilities.h"
#include <stdint.h>
#include "constants.h"

extern const int_fast8_t PIXEL_SIZE_IN_BYTES;

int_fast8_t bmp_image_width_padding_in_bytes( const uint_fast64_t bmp_image_width )
{
    return ( 4 - ( bmp_image_width *(uint_fast64_t) PIXEL_SIZE_IN_BYTES ) % 4 ) % 4;
}


size_t bmp_image_padded_pixel_array_size_in_bytes( const uint32_t bi_width, const uint32_t bi_height )
{
    uint_fast64_t padded_width_in_bytes = bi_width * (uint_fast64_t)( PIXEL_SIZE_IN_BYTES ) 
		+ (int_fast64_t)( bmp_image_width_padding_in_bytes( bi_width ) );
    return (size_t)( padded_width_in_bytes * bi_height );
}

size_t bmp_image_file_size_in_bytes(
    const uint32_t data_offset,
    const uint32_t bi_width,
    const uint32_t bi_height
)
{
    return (size_t)( data_offset ) + bmp_image_padded_pixel_array_size_in_bytes( bi_width, bi_height );
}

