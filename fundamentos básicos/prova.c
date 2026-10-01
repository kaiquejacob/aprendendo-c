#include <stdio.h>

int main()
{
    float nota_final, nota1, nota2;

    printf("Nota 1: ");
    scanf("%f", &nota1);

    printf("Nota 2: ");
    scanf("%f", &nota2);

    nota_final = (nota1 + nota2) / 2;

    if(nota_final >= 6)
    {
        printf("Parabens, voce foi aprovado!Sua media final foi %f", nota_final);
    }
    else
    {
        printf("Voce foi reprovado!Sua media final foi %f", nota_final);
    }

    return 0;
}
