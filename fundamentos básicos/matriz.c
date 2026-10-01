#include <stdio.h>

int main()
{
    int matriz[4][4];
    int x, y, soma = 0;
    for (x = 0; x < 4; x++)
    {
        for ( y = 0; y < 4; y++)
        {
            scanf("%d", &matriz[x][y]);
        } 
    }
    
    for (x = 0; x < 4; x++)
    {
        for ( y = 0; y < 4; y++)
        {
            soma = soma + matriz[x][y];
        }
    }

    printf("O valor da soma e: %d", soma);

    return 0;
}