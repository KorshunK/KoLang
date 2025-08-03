#include <stdio.h>
#include <locale.h>

void runtime_print(const char* str) {
 printf("%s", str); 
}

int main() {
setlocale(LC_ALL, "");
runtime_print(u8"Привет, мир!\n");
return 0;
}
