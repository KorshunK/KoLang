#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"
#include "codegen.h"

int main() {
    FILE* file = fopen("main.ko", "r");
    if (!file) {
        fprintf(stderr, "Не удалось открыть main.ko\n");
        return 1;
    }
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);
    char* src = malloc(size + 1);
    fread(src, 1, size, file);
    src[size] = '\0';
    fclose(file);

    Lexer lexer;
    init_lexer(&lexer, src);
    Parser parser;
    parser_init(&parser, &lexer);
    ASTNode* ast = parse_program(&parser);

    FILE* out = fopen("output.c", "w");
    fprintf(out, "#include <stdio.h>\n#include <locale.h>\n\n");
    fprintf(out, "void runtime_print(const char* str) {\n printf(\"%%s\", str); \n}\n\n");
    generate_code(ast, out);
    fclose(out);
    free(src);
    system("pause");
    printf(u8"Сгенерирован C-код в output.c\n");
    return 0;
}
