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

void print_void_value(void* value, int length, int8_t print_0) {
    for (int j = 0; j < length; j++) {
        u_int8_t c = ((u_int8_t*)value)[j];
        if (c == '\0' && !print_0) {
            continue;
        }
        printf("%02x", c);
    }
    printf("\n");
}

FILE* get_offset_file(struct Table* t, const char* flag) {
    int id = t->offset_file_id;
    int id_len = (int)((ceil(log10(id)) + 1) * sizeof(char));
    char str[id_len+4];
    sprintf(str, "%d", id);
    strcat(str, ".sro");
    FILE* f = fopen(str, flag);
    return f;
}

FILE* get_data_file(struct Table* t, const char* flag) {
    int id = t->offset_file_id;
    int id_len = (int)((ceil(log10(id)) + 1) * sizeof(char));
    char str[id_len+4];
    sprintf(str, "%d", id);
    strcat(str, ".srd");
    FILE* f = fopen(str, flag);
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

struct Attribute* get_attribute(struct Table* t, char* name)
{
    for (int i = 0; i < t->attr_count; i++) {
        if (strcmp(t->attributes[i]->name, name) == 0) {
            return t->attributes[i];
        }
    }
    return NULL;
}

void** select_raw(struct Database* db, char* table) {
    struct Table* t = get_table_from_name(db, table);
    if (t == NULL) {
        printf("Table %s not found\n", table);
        return NULL;
    }
    
    int SINGLE_RECORD_SIZE = get_record_size(t);

    FILE* offset_file = get_offset_file(t, "r");
    fseek(offset_file, 0, SEEK_END);
    int64_t offset_file_size = ftell(offset_file);
    fseek(offset_file, CONTENT_OFFSET, SEEK_SET);

    FILE* data_file = get_data_file(t, "r");

    int record_count = 0;
    void** records = malloc(0);
    
    int64_t current_file_offset = CONTENT_OFFSET;
    while (current_file_offset < offset_file_size) {
        int64_t current_record_offset = 0;
        void* record = malloc(SINGLE_RECORD_SIZE);

        for (int i = 0; current_record_offset < SINGLE_RECORD_SIZE; i++) {
            int attr_size = t->attributes[i]->size;

            // Get row and attribute offset for srd file
            int64_t file_offset = 0;
            fread(&file_offset, sizeof(int64_t), 1, offset_file);
            // file_offset = swap_int64(file_offset);
            
            // Get value from srd file using offset
            fseek(data_file, file_offset, SEEK_SET);
            void* value = malloc(attr_size);
            fread(value, attr_size, 1, data_file);

            //print_void_value(value, attr_size);
            for (int j = 0; j < attr_size; j++) {
                ((u_int8_t*)record)[current_record_offset + j] = ((u_int8_t*)value)[j];
            }

            current_record_offset += attr_size;
            current_file_offset += sizeof(int64_t);
        }
        record_count++;
        records = realloc(records, record_count * sizeof(void*));
        records[record_count - 1] = record;
    }
    fclose(offset_file);
    fclose(data_file);
    return records;
}

void print_select(char* table, struct Database* db, void** select_data, int record_count) {
    struct Table* t = get_table_from_name(db, table);
    if (t == NULL) {
        printf("Table %s not found\n", table);
        return;
    }
    printf("Printing records...\n");
    // For each record...
    for (int i = 0; i < record_count; i++) {
        printf("\nPrinting record %d...\n", i + 1);
        void* record = select_data[i];
        int attr_count = t->attr_count;

        // For each attribute...
        printf("Printing attributes...\n");
        for (int j = 0; j < attr_count; j++) {
            struct Attribute* attr = t->attributes[j];
            int offset = attr->record_offset;
            int size = attr->size;
            ATTR_TYPE type = attr->type;

            if (type == VARCHAR) {
                char* str = malloc((sizeof(char) * size) + 1);
                for (int k = 0; k < size; k++) {
                    char *c = malloc(sizeof(char) * 2);
                    c[0] = ((char*)record)[offset + k];
                    c[1] = '\0';
                    if (c[0] == '\0') continue;
                    strcat(str, c);
                }
                str[size] = '\0';
                printf("Attribute %d (%s, %d bytes, %d): %s\n", j + 1, attr->name, size, type, str);
            }
            else if (type == INTEGER) {
                char *strvalue = malloc(sizeof(unsigned char) * size);
                for (int k = 0; k < size; k++) {
                    char *c = malloc(sizeof(char) * 2);
                    c[0] = ((char*)record)[offset + k];
                    c[1] = '\0';
                    strcat(strvalue, c);
                }
                int val = *((int*)strvalue);
                printf("Attribute %d (%s, %d bytes, %d): %d\n", j + 1, attr->name, size, type, val);
            }
            else if (type == BOOLEAN) {
                u_int8_t val = 0;
                val = ((u_int8_t*)record)[offset];
                printf("Attribute %d (%s, %d byte, %d): %d\n", j + 1, attr->name, size, type, val);
            }
        }
    }
}


// Insert a single record into the table
void insert_single(struct Database* db, char* table, int count, char** attributes, void** values) {
    struct Table *t = get_table_from_name(db, table);
    if (t == NULL) {
        printf("Table %s not found\n", table);
        return;
    }

    // Get last offset in srd file
    FILE* data_file = get_data_file(t, "a+");
    FILE* offset_file = get_offset_file(t, "a+");

    // For each attribute being added to a new record
    for(int i = 0; i < count; i++) {
        struct Attribute* attr = get_attribute(t, attributes[i]);
        if (attr == NULL) {
            printf("Attribute %s not found\n", attributes[i]);
            return;
        }
        
        fseek(data_file, 0, SEEK_END);
        int64_t data_file_offset_start = ftell(data_file);

        // Write attribute value to srd file
        void* value = values[i];
        if (attr->type == VARCHAR) {
            int length = strlen((char*)value);
            if (length > MAX_VARCHAR_LENGTH) length = MAX_VARCHAR_LENGTH;
            for (int j = 0; j < attr->size - length; j++) fwrite(NIL, sizeof(char), 1, data_file);
            fwrite(value, sizeof(char), length, data_file);
        }
        else if (attr->type == BOOLEAN) {
            fwrite(value, sizeof(u_int8_t), 1, data_file);
        }
        else if (attr->type == INTEGER) {
            // TODO: Complete the INTEGER INVESTIGATION HERE
        }

        fwrite(&data_file_offset_start, sizeof(int64_t), 1, offset_file);
    }

    fclose(data_file);
    fclose(offset_file);
}