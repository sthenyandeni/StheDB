#include "database.h"

int8_t get_database_name_length(FILE* database_main, int offset)
{
    fseek(database_main, offset, SEEK_SET);

    // Get size of name
    int8_t db_name_len = 0;
    do {
        char curr_ch = fgetc(database_main);
        if (curr_ch == '\0')
            break;
        db_name_len++;
    } while(1);
    fseek(database_main, offset, SEEK_SET);
    return db_name_len;
}

int8_t get_database_table_count(FILE* database_main, int offset)
{
    fseek(database_main, offset, SEEK_SET);
    int8_t len = fgetc(database_main);
    fseek(database_main, offset, SEEK_SET);
    return len;
}

int8_t get_database_table_name_length(FILE* database_main, int offset)
{
    fseek(database_main, offset, SEEK_SET);

    int8_t db_table_name_len = 0;
    do {
        char curr_ch = fgetc(database_main);
        if (curr_ch == '\0')
            break;
        db_table_name_len++;
    } while(1);
    fseek(database_main, offset, SEEK_SET);
    return db_table_name_len;
}

char* get_database_table_name(FILE* database_main, int offset, int length)
{
    fseek(database_main, offset, SEEK_SET);
    char* table_name = malloc(length);
    fread(table_name, 1, length, database_main);
    return table_name;
}

int8_t get_database_tff_length(FILE* database_main, int offset)
{
    fseek(database_main, offset, SEEK_SET);

    int8_t db_tff_len = 0;
    do {
        char curr_ch = fgetc(database_main);
        if (curr_ch == '\0')
            break;
        db_tff_len++;
    } while(1);
    fseek(database_main, offset, SEEK_SET);
    return db_tff_len;
}

char* get_database_tff(FILE* database_main, int offset, int length)
{
    fseek(database_main, offset, SEEK_SET);
    char* tff = malloc(length);
    fread(tff, 1, length, database_main);
    return tff;
}

struct Database* database_init(void)
{
    FILE* database_main_read_only = fopen("main.sdm", "r");
    struct Database* database = malloc(sizeof(struct Database));
    database->head = NULL;
    
    int8_t database_name_len = get_database_name_length(database_main_read_only, 0);
    char* database_name = malloc(database_name_len);
    fread(database_name, 1, database_name_len, database_main_read_only);
    //TODO: Comment this out
    //printf("%s\n", database_name);

    database->name = database_name;

    int8_t database_table_count = get_database_table_count(database_main_read_only, database_name_len+1);
    //printf("%d\n", database_table_count);

    database->table_count = database_table_count;

    int32_t cum_offset = database_name_len+2;

    for (int i = 0; i < database_table_count; i++) {
        int8_t len = get_database_table_name_length(database_main_read_only, cum_offset);
        char* table_name = get_database_table_name(database_main_read_only, cum_offset, len);
        printf("%s\n", table_name);
        cum_offset += len+1;
        len = get_database_tff_length(database_main_read_only, cum_offset);
        char* tff = get_database_tff(database_main_read_only, cum_offset, len);
        printf("%s\n", tff);
        cum_offset += len+1;
    }

    return database;
}