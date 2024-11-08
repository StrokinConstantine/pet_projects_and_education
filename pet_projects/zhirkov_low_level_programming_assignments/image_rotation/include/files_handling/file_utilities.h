#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdbool.h>

bool is_file_has_at_least_n_bytes( FILE* const, const size_t );

bool are_files_binary_similar(const char* filename_1, const char* filename_2 );

#endif // UTIL_H
