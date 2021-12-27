#ifndef TYPES_H
#define TYPES_H

#define NIL "\0"
#define MAX_VARCHAR_LENGTH 255

typedef enum ATTR_TYPE {VARCHAR = 0x00, INTEGER = 0x01, BOOLEAN = 0x02} ATTR_TYPE;

struct Attribute {
    char* name;
    ATTR_TYPE type;
    int size;
    int record_offset;
};

struct Table {
    char* name;
    struct Attribute** attributes;
    int attr_count;
    int offset_file_id;
};

struct TableListNode {
    struct Table* table;
    struct TableListNode* next;
};

struct Database {
    struct TableListNode* head;
    char* name;
    int table_count;
};

#endif