#ifndef TABLE_H
#define TABLE_H

#include "types.h"
#include <stdio.h>
#include <stdlib.h>

struct Table* init_table(char* filename, char* name, int16_t offset_file_id);

#endif