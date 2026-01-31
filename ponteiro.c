#include <stdio.h>

int main() {
    int x = 10;
    int* p = &x;

    printf("Valor: %d\n", x);
    printf("Endereço de x: %p\n", (void*)&x);
    printf("Valor através do ponteiro: %d\n", *p);      
    printf("Endereço armazenado no ponteiro: %p\n", (void*)p);
    
    return 0;
}