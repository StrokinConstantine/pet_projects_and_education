#include "image/rotation/struct_image_rotation.h"
#include "constants.h"
#include "image/image.h"

#include <stdint.h>



static enum image_rotation_status get_image_turned_90_degrees_counterclockwise( const struct image* const source_image, struct image* const rotated_image );

enum image_rotation_status get_image_rotated_counterclockwise( const struct image* const source_image, struct image* const rotated_image, double angle )
{
	if ( ( angle - 90.0 ) < ROTATION_ANGLE_PRECISION_IN_DEGREES )
        return get_image_turned_90_degrees_counterclockwise( source_image, rotated_image );

    // for now, we can only rotate image on 90 degrees
    return IMAGE_ROTATION_STATUS_ROTATED_IMAGE_CREATION_FAILED;
}

static enum image_rotation_status
get_image_turned_90_degrees_counterclockwise( 
  const struct image* const source_image,
  struct image* const rotated_image 
)
{
  enum image_creation_status rotated_image_creation_status = create_image(
          rotated_image,
          source_image->height, // rotated image width
          source_image->width // rotated image height
  );
  
  if ( rotated_image_creation_status == IMAGE_CREATION_STATUS_MEMORY_ALLOCATION_FOR_IMAGE_DATA_FAILED )
    return IMAGE_ROTATION_STATUS_ROTATED_IMAGE_CREATION_FAILED;

  /*
  Description of how the loop works:
  
  Each "row" in the source image array we are copying to the column of the rotated image 
  array.
  First element of the row in source image corresponds to the "lowest" element in 
  the column of the rotated image.
  Rows in source image are iterated from the first ("the topmost") to the last 
  ("the bottommost").
  Columns in the rotated image are iterated from the "leftmost" to the "rightmost".
  */

  for ( uint64_t j = 0; j < source_image->height; j++ )
        for ( uint64_t i = 0; i < source_image->width; i++ )
            rotated_image->data[ ( source_image->width - 1 - i ) * source_image->height + j ]
            = source_image->data[ ( j * source_image->width ) + i ];

  return IMAGE_ROTATION_STATUS_SUCCESS;
}
