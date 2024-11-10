#include <stdio.h>
#include <inttypes.h>
#include "rotate_image.h"
#include "output_messages/output_message_printer.h"

int main ( int argc, char *argv[] )
{
	if ( argc != 3 )
	{  
		fprintf(stderr, "Usage: %s <source-image-filename> <rotated-image-filename>\n", argv[0]);  
		return 1;  
	}

    uint_fast8_t internal_error_code = 0;
	enum program_execution_status general_error_code = rotate_image( argv[1], argv[2], &internal_error_code );
	print_program_execution_status( general_error_code, internal_error_code );

	if ( general_error_code == PROGRAM_EXECUTION_STATUS_SUCCESS )
		return 0;
	return 1;
}
