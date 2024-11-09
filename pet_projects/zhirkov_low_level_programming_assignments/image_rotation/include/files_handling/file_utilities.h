#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdbool.h>
#include "image/image_file_formats.h"




enum image_file_extension_status
{
    IMAGE_FILE_EXTENSION_STATUS_VALID_EXTENSION,
    IMAGE_FILE_EXTENSION_STATUS_INVALID_EXTENSION
};


bool is_file_has_at_least_n_bytes( FILE* const, const size_t );

bool are_files_binary_similar(const char* filename_1, const char* filename_2 );

enum image_file_extension_status get_image_file_format(const char *filename, enum image_file_formats* image_format );




#endif // UTIL_H
