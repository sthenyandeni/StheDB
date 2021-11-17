typedef struct Map {

} Map;

typedef struct Table {
    char* name;
    char** attributes;
} Table;

typedef struct TableListTable {
    Table* table;
    TableListTable* next;
} TableListTable;

typedef struct Database {
    TableListTable* head;
    char* name;
} Database;

typedef struct Engine {

} Engine;

int main(int argc, char const *argv[])
{
    return 0;
}