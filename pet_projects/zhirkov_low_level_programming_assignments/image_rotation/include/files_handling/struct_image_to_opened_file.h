#ifndef STRUCT_IMAGE_TO_FILE_PROCESSING_H
#define STRUCT_IMAGE_TO_FILE_PROCESSING_H

#include <stdio.h>

#include "image/image.h"

enum file_write_status
{
  FILE_WRITE_OK = 0,
  FILE_WRITE_ERROR
};

enum file_write_status struct_image_to_bmp_opened_file (
  FILE *const out,
  const struct image* const source_image
);  

#endif // STRUCT_IMAGE_TO_FILE_PROCESSING_H
