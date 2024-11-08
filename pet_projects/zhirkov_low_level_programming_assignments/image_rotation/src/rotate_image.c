#include "rotate_image.h"

#include <inttypes.h>
#include <stdio.h>

#include "files_handling/file_utilities.h"
#include "files_handling/opened_file_to_struct_image.h"
#include "image/rotation/struct_image_rotation.h"
#include "files_handling/struct_image_to_opened_file.h"





enum processing_status rotate_image( 
	char* source_image_filename,
	char* rotated_image_filename,
	uint_fast8_t* internal_error_code
)
{
	// Open source image file
	FILE* source_image_file = fopen( source_image_filename, "rb" );
	if ( source_image_file == NULL )
		return PROCESSING_STATUS_PROCESSING_FAILED_WHILE_OPENING_SOURCE_IMAGE_FILE;
	struct image source_image = { 0 };
	// Source image file -> struct image
	enum file_read_status file_read_status = opened_bmp_file_to_struct_image( source_image_file , &source_image );	
	fclose(source_image_file);  
	if (file_read_status != FILE_READ_STATUS_SUCCESS )
	{
        delete_image(&source_image);
		*internal_error_code = file_read_status;
		return PROCESSING_STATUS_PROCESSING_FAILED_WHILE_CONVERTING_FILE_TO_STRUCT_IMAGE;
	}
	
	// Rotation of image
	struct image rotated_image;
	enum image_rotation_status rotation_status = 
		get_image_turned_90_degrees_counterclockwise( &source_image, &rotated_image );

    delete_image(&source_image);
  
	if (rotation_status != IMAGE_ROTATION_STATUS_SUCCESS )
	{
        delete_image(&rotated_image);
		*internal_error_code = rotation_status;
		return PROCESSING_STATUS_PROCESSING_FAILED_WHILE_ROTATING_IMAGE;
	}
  
	// Open rotated image file
	FILE* rotated_image_file = fopen( rotated_image_filename, "wb");  
	if ( rotated_image_file == NULL )
	{
        delete_image(&rotated_image);
		return PROCESSING_STATUS_PROCESSING_FAILED_WHILE_OPENING_ROTATED_IMAGE_FILE;  
	}  
 
	// Write rotated image to file
	enum file_write_status write_status = struct_image_to_bmp_opened_file(rotated_image_file, &rotated_image);
  
	if ( write_status != FILE_WRITE_OK )
	{
        delete_image(&rotated_image);
		fclose( rotated_image_file );
		return PROCESSING_STATUS_PROCESSING_FAILED_WHILE_WRITING_TO_ROTATED_IMAGE_FILE;
	}

    delete_image(&rotated_image);
	fclose(rotated_image_file);
	return PROCESSING_STATUS_PROCESSING_FINISHED_SUCCESSFULLY;
}
