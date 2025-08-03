#include "runtime.h"
#include <stdio.h>

void runtime_print(const char* str) {
    printf("%s", str);
}

int runtime_input(char* buf, int size) {
    if (fgets(buf, size, stdin)) {
        // Удаляем \n
        char* p = buf;
        while (*p) {
            if (*p == '\n') {
                *p = '\0';
                break;
            }
            p++;
        }
        return 1;
    }
    return 0;
}
