#include "engine.h"
#define OFFSET_FILE_ID_OFFSET 0
#define ROW_DATA_FILE_ID_OFFSET 2
#define CONTENT_OFFSET 64

int64_t swap_int64( int64_t val )
{
    val = ((val << 8) & 0xFF00FF00FF00FF00ULL ) | ((val >> 8) & 0x00FF00FF00FF00FFULL );
    val = ((val << 16) & 0xFFFF0000FFFF0000ULL ) | ((val >> 16) & 0x0000FFFF0000FFFFULL );
    return (val << 32) | ((val >> 32) & 0xFFFFFFFFULL);
}

FILE* get_offset_file(struct Table* t) {
    int id = t->offset_file_id;
    int id_len = (int)((ceil(log10(id)) + 1) * sizeof(char));
    char str[id_len+4];
    sprintf(str, "%d", id);
    strcat(str, ".sro");
    FILE* f = fopen(str, "r");
    return f;
}

int get_record_size(struct Table* t)
{
    int size = 0;
    for (int i = 0; i < t->attr_count; i++) {
        size += t->attributes[i]->size;
    }
    return size;
}

void select(struct Database* db, char* table) {
    struct Table* t = get_table_from_name(db, table);
    if (t == NULL) {
        printf("Table %s not found\n", table);
        return;
    }
    
    FILE* offset_file = get_offset_file(t);
    fseek(offset_file, CONTENT_OFFSET, SEEK_SET);

    int record_size = get_record_size(t);

    int64_t row_1_attr_1_offset = 0;
    fread(&row_1_attr_1_offset, sizeof(int64_t), 1, offset_file);
    row_1_attr_1_offset = swap_int64(row_1_attr_1_offset);
}