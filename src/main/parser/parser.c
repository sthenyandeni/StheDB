#include "parser.h"

void push_token(struct Token ***token_list, struct Token **token, int *token_list_size) {
    if ((*token)->token_type != SPACE) {
        if (*token_list == NULL) 
            *token_list = malloc(sizeof(struct Token*) * 1);
        else 
            *token_list = realloc(*token_list, sizeof(struct Token*) * ((*token_list_size) + 1));

        (*token_list)[(*token_list_size)] = *token;
        (*token_list_size)++;

        if ((*token)->token_type == IDENTIFIER) {
            if (strcmp((*token)->token_text,"AND") == 0) (*token)->token_type = AND;
            else if (strcmp((*token)->token_text,"OR") == 0) (*token)->token_type = OR;
            else if (strcmp((*token)->token_text,"SELECT") == 0) (*token)->token_type = SELECT;
            else if (strcmp((*token)->token_text, "INSERT") == 0) (*token)->token_type = INSERT;
            else if (strcmp((*token)->token_text, "FROM") == 0) (*token)->token_type = FROM;
            else if (strcmp((*token)->token_text, "WHERE") == 0) (*token)->token_type = WHERE;
            else if (strcmp((*token)->token_text, "VALUES") == 0) (*token)->token_type = VALUES;
        }

        *token = malloc(sizeof(struct Token));
        (*token)->token_text = malloc(sizeof(char));
        strcpy((*token)->token_text, "");
        (*token)->token_type = SPACE;
    }  
}

void push_string(char **str, char* ch) {
    (*str) = realloc(*str, strlen(*str) + 1);
    strcat(*str, ch);
}

void print_tokens(struct Token **token_list, int token_count) {
    for (int i = 0; i < token_count; i++) {
        struct Token *token = token_list[i];
        printf("\n***** Token %d *****\n", i + 1);
        printf("Text: %s\n", token->token_text);
        printf("Type: %s\n\n", get_token_type_name(token->token_type));
    }
}

void free_tokens(struct Token ***token_list, int token_count) {
    for (int i = 0; i < token_count; i++) {
        struct Token *token = (*token_list)[i];

        free(token->token_text);
        token->token_text = NULL;

        free(token);
        (*token_list)[i] = NULL;
    }
    free(*token_list);
    printf("!!!!! ALL TOKENS FREED !!!!!\n");
}

void parse(char* program, u_int64_t length) {
    struct Token **token_list = NULL;
    struct Token *current_token = malloc(sizeof(struct Token));
    int token_list_size = 0;

    current_token->token_text = malloc(sizeof(char));
    strcpy(current_token->token_text, "");
    current_token->token_type = SPACE;

    for (int i = 0; i < length; i++) {
        char elem[2] = {program[i], '\0'};
        switch (current_token->token_type) {
            case STRINGLITERAL:
                if (elem[0] == '\"') {
                    // push_string(&(current_token->token_text), elem);
                    push_token(&token_list, &current_token, &token_list_size);
                }
                else push_string(&(current_token->token_text), elem);
                break;
            default:
                switch (elem[0]) {
                    case '0':
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                        if (current_token->token_type == SPACE) {
                            push_string(&(current_token->token_text), elem);
                            current_token->token_type = INTEGERLITERAL;
                        }
                        else {
                            push_string(&(current_token->token_text), elem);
                        }
                        break;
                    case '.':
                        if (current_token->token_type == INTEGERLITERAL) {
                            push_string(&(current_token->token_text), elem);
                            current_token->token_type = FLOATLITERAL;
                        }
                        else {
                            push_token(&token_list, &current_token, &token_list_size);
                            push_string(&(current_token->token_text), elem);
                            current_token->token_type = DOT;
                            push_token(&token_list, &current_token, &token_list_size);
                        }
                        break;
                    case '\n':
                    case '\r':
                    case ' ':
                        push_token(&token_list, &current_token, &token_list_size);
                        break;
                    case '"':
                        push_token(&token_list, &current_token, &token_list_size);
                        // push_string(&(current_token->token_text), elem);
                        current_token->token_type = STRINGLITERAL;
                        break;
                    case ';':
                        push_token(&token_list, &current_token, &token_list_size);
                        push_string(&(current_token->token_text), elem);
                        current_token->token_type = SEMICOLON;
                        push_token(&token_list, &current_token, &token_list_size);
                        break;
                    case '=':
                        push_token(&token_list, &current_token, &token_list_size);
                        push_string(&(current_token->token_text), elem);
                        current_token->token_type = EQ;
                        push_token(&token_list, &current_token, &token_list_size);
                        break;
                    case '>':
                        push_token(&token_list, &current_token, &token_list_size);
                        push_string(&(current_token->token_text), elem);
                        current_token->token_type = GT;
                        push_token(&token_list, &current_token, &token_list_size);
                        break;
                    case '<':
                        push_token(&token_list, &current_token, &token_list_size);
                        push_string(&(current_token->token_text), elem);
                        current_token->token_type = LT;
                        push_token(&token_list, &current_token, &token_list_size);
                        break;
                    case '(':
                        push_token(&token_list, &current_token, &token_list_size);
                        push_string(&(current_token->token_text), elem);
                        current_token->token_type = OPENBRACKET;
                        push_token(&token_list, &current_token, &token_list_size);
                        break;
                    case ')':
                        push_token(&token_list, &current_token, &token_list_size);
                        push_string(&(current_token->token_text), elem);
                        current_token->token_type = CLOSEDBRACKET;
                        push_token(&token_list, &current_token, &token_list_size);
                        break;
                    case ',':
                        push_token(&token_list, &current_token, &token_list_size);
                        push_string(&(current_token->token_text), elem);
                        current_token->token_type = COMMA;
                        push_token(&token_list, &current_token, &token_list_size);
                        break;
                    default:
                        switch (current_token->token_type) {
                            case SPACE:
                            case INTEGERLITERAL:
                                push_token(&token_list, &current_token, &token_list_size);
                                current_token->token_type = IDENTIFIER;
                                push_string(&(current_token->token_text), elem);
                                break;
                            default:
                                push_string(&(current_token->token_text), elem);
                                break;
                        }
                        break;
                }   
                break;
        }
        
    }

    print_tokens(token_list, token_list_size);
    free_tokens(&token_list, token_list_size);
}