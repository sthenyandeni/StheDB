#include "database.h"
#include "table.h"
#include "engine.h"

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

    void** data = select_raw(db, "users");
    print_select("users", db, data, 2);

    int count = 5;

    printf("Inserting %d records...\n", count);

    char* attr_1 = "id";
    char* attr_2 = "first_name";
    char* attr_3 = "last_name";
    char* attr_4 = "email_address";
    char* attr_5 = "admin";

    int64_t* value_1 = (int64_t*)malloc(sizeof(int64_t));
    *value_1 = 100;
    char* value_2 = "John";
    char* value_3 = "Doe";
    char* value_4 = "johndoe@email.com";
    int8_t* value_5 = (int8_t*)malloc(sizeof(int8_t));
    *value_5 = 1;

    char** attr_names = malloc(sizeof(char*) * count);
    attr_names[0] = attr_1;
    attr_names[1] = attr_2;
    attr_names[2] = attr_3;
    attr_names[3] = attr_4;
    attr_names[4] = attr_5;

    void** values = malloc(sizeof(void*) * count);
    values[0] = (void*)value_1;
    values[1] = value_2;
    values[2] = value_3;
    values[3] = value_4;
    values[4] = (void*)value_5;

    insert_single(db, "users", attr_names, values);
    insert_single(db, "users", attr_names, values);
    insert_single(db, "users", attr_names, values);
    insert_single(db, "users", attr_names, values);
    insert_single(db, "users", attr_names, values);
    insert_single(db, "users", attr_names, values);
    insert_single(db, "users", attr_names, values);

    printf("Inserted %d records...\n", count);

    data = select_raw(db, "users");
    print_select("users", db, data, 9);

    return 0;
}