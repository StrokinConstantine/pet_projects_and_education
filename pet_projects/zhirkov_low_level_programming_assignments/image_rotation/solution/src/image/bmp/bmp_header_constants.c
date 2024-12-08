#include "image/bmp/bmp_header_constants.h"
#include <stdint.h>

const uint16_t BMP_HEADER_SIGNATURE = 0x4D42;
const uint32_t BMP_HEADER_RESERVED = 0;
const uint32_t BMP_HEADER_DATA_OFFSET = 54;
const uint32_t BMP_HEADER_BI_SIZE = 40;
const uint16_t BMP_HEADER_BI_PLANES = 1;
const uint16_t BMP_HEADER_BI_BIT_COUNT = 24;
const uint32_t BMP_HEADER_BI_COMPRESSION = 0;
const uint32_t BMP_HEADER_BI_X_PIXELS_PER_METER = 0;
const uint32_t BMP_HEADER_BI_Y_PIXELS_PER_METER = 0;
const uint32_t BMP_HEADER_BI_COLOR_USED = 0;
const uint32_t BMP_HEADER_BI_IMPORTANT_COLORS = 0;
