#include "token.h"

const char* get_token_type_name(TOKEN_TYPE token_type) {
    switch (token_type) {
        case SPACE: return "SPACE";
        case IDENTIFIER: return "IDENTIFIER";
        case STRINGLITERAL: return "STRINGLITERAL";
        case INTEGERLITERAL: return "INTEGERLITERAL";
        case FLOATLITERAL: return "FLOATLITERAL";
        case BOOLEANLITERAL: return "BOOLEANLITERAL";
        case COLON: return "COLON";
        case SEMICOLON: return "SEMICOLON";
        case COMMA: return "COMMA";
        case NEWLINE: return "NEWLINE";
        case EQ: return "EQ";
        case NE: return "NE";
        case LT: return "LT";
        case LE: return "LE";
        case GT: return "GT";
        case GE: return "GE";
        case AND: return "AND";
        case OR: return "OR";
        case LIKE: return "LIKE";
        case OPENBRACKET: return "OPENBRACKET";
        case CLOSEDBRACKET: return "CLOSEDBRACKET";
        case DOT: return "DOT";
        case SELECT: return "SELECT";
        case INSERT: return "INSERT";
        case DELETE: return "DELETE";
        case UPDATE: return "UPDATE";
        case FROM: return "FROM";
        case WHERE: return "WHERE";
        case VALUES: return "VALUES";
        default: return NULL;
    }
}