#include "files_handling/struct_image_to_opened_file.h"
#include <stdio.h>
#include <inttypes.h>  
#include <string.h>
#include "image/bmp/bmp_header.h"
#include "image/image.h"
#include "image/pixel.h"
#include "image/bmp/bmp_utilities.h"
#include "image/image_file_formats.h"
#include "files_handling/file_utilities.h"

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
static enum file_write_status struct_image_to_bmp_opened_file (FILE* const output_file, const struct image* const input_image );

enum file_write_status struct_image_to_opened_file ( const char* filename, FILE *const output_file, const struct image* const input_image )
{

    static enum file_write_status ( *struct_image_to_opened_file_handlers[2] )(
        FILE* const output_file,
        const struct image* const input_image ) =
            {
        [IMAGE_FILE_FORMATS_BMP] = struct_image_to_bmp_opened_file,
        [IMAGE_FILE_FORMATS_PNG] = NULL // to do
            };

    enum image_file_formats output_file_format;
    enum image_file_extension_status output_file_extension_status = get_image_file_format( filename, &output_file_format );

    if (output_file_extension_status != IMAGE_FILE_EXTENSION_STATUS_VALID_EXTENSION )
        return FILE_WRITE_STATUS_UNKNOWN_FILE_EXTENSION;

    return struct_image_to_opened_file_handlers[output_file_format]( output_file, input_image );
}


static enum file_write_status struct_image_to_bmp_opened_file (FILE* const output_file, const struct image* const input_image )
{  
	const size_t padding = bmp_image_width_padding_in_bytes( input_image->width );
	uint8_t bmp_file_header[ sizeof(struct bmp_header) ] = {0};
	struct bmp_header header;
    fill_bmp_header(&header, input_image->width, input_image->height);
	memcpy(bmp_file_header, &header, sizeof(header));

	if ( fwrite(bmp_file_header, sizeof(uint8_t), BMP_HEADER_DATA_OFFSET, output_file ) != BMP_HEADER_DATA_OFFSET )
		return FILE_WRITE_STATUS_UNABLE_TO_WRITE_IMAGE_TO_BMP_FILE;

    // Write pixel array to the output file  
    for (uint64_t j = 0; j < input_image->height; j++)
	{  
		for (uint64_t i = 0; i < input_image->width; i++)
		{  
			struct pixel px = input_image->data[(input_image->height - 1 - j) * input_image->width + i];
            fwrite(&px, sizeof(struct pixel), 1, output_file );
        } 
        // Padding
        uint8_t zeros[3] = {0, 0, 0};  
        if ( padding > 0 ) 
            fwrite(zeros, sizeof(uint8_t), padding, output_file);
    }
    return FILE_WRITE_STATUS_SUCCESS;
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
