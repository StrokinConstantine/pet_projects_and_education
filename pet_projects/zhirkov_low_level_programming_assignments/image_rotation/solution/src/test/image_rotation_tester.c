#include "test/image_rotation_tester.h"
#include "files_handling/file_utilities.h"
#include "rotate_image.h"

#include <stdbool.h>
#include <stdio.h>






bool test_image_rotation ( char* source_image_filename, char* expected_rotated_image_filename )
{
    char* temporary_image_filename = "temporary_image.bmp";
	uint_fast8_t internal_error_code = 0;
	enum program_execution_status status = rotate_image( source_image_filename,temporary_image_filename, &internal_error_code );
	
	if ( status != PROGRAM_EXECUTION_STATUS_SUCCESS )
        return false;

	if ( !are_files_binary_similar( temporary_image_filename, expected_rotated_image_filename ) )
	{
		remove( temporary_image_filename );
		return false;
	}

	remove( temporary_image_filename );
	return true;
}
