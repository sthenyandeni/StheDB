#include "database.h"

int main(int argc, char const *argv[])
{
    struct Database* db =  database_init();
    printf("Database name: %s\n", db->name);
    return 0;
}