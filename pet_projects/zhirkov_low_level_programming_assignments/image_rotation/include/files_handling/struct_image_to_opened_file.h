#ifndef STRUCT_IMAGE_TO_FILE_PROCESSING_H
#define STRUCT_IMAGE_TO_FILE_PROCESSING_H

#include <stdio.h>

#include "image/image.h"

enum file_write_status
{
  FILE_WRITE_STATUS_SUCCESS = 0,

  FILE_WRITE_STATUS_UNKNOWN_FILE_EXTENSION,

  FILE_WRITE_STATUS_UNABLE_TO_WRITE_IMAGE_TO_BMP_FILE
};

enum file_write_status struct_image_to_bmp_opened_file (
  FILE *const output_file,
  const struct image* const input_image
);

enum file_write_status struct_image_to_opened_file (
        const char* filename,
        FILE *const output_file,
        const struct image* const input_image
);


#endif // STRUCT_IMAGE_TO_FILE_PROCESSING_H
