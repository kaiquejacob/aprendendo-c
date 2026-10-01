#include <stdio.h>

float recebimentos[10000][2];
float despesas[10000][2];

int num_recebimento = 0;
int num_despesas = 0;
int num_operacao = 0;

void add_recebimentos()
{
    float valores;

    printf("Valor recebido: ");
    scanf("%f", &valores);

    if (valores > 0)
    {
        recebimentos[num_recebimento][0] = num_operacao;
        recebimentos[num_recebimento][1] = valores;
        printf("Voce recebeu %.2f reais na operacao %d\n", valores, num_operacao);
        
        num_operacao++;
        num_recebimento++;
    }
}
void add_despesa()
{
    float valores;

    printf("Valor de despesa: ");
    scanf("%f", &valores);

    if (valores > 0)
    {
        despesas[num_despesas][0] = num_operacao;
        despesas[num_despesas][1] = -valores;
        
        printf("Voce teve uma despesa de %.2f reais na operacao %d\n", valores, num_operacao);
        
        num_operacao++;
        num_despesas++;
    }
}
void saldo()
{
    int i;
    float saldo = 0;

    for (i = 0; i < num_recebimento; i++)
    {
        saldo += recebimentos[i][1];
    }

    for (i = 0; i < num_despesas; i++)
    {
        saldo += despesas[i][1]; 
    }

    printf("\nSeu saldo é %.2f\n", saldo);
}
void extrato()
{
    int i;
    float saldo = 0;

    for (i = 0; i < num_recebimento; i++)
    {
        printf("Recebimento: %.2f\n", recebimentos[i][1]);
        saldo += recebimentos[i][1];
    }

    for (i = 0; i < num_despesas; i++)
    {
        printf("Despesa: %.2f\n", despesas[i][1]);
        saldo += despesas[i][1];
    }

    printf("O seu saldo é de %.2f\n", saldo);
}
int calculo_irpf()
{
    float salario, recolhimento;
    int i = 0;
    salario = 0;

    for(i=0; i < num_recebimento; i++)
    {
        salario = salario + recebimentos[i][1];
    }

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
void menu()
{
    int tmp = 1;
    int opcao = 0;
    while (tmp == 1)
    {
        printf("\n\nEntre a opção desejada.");
        printf("\nDigite 1 para adicionar um recebimento:");
        printf("\nDigite 2 para adicionar uma despesa:");
        printf("\nDigite 3 para o saldo:");
        printf("\nDigite 4 para o extrato:");
        printf("\nDigite 5 para calcular o IRPF:");
        printf("\nDigite 9 para sair:\n");

        scanf("%d", &opcao);

        switch(opcao)
        {
            case 1:
                add_recebimentos();
                break;
            case 2:
                add_despesa();
                break;
            case 3:
                saldo();
                break;
            case 4:
                extrato();
                break;
            case 5:
                calculo_irpf();
                break;
            case 9:
                printf("A aplicação esta sendo finalizada...");
                tmp = 0;
                break;
            default:
                printf("A opção inserida esta errada.\n");
                break;
        }

    }
    
}

int main()
{
    menu();
    return 0;
}