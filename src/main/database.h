#ifndef DATABASE_H
#define DATABASE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "table.h"

struct Table* get_table_from_index(struct Database* database, int index);
struct Table* get_table_from_name(struct Database* database, char* name);
struct Database* database_init(void);

#endif