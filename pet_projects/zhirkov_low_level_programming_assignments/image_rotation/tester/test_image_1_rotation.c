#include <stdbool.h>
#include "test/image_rotation_tester.h"

int main()
{
  
	bool is_rotation_correct = test_image_rotation( 
		"tester/bmp_test_images/bmp_test_image_1/test_image_1.bmp", 
		"tester/bmp_test_images/bmp_test_image_1/expected_rotated_test_image_1.bmp"
	);
		
	if ( is_rotation_correct )
		return 0;
  return 1;
}
