#include <stdio.h>
#include "imposto.c"
void menu1()
{
    int opcao = 0;

    printf("Digite 1 para calcular imposto: ");
    printf("\nDigite 2 para sair: ");
    scanf("%d", &opcao);

    switch (opcao)
    {
    case 1:
        calculadora();
        break;
    case 2:
        printf("A aplicacao sera finalizada");
        break;
    
    default:
        menu1();
        break;
    }
}