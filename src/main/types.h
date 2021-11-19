#ifndef TYPES_H
#define TYPES_H

struct Table {
    char* name;
    char** attributes;
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