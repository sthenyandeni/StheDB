#ifndef ENGINE_H
#define ENGINE_H

#include "types.h"
#include "database.h"
#include <math.h>
#include <stdio.h>

void** select_raw(struct Database* db, char* table);
void print_select(char* table, struct Database* db, void** select_data, int record_count);
void insert_single(struct Database* db, char* table, int count, char** attributes, void** values);

#endif