#include "image/image.h"
#include "image/pixel.h"

#include <inttypes.h>
#include <malloc.h>



enum image_creation_status create_image(
    struct image* const image_pointer,
        const uint_fast64_t width,
        const uint_fast64_t height
)
{
    image_pointer->data = NULL;
	if (  width == 0 || height == 0 )
	{
		image_pointer->width = 0;
		image_pointer->height = 0;
		return IMAGE_CREATION_STATUS_SUCCESS;
	}

	image_pointer->width = width;
    image_pointer->height = height;  
    image_pointer->data = ( struct pixel* ) malloc( width * height * (uint_fast64_t)( sizeof(struct pixel) ) );
    if ( image_pointer->data == NULL )
		return IMAGE_CREATION_STATUS_MEMORY_ALLOCATION_FOR_IMAGE_DATA_FAILED;
    return IMAGE_CREATION_STATUS_SUCCESS;
}  

void delete_image(struct image* const image )
{  
    if ( image->data != NULL )
    {  
        free( image->data );
        image->data = NULL;  
    }  
    image->width = 0;  
    image->height = 0;  
}
