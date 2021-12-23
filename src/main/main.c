#include "database.h"
#include "table.h"
#include "engine.h"

extern int print_select();

int main(int argc, char const *argv[])
{
    struct Database* db =  database_init();
    printf("Database name: %s\n", db->name);

    // struct Table* table = get_table_from_index(db, 1);
    // printf("Table name: %s\n", table->name);
    // for (int i = 0; i < table->attr_count; i++) {
    //     printf("Attr name %d: %s\n", i, table->attributes[i]->name);
    //     printf("Attr size %d: %d\n", i, table->attributes[i]->size);
    //     printf("Attr type %d: %d\n", i, table->attributes[i]->type);
    // }

    //void** data = select_raw(db, "users");
    //print_select("users", db, data, 2);

    printf("Size: %ld", sizeof(struct Attribute));
    return 0;
}