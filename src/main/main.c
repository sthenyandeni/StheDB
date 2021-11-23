#include "database.h"
#include "table.h"

int main(int argc, char const *argv[])
{
    struct Database* db =  database_init();
    printf("Database name: %s\n", db->name);

    struct Table* table = init_table("users.stf", "users");
    printf("Table name: %s\n", table->name);
    for (int i = 0; i < table->attr_count; i++) {
        printf("Attr name %d: %s\n", i, table->attributes[i]->name);
        printf("Attr size %d: %d\n", i, table->attributes[i]->size);
        printf("Attr type %d: %d\n", i, table->attributes[i]->type);
    }
    return 0;
}