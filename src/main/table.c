#include "table.h"

struct Table* init_table(char* filename, char* name, int16_t offset_file_id) {
    FILE* table_format = fopen(filename, "r");
    struct Table* table = malloc(sizeof(struct Table));
    table->name = name;
    table->offset_file_id = offset_file_id;

    fseek(table_format, 0, SEEK_SET);
    int8_t attr_count = fgetc(table_format);
    table->attr_count = attr_count;
    table->attributes = malloc(sizeof(struct Attribute*) * attr_count);

    //Ideally, this line would not be necessary
    //TODO: Explore storing everything in hash tables
    fseek(table_format, 1, SEEK_SET);
    for (int i = 0; i < attr_count; i++) {
        struct Attribute* attribute = malloc(sizeof(struct Attribute));

        int8_t attribute_name_length = fgetc(table_format);
        attribute->name = malloc((sizeof(char) * attribute_name_length) + 1);
        fread(attribute->name, sizeof(char), attribute_name_length, table_format);
        attribute->name[attribute_name_length] = '\0';
        
        int16_t attribute_type = fgetc(table_format);
        attribute->type = attribute_type;

        int16_t attribute_size = fgetc(table_format);
        attribute->size = attribute_size;
        
        table->attributes[i] = attribute;
    }

    return table;
}