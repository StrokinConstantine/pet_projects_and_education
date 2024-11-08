#ifndef BMP_HEADER_CONSTANTS_H
#define BMP_HEADER_CONSTANTS_H

#include <stdint.h>

extern const uint16_t BMP_HEADER_SIGNATURE;
extern const uint32_t BMP_HEADER_RESERVED;
extern const uint32_t BMP_HEADER_DATA_OFFSET;
extern const uint32_t BMP_HEADER_BI_SIZE;
extern const uint16_t BMP_HEADER_BI_PLANES;
extern const uint16_t BMP_HEADER_BI_BIT_COUNT;
extern const uint32_t BMP_HEADER_BI_COMPRESSION;
extern const uint32_t BMP_HEADER_BI_X_PIXELS_PER_METER;
extern const uint32_t BMP_HEADER_BI_Y_PIXELS_PER_METER;
extern const uint32_t BMP_HEADER_BI_COLOR_USED;
extern const uint32_t BMP_HEADER_BI_IMPORTANT_COLORS;

#endif //BMP_HEADER_CONSTANTS_H
