#include "database.h"
#define MAIN_SDM "main.sdm"
#define FILE_START_OFFSET 0
#define NULL_OFFSET 1
#define FILE_ID_OFFSET 2

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

int16_t get_database_row_offset_id(FILE* database_main, int offset)
{
    fseek(database_main, offset, SEEK_SET);
    int16_t row_offset_id = 0;
    fread(&row_offset_id, sizeof(int16_t), 1, database_main);
    // Convert big endian to little endian
    int16_t row_offset_id_big_to_little = (row_offset_id >> 8) | (row_offset_id << 8);
    return row_offset_id_big_to_little;
}

struct Database* database_init(void)
{
    FILE* database_main_read_only = fopen(MAIN_SDM, "r");
    struct Database* database = malloc(sizeof(struct Database));
    database->head = NULL;
    
    // Get database length name and store name in database_name variable
    int8_t database_name_len = get_database_name_length(database_main_read_only, FILE_START_OFFSET);
    char* database_name = malloc(database_name_len);
    fread(database_name, 1, database_name_len, database_main_read_only);

    // Store the name in database object
    database->name = database_name;

    // Get database table count and store in database_table_count variable
    int8_t database_table_count = get_database_table_count(database_main_read_only, database_name_len+1);

    // Store the table count in database object
    database->table_count = database_table_count;

    int32_t cum_offset = database_name_len+2;

    for (int i = 0; i < database_table_count; i++) {
        int8_t len = get_database_table_name_length(database_main_read_only, cum_offset);
        char* table_name = get_database_table_name(database_main_read_only, cum_offset, len);
        printf("%s\n", table_name);
        cum_offset += len + NULL_OFFSET;
        len = get_database_tff_length(database_main_read_only, cum_offset);
        char* tff = get_database_tff(database_main_read_only, cum_offset, len);
        printf("%s\n", tff);
        cum_offset += len + NULL_OFFSET;
        int16_t row_offset_id = get_database_row_offset_id(database_main_read_only, cum_offset);
        printf("%d\n", row_offset_id);
        cum_offset += FILE_ID_OFFSET;
    }

    return database;
}