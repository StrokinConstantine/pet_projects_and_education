#ifndef IMAGE_H
#define IMAGE_H

#include "pixel.h"
#include <inttypes.h>

struct image
{
	uint_fast64_t width;
    uint_fast64_t height;
	struct pixel* data;
};

enum image_creation_status
{
	IMAGE_CREATION_STATUS_SUCCESS = 0,
	IMAGE_CREATION_STATUS_MEMORY_ALLOCATION_FOR_IMAGE_DATA_FAILED
};

enum image_creation_status
        create_image(struct image *const image_pointer, const uint64_t width, const uint64_t height);

void delete_image(struct image *const image);

#endif // IMAGE_H
