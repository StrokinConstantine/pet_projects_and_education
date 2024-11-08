#include "files_handling/struct_image_to_opened_file.h"

#include <stdio.h>
#include <inttypes.h>  
#include <string.h>

#include "../../include/image/bmp/bmp_header.h"
#include "image/image.h"
#include "image/pixel.h"
#include "image/bmp/bmp_utilities.h"

extern const int_fast8_t PIXEL_SIZE_IN_BYTES;

extern const uint16_t BMP_HEADER_SIGNATURE;
extern const uint32_t BMP_HEADER_RESERVED;
extern const uint32_t BMP_HEADER_DATA_OFFSET;
extern const uint32_t BMP_HEADER_BI_SIZE;
extern const uint16_t BMP_HEADER_BI_PLANES;
extern const uint16_t BMP_HEADER_BI_BIT_COUNT;
extern const uint32_t BMP_HEADER_BI_COMPRESSION;
extern const uint32_t BMP_HEADER_BI_X_PIXELS_PER_METER;
extern const uint32_t BMP_HEADER_BI_Y_PIXELS_PER_METER;
extern const uint32_t BMP_HEADER_BI_COLOR_USED;
extern const uint32_t BMP_HEADER_BI_IMPORTANT_COLORS;



static void fill_bmp_header( struct bmp_header* const header, const uint32_t bi_width, const uint32_t bi_height);


enum file_write_status struct_image_to_bmp_opened_file (FILE* const out, const struct image* const source_image )
{  
	const size_t padding = (4 - (source_image->width * sizeof( struct pixel )  ) % 4) % 4;
	//const size_t padded_row_size = (source_image->width * sizeof( struct pixel ) + padding);
	//const size_t pixel_array_size = padded_row_size * source_image->height;

	uint8_t bmp_file_header[ sizeof(struct bmp_header) ] = {0};  
  
	struct bmp_header header;

    fill_bmp_header( &header, source_image->width, source_image->height);

	// Fill header data
//	header.signature = BMP_HEADER_SIGNATURE;
//	header.file_size = BMP_HEADER_DATA_OFFSET + pixel_array_size;
//	header.reserved = BMP_HEADER_RESERVED;
//	header.data_offset = BMP_HEADER_DATA_OFFSET;
//	header.bi_size = BMP_HEADER_BI_SIZE;
//	header.bi_width = source_image->width;
//	header.bi_height = source_image->height;
//	header.bi_planes = BMP_HEADER_BI_PLANES;
//	header.bi_bit_count = BMP_HEADER_BI_BIT_COUNT;
//	header.bi_compression = BMP_HEADER_BI_COMPRESSION;
//	header.bi_size_image = pixel_array_size;
//	header.bi_x_pixels_per_meter = BMP_HEADER_BI_X_PIXELS_PER_METER;
//	header.bi_y_pixels_per_meter = BMP_HEADER_BI_Y_PIXELS_PER_METER;
//	header.bi_color_used = BMP_HEADER_BI_COLOR_USED;
//	header.bi_important_colors = BMP_HEADER_BI_IMPORTANT_COLORS;

	memcpy(bmp_file_header, &header, sizeof(header));  

	if ( fwrite( bmp_file_header, sizeof(uint8_t), BMP_HEADER_DATA_OFFSET, out ) != BMP_HEADER_DATA_OFFSET )
		return FILE_WRITE_ERROR;

    // Write pixel array to the output file  
    for (uint64_t j = 0; j < source_image->height; j++)
	{  
		for (uint64_t i = 0; i < source_image->width; i++)
		{  
			struct pixel px = source_image->data[(source_image->height - 1 - j) * source_image->width + i];
            fwrite( &px, sizeof(struct pixel), 1, out );  
        } 
        // Padding
        uint8_t zeros[3] = {0, 0, 0};  
        if ( padding > 0 ) 
            fwrite( zeros, sizeof(uint8_t), padding, out);  
    }  
	
    return FILE_WRITE_OK;  
}

static void fill_bmp_header( struct bmp_header* const header, const uint32_t bi_width, const uint32_t bi_height )
{
    header->signature = BMP_HEADER_SIGNATURE;
    header->file_size = bmp_image_file_size_in_bytes( BMP_HEADER_DATA_OFFSET, bi_width, bi_height );
    header->reserved = BMP_HEADER_RESERVED;
    header->data_offset = BMP_HEADER_DATA_OFFSET;
    header->bi_size = BMP_HEADER_BI_SIZE;
    header->bi_width = bi_width;
    header->bi_height = bi_height;
    header->bi_planes = BMP_HEADER_BI_PLANES;
    header->bi_bit_count = BMP_HEADER_BI_BIT_COUNT;
    header->bi_compression = BMP_HEADER_BI_COMPRESSION;
    header->bi_size_image = bmp_image_padded_pixel_array_size_in_bytes( bi_width, bi_height );
    header->bi_x_pixels_per_meter = BMP_HEADER_BI_X_PIXELS_PER_METER;
    header->bi_y_pixels_per_meter = BMP_HEADER_BI_Y_PIXELS_PER_METER;
    header->bi_color_used = BMP_HEADER_BI_COLOR_USED;
    header->bi_important_colors = BMP_HEADER_BI_IMPORTANT_COLORS;
}