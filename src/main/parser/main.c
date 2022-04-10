#include <stdio.h>
#include "parser.h"

int main(void) {
    FILE* sample_file = fopen("sample.stheql", "r");
    fseek(sample_file, 0, SEEK_END);
    long file_len = ftell(sample_file);

    char* file_content = malloc(sizeof(char) * (file_len + 1));
    fseek(sample_file, 0, SEEK_SET);
    fread(file_content, file_len, 1, sample_file);

    printf("%s\n", file_content);

    // parse("SELECT \"Hello\" \"Hi\"", 19);
    parse(file_content, file_len);

    fclose(sample_file);
    return 0;
};