#ifndef OPENED_FILE_TO_STRUCT_IMAGE_H
#define OPENED_FILE_TO_STRUCT_IMAGE_H

#include <stdio.h> 
#include "image/image.h"

enum file_read_status
{
  FILE_READ_STATUS_SUCCESS = 0,
  FILE_READ_STATUS_UNABLE_TO_READ_BMP_HEADER,
  FILE_READ_STATUS_BMP_HEADER_INVALID_MEMBER_SIGNATURE,
  FILE_READ_STATUS_BMP_HEADER_INVALID_MEMBER_RESERVED,
  FILE_READ_STATUS_BMP_HEADER_INVALID_MEMBER_BI_PLANES,
  FILE_READ_STATUS_BMP_HEADER_INVALID_MEMBER_BI_BIT_COUNT,
  FILE_READ_STATUS_BMP_HEADER_INVALID_MEMBER_BI_COMPRESSION,
  FILE_READ_STATUS_BMP_HEADER_INVALID_MEMBER_BI_COLOR_USED,
  FILE_READ_STATUS_BMP_HEADER_INVALID_MEMBER_BI_IMPORTANT_COLORS,
  FILE_READ_STATUS_BMP_HEADER_DATA_OFFSET_ERROR,
  FILE_READ_STATUS_IMAGE_CREATION_FROM_BMP_FILE_FAILED,
  FILE_READ_STATUS_EXPECTED_PIXEL_DATA_OF_BMP_FILE_CROSSES_END_OF_FILE
};

enum file_read_status opened_bmp_file_to_struct_image(
  FILE *const input_bmp_file,
  struct image *const output_image
);

#endif // OPENED_FILE_TO_STRUCT_IMAGE_H
