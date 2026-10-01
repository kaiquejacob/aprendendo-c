#include <stdio.h>

int main()
{
    int vetor[100], n, i, j, posicao, troca;

    printf("Tamanho do vetor: \n");
    scanf("%d", &n);

    for ( i = 0; i < n; i++)
    {
        scanf("%d", &vetor[i]);
    }

    for (i = 0; i < n; i++)
    {
        posicao = i;
        for (j = i; j < n; j++)
        {
            if(vetor[posicao] > vetor[j])
            posicao  = j;
        }
        if (posicao != i)
        {
            troca = vetor[i];
            vetor[i] = vetor[posicao];
            vetor[posicao] = troca;
        }
    }
    printf("O vetor foi ordenado\n");

    for ( i = 0; i < n; i++)
    {
        printf("%d\n", vetor[i]);
    }
    

    return 0;
}