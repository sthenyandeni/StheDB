#ifndef ENGINE_H
#define ENGINE_H

#include "types.h"
#include "database.h"
#include <math.h>
#include <stdio.h>

void** select_raw(struct Database* db, char* table);
void print_select_c(char* table, struct Database* db, void** select_data, int record_count);

#endif