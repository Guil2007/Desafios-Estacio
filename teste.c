#include <stdio.h>

void dobrar(int* x) {
    *x = (*x) * 2;
    printf("Dentro da função dobrar: %d\n", *x);
}

int main() {
    int num = 5;
    printf("Antes de chamar dobrar: %d\n", num);
    
    dobrar(&num);
    
    printf("Depois de chamar dobrar: %d\n", num);
    return 0;
}
