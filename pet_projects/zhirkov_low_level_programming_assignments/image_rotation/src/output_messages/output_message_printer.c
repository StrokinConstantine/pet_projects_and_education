#include "output_messages/output_message_printer.h"
#include <stdio.h>
#include <stdint.h>
#include "files_handling/opened_file_to_struct_image.h"
#include "image/rotation/struct_image_rotation.h"
#include "files_handling/struct_image_to_opened_file.h"
#include "rotate_image.h"

static void print_message_on_success(const uint_fast8_t internal_error_code __attribute__ (( unused )) );
static void print_message_on_error_while_opening_source_image_file( const uint_fast8_t internal_error_code __attribute__ (( unused )) );
static void print_message_on_error_while_converting_image_file_to_struct_image( const uint_fast8_t internal_error_code );
static void print_message_on_error_while_rotating_image( const uint_fast8_t internal_error_code );
static void print_message_on_error_while_opening_rotated_image_file(const uint_fast8_t internal_error_code __attribute__ (( unused )) );
static void print_message_on_error_while_writing_to_rotated_image_file(const uint_fast8_t internal_error_code );

void print_program_execution_status( const uint_fast8_t general_error_code, const uint_fast8_t internal_error_code )
{
	static void ( *error_message_handlers[8] )( const uint_fast8_t internal_error_code ) =
        {
        [PROGRAM_EXECUTION_STATUS_SUCCESS] = print_message_on_success,
        [PROGRAM_EXECUTION_STATUS_ERROR_WHILE_OPENING_SOURCE_IMAGE_FILE] = print_message_on_error_while_opening_source_image_file,
        [PROGRAM_EXECUTION_STATUS_ERROR_WHILE_CONVERTING_IMAGE_FILE_TO_STRUCT_IMAGE] = print_message_on_error_while_converting_image_file_to_struct_image,
        [PROGRAM_EXECUTION_STATUS_ERROR_WHILE_ROTATING_IMAGE] = print_message_on_error_while_rotating_image,
        [PROGRAM_EXECUTION_STATUS_ERROR_WHILE_OPENING_ROTATED_IMAGE_FILE] = print_message_on_error_while_opening_rotated_image_file,
        [PROGRAM_EXECUTION_STATUS_ERROR_WHILE_WRITING_TO_ROTATED_IMAGE_FILE] = print_message_on_error_while_writing_to_rotated_image_file
        };
	error_message_handlers[ general_error_code ]( internal_error_code );
}

static void print_message_on_success( const uint_fast8_t internal_error_code __attribute__ (( unused )) )
{
    puts( "Image successfully rotated.");
}

static void print_message_on_error_while_opening_source_image_file( const uint_fast8_t internal_error_code __attribute__ (( unused )) )
{
    fputs( "Error while opening source image file.\n" , stderr );
}

static void print_message_on_error_while_converting_image_file_to_struct_image( const uint_fast8_t internal_error_code )
{
    static const char* error_messages[] =
            {
        [FILE_READ_STATUS_SUCCESS] = "Source image file successfully converted to struct image.\n", // this message will never be shown
        [FILE_READ_STATUS_UNKNOWN_FILE_EXTENSION] = "Unknown source image file extension.\n",
        [FILE_READ_STATUS_UNABLE_TO_READ_BMP_HEADER] = "Unable to read bmp header in source image file.\n",
        [FILE_READ_STATUS_BMP_HEADER_INVALID_MEMBER_SIGNATURE] = "bmp source image file has invalid signature.\n",
        [FILE_READ_STATUS_BMP_HEADER_INVALID_MEMBER_RESERVED] = "bmp source image file has invalid member \"reserved\".\n",
        [FILE_READ_STATUS_BMP_HEADER_INVALID_MEMBER_BI_PLANES] = "bmp source image file has invalid member \"bi_planes\".\n",
        [FILE_READ_STATUS_BMP_HEADER_INVALID_MEMBER_BI_BIT_COUNT] = "bmp source image file has invalid member \"bit_count\".\n",
        [FILE_READ_STATUS_BMP_HEADER_INVALID_MEMBER_BI_COMPRESSION] = "bmp source image file has invalid member \"bi_compression\".\n",
        [FILE_READ_STATUS_BMP_HEADER_INVALID_MEMBER_BI_COLOR_USED] = "bmp source image file has invalid member \"bi_color_used\".\n",
        [FILE_READ_STATUS_BMP_HEADER_INVALID_MEMBER_BI_IMPORTANT_COLORS] = "bmp source image file has invalid member \"bi_important_colors\".\n",
        [FILE_READ_STATUS_BMP_HEADER_DATA_OFFSET_ERROR] = "bmp source image file has invalid data offset.\n",
        [FILE_READ_STATUS_IMAGE_CREATION_FROM_BMP_FILE_FAILED] = "Image creation from bmp source image file failed.\n",
        [FILE_READ_STATUS_EXPECTED_PIXEL_DATA_OF_BMP_FILE_CROSSES_END_OF_FILE] = "Expected pixel data of bmp source image file crosses end of file.\n",
        };
    fputs( error_messages[internal_error_code] , stderr );
}

static void print_message_on_error_while_rotating_image( const uint_fast8_t internal_error_code )
{
    static const char* error_messages[] =
        {
        [IMAGE_ROTATION_STATUS_SUCCESS] = "Image successfully rotated.", // this message will never be shown
        [IMAGE_ROTATION_STATUS_ROTATED_IMAGE_CREATION_FAILED] = "Rotated image creation failed."
        };
    fputs( error_messages[internal_error_code] , stderr );
}

static void print_message_on_error_while_opening_rotated_image_file(
        const uint_fast8_t internal_error_code __attribute__ (( unused ))
)
{
    fputs( "Error while opening rotated image file.\n" , stderr );
}

static void print_message_on_error_while_writing_to_rotated_image_file(
        const uint_fast8_t internal_error_code
)
{
    static const char* error_messages[] =
        {
        [FILE_WRITE_STATUS_SUCCESS] = "Image has been successfully written to the file.\n",
        [FILE_WRITE_STATUS_UNKNOWN_FILE_EXTENSION] = "Unknown extension for output file.\n",
        [FILE_WRITE_STATUS_UNABLE_TO_WRITE_IMAGE_TO_BMP_FILE] = "Unable to write image to bmp file.\n"
        };
    fputs( error_messages[internal_error_code] , stderr );
}
