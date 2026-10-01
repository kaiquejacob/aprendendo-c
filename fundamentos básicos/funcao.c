#include <stdio.h>

void imprimi(int a, int b)
{
    printf("O valor um e %d e o valor dois e %d", a, b);
}

int main()
{
    int i, j = 0;
    printf("Valor 1: ");
    scanf("%d", &i);
    printf("Valor 2: ");
    scanf("%d", &j);

    imprimi(i, j);
    return 0;
}