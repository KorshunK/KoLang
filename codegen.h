#ifndef CODEGEN_H
#define CODEGEN_H

#include "parser.h"
#include <stdio.h>

void generate_code(ASTNode* ast, FILE* out);

#endif
