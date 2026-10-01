#include <stdio.h>

int main()
{
    int nota1, nota2;
    float media;
    char resp = 's';

    while (resp == 's')
    {
        printf("\r\nNota 1: ");
        scanf("%d", &nota1);
        printf("\r\nNota 2: ");
        scanf("%d", &nota2);

        media = (nota1 + nota2) / 2.0;

        printf("\r\nSua media e %f", media);

        printf("\r\nPara continuar digite s: ");
        scanf(" %c", &resp);
    }

return 0;
}