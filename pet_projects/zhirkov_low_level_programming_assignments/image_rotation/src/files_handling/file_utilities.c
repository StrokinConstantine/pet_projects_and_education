#include "files_handling/file_utilities.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool is_file_has_at_least_n_bytes( FILE* const file , const size_t n )
{
    if ( !file )
        return false;
    if ( fseek( file, 0, SEEK_END ) != 0 )
      return false;
    size_t file_size = (size_t) ftell(file);
    return file_size >= n;
}

bool are_files_binary_similar(const char* filename_1, const char* filename_2)
{
    FILE *f1 = fopen(filename_1, "rb");
    FILE *f2 = fopen(filename_2, "rb");
    if (f1 == NULL || f2 == NULL)
    {
        if ( f1 ) fclose(f1);
        if ( f2 ) fclose(f2);
        return false;
    }
    static const size_t BUFFER_SIZE = 4096;
    unsigned char buffer1[BUFFER_SIZE];
    unsigned char buffer2[BUFFER_SIZE];

    size_t bytesRead1, bytesRead2;
    do
    {
        bytesRead1 = fread(buffer1, 1, BUFFER_SIZE, f1);
        bytesRead2 = fread(buffer2, 1, BUFFER_SIZE, f2);
        if (bytesRead1 != bytesRead2 || memcmp(buffer1, buffer2, bytesRead1) != 0)
        {
            fclose(f1);
            fclose(f2);
            return false;
        }

    } while (bytesRead1 > 0 && bytesRead2 > 0);
    fclose(f1);
    fclose(f2);
    return true;
}
