#include <stdio.h>
#include <inttypes.h>

#include "image/bmp/bmp_header_constants.h"
#include "rotate_image.h"
#include "files_handling/opened_file_to_struct_image.h"


int main()
{	
	uint_fast8_t internal_error_code = 0;

	enum processing_status status = rotate_image(  
		"tester/bmp_test_images/bmp_test_image_4/random_25_bytes_file.bmp"  , 
		" ", 
		&internal_error_code 
	);

	if ( status == PROCESSING_STATUS_PROCESSING_FAILED_WHILE_CONVERTING_FILE_TO_STRUCT_IMAGE 
	&& internal_error_code == FILE_READ_STATUS_UNABLE_TO_READ_BMP_HEADER )
		return 0;
  return 1;
}
