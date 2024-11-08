#include "files_handling/opened_file_to_struct_image.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "image/bmp/bmp_header.h"
#include "image/image.h"
#include "image/bmp/bmp_utilities.h"
#include "files_handling/file_utilities.h"

extern const int_fast8_t PIXEL_SIZE_IN_BYTES;

extern const uint16_t BMP_HEADER_SIGNATURE;
extern const uint32_t BMP_HEADER_RESERVED;
extern const uint16_t BMP_HEADER_BI_PLANES;
extern const uint16_t BMP_HEADER_BI_BIT_COUNT;
extern const uint32_t BMP_HEADER_BI_COMPRESSION;
extern const uint32_t BMP_HEADER_BI_COLOR_USED;
extern const uint32_t BMP_HEADER_BI_IMPORTANT_COLORS;

static bool validate_bmp_header_signature( const uint16_t signature );
static bool validate_bmp_header_reserved( const uint32_t reserved );
static bool validate_bmp_header_bi_planes( const uint16_t bi_planes );
static bool validate_bmp_header_bi_bit_count( const uint16_t bi_bit_count );
static bool validate_bmp_header_bi_compression( const uint32_t bi_compression );
static bool validate_bmp_header_bi_color_used( const uint32_t bi_color_used );
static bool validate_bmp_header_bi_important_colors( const uint32_t bi_important_colors );

static enum file_read_status validate_bmp_header( const struct bmp_header* const );

enum file_read_status opened_bmp_file_to_struct_image(
    FILE* const input_bmp_file,
    struct image* const output_image
)
{
	struct bmp_header header;

    // Try to copy the header from file to the local variable
	if ( fread(&header, sizeof( struct bmp_header ), 1, input_bmp_file ) != 1 )
		return FILE_READ_STATUS_UNABLE_TO_READ_BMP_HEADER;

    int_fast8_t padding = bmp_image_width_padding_in_bytes(header.bi_width);

    // Validate header
	enum file_read_status status = validate_bmp_header( &header );
	if ( status != FILE_READ_STATUS_SUCCESS )
		return status;
	
    // Creating image
	enum image_creation_status output_image_creation_status = create_image(
            output_image,
            header.bi_width,
            header.bi_height
    );

    // If image not created, then delete it and return error
	if (output_image_creation_status != IMAGE_CREATION_STATUS_SUCCESS )
    {
        delete_image(output_image);
        return FILE_READ_STATUS_IMAGE_CREATION_FROM_BMP_FILE_FAILED;
    }
	
	if(
        !is_file_has_at_least_n_bytes(
            input_bmp_file,
            bmp_image_file_size_in_bytes( header.data_offset, header.bi_width, header.bi_height )
        )
	)
		return  FILE_READ_STATUS_EXPECTED_PIXEL_DATA_OF_BMP_FILE_CROSSES_END_OF_FILE;

	

    // Move file position indicator to the start of pixel data
	fseek(input_bmp_file, ( long ) header.data_offset, SEEK_SET );
	for (int i = header.bi_height - 1; i >= 0; i--)
    {
        fread(&( output_image->data[ i * header.bi_width ] ),  PIXEL_SIZE_IN_BYTES, header.bi_width, input_bmp_file );
        fseek(input_bmp_file, padding, SEEK_CUR ); // Skip padding bytes
	}

	return FILE_READ_STATUS_SUCCESS;
}

static bool validate_bmp_header_signature( const uint16_t signature )
{
    return signature == BMP_HEADER_SIGNATURE;
}

static bool validate_bmp_header_reserved( const uint32_t reserved )
{
    return reserved == BMP_HEADER_RESERVED;
}

static bool validate_bmp_header_bi_planes( const uint16_t bi_planes )
{
    return bi_planes == BMP_HEADER_BI_PLANES;
}

static bool validate_bmp_header_bi_bit_count( const uint16_t bi_bit_count )
{
    return bi_bit_count == BMP_HEADER_BI_BIT_COUNT;
}

static bool validate_bmp_header_bi_compression( const uint32_t bi_compression )
{
    return bi_compression == BMP_HEADER_BI_COMPRESSION;
}

static bool validate_bmp_header_bi_color_used( const uint32_t bi_color_used )
{
    return bi_color_used == BMP_HEADER_BI_COLOR_USED;
}

static bool validate_bmp_header_bi_important_colors( const uint32_t bi_important_colors )
{
    return bi_important_colors == BMP_HEADER_BI_IMPORTANT_COLORS;
}

static enum file_read_status validate_bmp_header(
        const struct bmp_header* const header
)
{
    if ( !validate_bmp_header_signature(header->signature) )
        return FILE_READ_STATUS_BMP_HEADER_INVALID_MEMBER_SIGNATURE;
    if ( !validate_bmp_header_reserved(header->reserved) )
        return FILE_READ_STATUS_BMP_HEADER_INVALID_MEMBER_RESERVED;
    if ( !validate_bmp_header_bi_planes(header->bi_planes ) )
        return FILE_READ_STATUS_BMP_HEADER_INVALID_MEMBER_BI_PLANES;
    if ( !validate_bmp_header_bi_bit_count(header->bi_bit_count ) )
        return FILE_READ_STATUS_BMP_HEADER_INVALID_MEMBER_BI_BIT_COUNT;
    if ( !validate_bmp_header_bi_compression(header->bi_compression ) )
        return FILE_READ_STATUS_BMP_HEADER_INVALID_MEMBER_BI_COMPRESSION;
    if ( !validate_bmp_header_bi_color_used(header->bi_color_used) )
        return FILE_READ_STATUS_BMP_HEADER_INVALID_MEMBER_BI_COLOR_USED;
    if ( !validate_bmp_header_bi_important_colors(header->bi_important_colors) )
        return FILE_READ_STATUS_BMP_HEADER_INVALID_MEMBER_BI_IMPORTANT_COLORS;
    if ( header->data_offset < sizeof( struct bmp_header ) ||
         header->data_offset >= header->file_size )
        return FILE_READ_STATUS_BMP_HEADER_DATA_OFFSET_ERROR;
    return FILE_READ_STATUS_SUCCESS;
}
