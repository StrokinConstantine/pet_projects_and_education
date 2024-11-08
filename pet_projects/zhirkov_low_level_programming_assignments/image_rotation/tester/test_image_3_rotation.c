#include <stdbool.h>
#include "test/image_rotation_tester.h"

int main()
{
  
	bool is_rotation_correct = test_image_rotation( 
		"tester/bmp_test_images/bmp_test_image_3/test_image_3.bmp", 
		"tester/bmp_test_images/bmp_test_image_3/expected_rotated_test_image_3.bmp"
	);
		
	if ( is_rotation_correct )
		return 0;
  return 1;
}
