#ifndef OUTPUT_MESSAGE_PRINTER_H
#define OUTPUT_MESSAGE_PRINTER_H

#include <inttypes.h>

void print_program_execution_status( 
  const uint_fast8_t general_error_code, 
  const uint_fast8_t internal_error_code 
);

#endif // OUTPUT_MESSAGE_PRINTER_H
