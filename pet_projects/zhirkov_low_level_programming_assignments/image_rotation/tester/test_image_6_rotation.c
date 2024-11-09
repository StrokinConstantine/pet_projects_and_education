#include <stdio.h>
#include <inttypes.h>

#include "image/bmp/bmp_header_constants.h"
#include "rotate_image.h"
#include "files_handling/opened_file_to_struct_image.h"

int main()
{	
	uint_fast8_t internal_error_code = 0;

	enum program_execution_status status =
	rotate_image(  
		"tester/bmp_test_images/bmp_test_image_6/wrong_height_and_width_image.bmp"  , 
		" ", 
		&internal_error_code 
	);

	if (status == PROGRAM_EXECUTION_STATUS_ERROR_WHILE_CONVERTING_IMAGE_FILE_TO_STRUCT_IMAGE
	&& internal_error_code == FILE_READ_STATUS_EXPECTED_PIXEL_DATA_OF_BMP_FILE_CROSSES_END_OF_FILE )
		return 0;
  return 1;
}
