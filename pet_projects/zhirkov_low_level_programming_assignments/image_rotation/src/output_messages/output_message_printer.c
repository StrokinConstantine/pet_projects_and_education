#include <output_messages/output_message_printer.h>

#include <stdio.h>
#include <inttypes.h>

#include <files_handling/opened_file_to_struct_image.h>
#include <image/rotation/struct_image_rotation.h>
#include <files_handling/struct_image_to_opened_file.h>
#include <rotate_image.h>


static void print_message_on_processing_finished_successfully( 
	const uint_fast8_t internal_error_code __attribute__ (( unused ))
)
{
	puts( "Image successfully rotated.");
}

static void print_message_on_processing_failed_while_opening_source_image_file( 
	const uint_fast8_t internal_error_code __attribute__ (( unused ))
)
{	
	fputs( "Error while opening source image file.\n" , stderr );
}

static void print_message_on_processing_failed_while_converting_file_to_struct_image( 
	const uint_fast8_t internal_error_code
)
{
	static const char* error_messages[] = 
	{
		[FILE_READ_STATUS_SUCCESS] =
		"FILE_READ_STATUS_SUCCESS",
		[FILE_READ_STATUS_UNABLE_TO_READ_BMP_HEADER] =
		"FILE_READ_STATUS_UNABLE_TO_READ_BMP_HEADER",
		[FILE_READ_STATUS_BMP_HEADER_INVALID_MEMBER_SIGNATURE] =
		"FILE_READ_STATUS_BMP_HEADER_INVALID_MEMBER_SIGNATURE",
		[FILE_READ_STATUS_BMP_HEADER_INVALID_MEMBER_RESERVED] =
		"FILE_READ_STATUS_BMP_HEADER_INVALID_MEMBER_RESERVED",
		[FILE_READ_STATUS_BMP_HEADER_INVALID_MEMBER_BI_PLANES] =
		"FILE_READ_STATUS_BMP_HEADER_INVALID_MEMBER_BI_PLANES",
		[FILE_READ_STATUS_BMP_HEADER_INVALID_MEMBER_BI_BIT_COUNT] =
		"FILE_READ_STATUS_BMP_HEADER_INVALID_MEMBER_BI_BIT_COUNT",
		[FILE_READ_STATUS_BMP_HEADER_INVALID_MEMBER_BI_COMPRESSION] =
		"FILE_READ_STATUS_BMP_HEADER_INVALID_MEMBER_BI_COMPRESSION",
		[FILE_READ_STATUS_BMP_HEADER_INVALID_MEMBER_BI_COLOR_USED] =
		"FILE_READ_STATUS_BMP_HEADER_INVALID_MEMBER_BI_COLOR_USED",
		[FILE_READ_STATUS_BMP_HEADER_INVALID_MEMBER_BI_IMPORTANT_COLORS] =
		"FILE_READ_STATUS_BMP_HEADER_INVALID_MEMBER_BI_IMPORTANT_COLORS",
		[FILE_READ_STATUS_BMP_HEADER_DATA_OFFSET_ERROR] =
		"FILE_READ_STATUS_BMP_HEADER_DATA_OFFSET_ERROR",
		[FILE_READ_STATUS_IMAGE_CREATION_FROM_BMP_FILE_FAILED] =
		"FILE_READ_STATUS_IMAGE_CREATION_FROM_BMP_FILE_FAILED",
		[FILE_READ_STATUS_EXPECTED_PIXEL_DATA_OF_BMP_FILE_CROSSES_END_OF_FILE] =
		"FILE_READ_STATUS_EXPECTED_PIXEL_DATA_OF_BMP_FILE_CROSSES_END_OF_FILE",
	};
	
	fputs( error_messages[internal_error_code] , stderr );
}

static void print_message_on_processing_failed_while_rotating_image( 
	const uint_fast8_t internal_error_code
)
{
	static const char* error_messages[] = 
	{
		[IMAGE_ROTATION_STATUS_SUCCESS] =
		"IMAGE_ROTATION_STATUS_SUCCESS",
		[IMAGE_ROTATION_STATUS_ROTATED_IMAGE_CREATION_FAILED] =
		"IMAGE_ROTATION_STATUS_ROTATED_IMAGE_CREATION_FAILED"
	};
	
	fputs( error_messages[internal_error_code] , stderr );
}

static void print_message_on_processing_failed_while_opening_rotated_image_file( 
	const uint_fast8_t internal_error_code __attribute__ (( unused ))
)
{
	fputs( "Error while opening rotated image file.\n" , stderr );
}

static void print_message_on_processing_failed_while_writing_to_rotated_image_file( 
	const uint_fast8_t internal_error_code
)
{
	static const char* error_messages[] = 
	{
		[FILE_WRITE_OK] = "FILE_WRITE_OK", 
		[FILE_WRITE_ERROR] = "FILE_WRITE_ERROR"
	};

	fputs( error_messages[internal_error_code] , stderr );
}


void print_program_execution_status( 
  const uint_fast8_t general_error_code, 
  const uint_fast8_t internal_error_code 
)
{
	static void (*error_message_handlers[6])( const uint_fast8_t internal_error_code ) = 
	{
		[PROCESSING_STATUS_PROCESSING_FINISHED_SUCCESSFULLY] = 
		print_message_on_processing_finished_successfully,
		[PROCESSING_STATUS_PROCESSING_FAILED_WHILE_OPENING_SOURCE_IMAGE_FILE] = 
		print_message_on_processing_failed_while_opening_source_image_file,
		[PROCESSING_STATUS_PROCESSING_FAILED_WHILE_CONVERTING_FILE_TO_STRUCT_IMAGE] = 
		print_message_on_processing_failed_while_converting_file_to_struct_image,
		[PROCESSING_STATUS_PROCESSING_FAILED_WHILE_ROTATING_IMAGE] = 
		print_message_on_processing_failed_while_rotating_image,
		[PROCESSING_STATUS_PROCESSING_FAILED_WHILE_OPENING_ROTATED_IMAGE_FILE] = 
		print_message_on_processing_failed_while_opening_rotated_image_file,
		[PROCESSING_STATUS_PROCESSING_FAILED_WHILE_WRITING_TO_ROTATED_IMAGE_FILE] = 
		print_message_on_processing_failed_while_writing_to_rotated_image_file
	};
	
	error_message_handlers[ general_error_code ]( internal_error_code );
}
