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
    table_name[length] = '\0';
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
    tff[length] = '\0';
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

void add_table_to_database(struct Database* database, struct Table* table)
{
    // database->tables = realloc(database->tables, sizeof(struct Table*) * (database->table_count + 1));
    // database->tables[database->table_count] = table;
    // database->table_count++;
    struct TableListNode* new_node = malloc(sizeof(struct TableListNode));
    new_node->table = table;
    new_node->next = NULL;
    if (database->head == NULL)
    {
        database->head = new_node;
    }
    else
    {
        struct TableListNode* curr_node = database->head;
        while (curr_node->next != NULL)
        {
            curr_node = curr_node->next;
        }
        curr_node->next = new_node;
    }
}

// Get the table from the database using the name
struct Table* get_table_from_name(struct Database* database, char* table_name) 
{
    struct TableListNode* curr_node = database->head;
    while (curr_node != NULL)
    {
        if (strcmp(curr_node->table->name, table_name) == 0) return curr_node->table;
        curr_node = curr_node->next;
    }
    return NULL;
}

// Get the table from the database using the index
struct Table* get_table_from_index(struct Database* database, int index) 
{
    struct TableListNode* curr_node = database->head;
    int counter = 0;
    while (curr_node != NULL)
    {
        if (counter == index) return curr_node->table;
        curr_node = curr_node->next;
        counter++;
    }
    return NULL;
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
        char* table_name = get_database_table_name(database_main_read_only, cum_offset, len+1);
        printf("%s\n", table_name);
        cum_offset += len + NULL_OFFSET;
        len = get_database_tff_length(database_main_read_only, cum_offset);
        char* tff = get_database_tff(database_main_read_only, cum_offset, len+1);
        printf("%s\n", tff);
        cum_offset += len + NULL_OFFSET;
        int16_t row_offset_id = get_database_row_offset_id(database_main_read_only, cum_offset);
        printf("%d\n", row_offset_id);
        cum_offset += FILE_ID_OFFSET;

        struct Table* table = init_table(tff, table_name, row_offset_id);
        add_table_to_database(database, table);
    }

    return database;
}