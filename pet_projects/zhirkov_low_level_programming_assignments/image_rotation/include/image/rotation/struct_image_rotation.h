#ifndef STRUCT_IMAGE_ROTATION_H
#define STRUCT_IMAGE_ROTATION_H

#include "image/image.h"

enum image_rotation_status
{
  IMAGE_ROTATION_STATUS_SUCCESS = 0,
  IMAGE_ROTATION_STATUS_ROTATED_IMAGE_CREATION_FAILED
};


enum image_rotation_status get_image_rotated_counterclockwise(
        const struct image* const source_image,
        struct image* const rotated_image,
        double angle
);




enum image_rotation_status
    get_image_turned_90_degrees_counterclockwise(
        const struct image* const,
        struct image* const
);

#endif // STRUCT_IMAGE_ROTATION_H
