#include <stdio.h>

int calculadora()
{
    float salario, recolhimento;

    printf("Informe o salario recebido: ");
    scanf("%f", &salario);

    if (salario < 1903.98)
    {
        printf("\nVoce esta isento!");
    }else if (salario > 1903.98 && salario <= 2826.65)
    {
        recolhimento = (salario*7.5/100) - 142.80;
        printf("Voce devera recolher %f", recolhimento);
    }else if (salario > 2826.65 && salario <= 3751.05)
    {
        recolhimento = (salario*15/100) - 354.80;
        printf("Voce devera recolher %f", recolhimento);
    }else if (salario > 3751.05 && salario <= 4664.68)
    {
        recolhimento = (salario*22.5/100) - 636.13;
        printf("Voce devera recolher %f", recolhimento);
    }else if (salario > 4664.68)
    {
        recolhimento = (salario*27.5/100) - 869.36;
        printf("Voce devera recolher %f", recolhimento);
    }

    return 0;
}