#include <stdio.h>

int main()
{
    int contador, tabuada, resultado;

    printf("Valor da tabuada: ");
    scanf("%d", &tabuada);

    for (contador = 1; contador <= 10; contador++)
    {
        resultado = contador*tabuada;
        printf("O valor de %d vezes %d e: %d\n", contador, tabuada, resultado);
    }

    return 0;
}