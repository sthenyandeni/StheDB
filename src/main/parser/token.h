#ifndef TOKEN_H
#define TOKEN_H

#include <stdlib.h>

typedef enum TOKEN_TYPE {
    SPACE,
    IDENTIFIER,
    STRINGLITERAL,
    INTEGERLITERAL,
    FLOATLITERAL,
    BOOLEANLITERAL,
    COLON,
    SEMICOLON,
    COMMA,
    NEWLINE,
    EQ, // Equal to
    NE, // Not equals
    LT, // Less than
    LE, // Less than or equal to
    GT, // Greater than
    GE, // Greater than or equal to
    AND,
    OR,
    LIKE
    OPENBRACKET,
    CLOSEDBRACKET,
    DOT,
    SELECT,
    INSERT,
    DELETE,
    UPDATE,
    FROM,
    WHERE,
    VALUES
} TOKEN_TYPE;

const char* get_token_type_name(TOKEN_TYPE token_type);

struct Token {
    char* token_text;
    TOKEN_TYPE token_type;
};

#endif