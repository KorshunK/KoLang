#include "codegen.h"
#include <string.h>

void generate_code(ASTNode* ast, FILE* out) {
    if (!ast) return;

    switch (ast->kind) {
        case AST_FUNCTION:
            if (strcmp(ast->function_def.name, "main") == 0) {
                fprintf(out, "int main() {\n");
                fprintf(out, "setlocale(LC_ALL, \"\");\n");
                generate_code(ast->function_def.body, out);
                fprintf(out, "return 0;\n}\n");
            }
            break;

        case AST_CALL:
            if (strcmp(ast->call_expr.callee, "print") == 0) {
                if (ast->call_expr.argc == 1 && ast->call_expr.args[0]->kind == AST_STRING_LITERAL) {
                    fprintf(out, "runtime_print(u8\"%s\\n\");\n", ast->call_expr.args[0]->string_literal);
                }
            }
            break;

        case AST_STRING_LITERAL:
            // Не генерируем отдельно
            break;
    }
}
