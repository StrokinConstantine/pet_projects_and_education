#include "rotate_image.h"

#include <inttypes.h>
#include <stdio.h>

#include "files_handling/opened_file_to_struct_image.h"
#include "image/rotation/struct_image_rotation.h"
#include "files_handling/struct_image_to_opened_file.h"
#include "constants.h"

enum program_execution_status rotate_image(
        char* const source_image_filename,
        char* const rotated_image_filename,
        uint_fast8_t* const internal_error_code
)
{

	FILE* source_image_file = fopen( source_image_filename, "rb" );
	if ( source_image_file == NULL )
		return PROGRAM_EXECUTION_STATUS_ERROR_WHILE_OPENING_SOURCE_IMAGE_FILE;
	struct image source_image = { 0 };


    enum file_read_status file_read_status = opened_file_to_struct_image( source_image_filename ,source_image_file , &source_image );
    fclose(source_image_file);

	if (file_read_status != FILE_READ_STATUS_SUCCESS )
	{
		*internal_error_code = file_read_status;
		return PROGRAM_EXECUTION_STATUS_ERROR_WHILE_CONVERTING_IMAGE_FILE_TO_STRUCT_IMAGE;
	}


	struct image rotated_image;

    enum image_rotation_status rotation_status = get_image_rotated_counterclockwise( &source_image, &rotated_image, CONSTANT_ROTATION_ANGLE_IN_DEGREES );

    delete_image(&source_image);
  
	if (rotation_status != IMAGE_ROTATION_STATUS_SUCCESS )
	{
        delete_image(&rotated_image);
		*internal_error_code = rotation_status;
		return PROGRAM_EXECUTION_STATUS_ERROR_WHILE_ROTATING_IMAGE;
	}

	FILE* rotated_image_file = fopen( rotated_image_filename, "wb");  
	if ( rotated_image_file == NULL )
	{
        delete_image(&rotated_image);
		return PROGRAM_EXECUTION_STATUS_ERROR_WHILE_OPENING_ROTATED_IMAGE_FILE;
	}

    enum file_write_status write_status = struct_image_to_opened_file(rotated_image_filename, rotated_image_file, &rotated_image);


	if (write_status != FILE_WRITE_STATUS_SUCCESS )
	{
        delete_image(&rotated_image);
		fclose( rotated_image_file );
        remove(rotated_image_filename );
        *internal_error_code = write_status;
        return PROGRAM_EXECUTION_STATUS_ERROR_WHILE_WRITING_TO_ROTATED_IMAGE_FILE;
	}

    delete_image(&rotated_image);
	fclose(rotated_image_file);
	return PROGRAM_EXECUTION_STATUS_SUCCESS;
}
