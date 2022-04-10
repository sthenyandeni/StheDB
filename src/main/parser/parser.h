#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "token.h"

void parse(char* program, u_int64_t length);

#endif