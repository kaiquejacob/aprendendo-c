#include <stdio.h>

int main()
{
    float nota_final, nota1, nota2;
    int opcao;

    printf("Nota 1: ");
    scanf("%f", &nota1);

    printf("Nota 2: ");
    scanf("%f", &nota2);

    printf("Escolha 1 para calcular outra media ou 2 para sair: ");
    scanf("%d", &opcao);

    switch (opcao)
    {
    case 1:
        nota_final = (nota1 + nota2) / 2;

        if(nota_final >= 6)
        {
            printf("Parabens, voce foi aprovado!Sua media final foi %f", nota_final);
        }
        else
        {
            printf("Voce foi reprovado!Sua media final foi %f", nota_final);
        }
        break;
    
    default:
        break;
    }

    return 0;
}