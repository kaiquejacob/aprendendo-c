#include <stdio.h>
#include <string.h>

#define MAX_ALUNOS 100
#define DIAS 7

const char nomes_dias[DIAS][15] = {
    "Segunda", "Terca", "Quarta", 
    "Quinta", "Sexta", "Sabado", "Domingo"
};

typedef struct {
    int id;
    char nome[60];
    int senha; 
    int unidade; 
    float peso_inicial;
    float peso_atual;
    float altura;
    int treino[DIAS];
    char descricao_treino[DIAS][50]; 
    int dias_atraso;
} Aluno;

Aluno alunos[MAX_ALUNOS];
int total = 0;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int validarSenha(int indice) {
    int senha_digitada;
    printf("PIN do aluno (numerico, 4 digitos): ");
    if (scanf("%d", &senha_digitada) != 1) {
        limparBuffer();
        printf("Valor invalido. Digite apenas numeros.\n");
        return 0;
    }
    
    if (alunos[indice].senha == senha_digitada) {
        return 1;
    } else {
        printf("PIN incorreto! Acesso negado.\n");
        return 0;
    }
}

void cadastrarAluno() {
    Aluno novo;
    int i;

    if (total >= MAX_ALUNOS) {
        printf("Limite de alunos atingido.\n");
        return;
    }

    printf("\n--- Novo Aluno ---\n");
    printf("Nome completo: ");
    fgets(novo.nome, 60, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    do {
        printf("Defina um PIN numerico de acesso (exatamente 4 digitos, de 1000 a 9999): ");
        if (scanf("%d", &novo.senha) != 1) {
            limparBuffer();
            novo.senha = 0;
        }
        if (novo.senha < 1000 || novo.senha > 9999) {
            printf("Valor invalido. O PIN deve ter 4 digitos invalidando zeros a esquerda.\n");
        }
    } while (novo.senha < 1000 || novo.senha > 9999);

    do {
        printf("Unidade (1-Jaguare, 2-Cotia, 3-Osasco): ");
        if (scanf("%d", &novo.unidade) != 1) {
            limparBuffer();
            novo.unidade = 0;
        }
        if (novo.unidade < 1 || novo.unidade > 3) {
            printf("Valor invalido. Escolha 1, 2 ou 3.\n");
        }
    } while (novo.unidade < 1 || novo.unidade > 3);

    do {
        printf("Altura (em metros, ex: 1.75): ");
        if (scanf("%f", &novo.altura) != 1) {
            limparBuffer();
            novo.altura = 0;
        }
        if (novo.altura <= 0) {
            printf("Valor invalido. A altura deve ser maior que zero.\n");
        }
    } while (novo.altura <= 0);

    do {
        printf("Peso inicial (kg): ");
        if (scanf("%f", &novo.peso_inicial) != 1) {
            limparBuffer();
            novo.peso_inicial = 0;
        }
        if (novo.peso_inicial <= 0) {
            printf("Valor invalido. O peso deve ser maior que zero.\n");
        }
    } while (novo.peso_inicial <= 0);
    
    do {
        printf("Dias de atraso da mensalidade (0 se estiver em dia): ");
        if (scanf("%d", &novo.dias_atraso) != 1) {
            limparBuffer();
            novo.dias_atraso = -1;
        }
        if (novo.dias_atraso < 0) {
            printf("Valor invalido. Os dias de atraso nao podem ser negativos.\n");
        }
    } while (novo.dias_atraso < 0);

    for(i = 0; i < DIAS; i++) {
        novo.treino[i] = 0;
        strcpy(novo.descricao_treino[i], "Sem treino");
    }

    novo.id = total + 1;
    novo.peso_atual = novo.peso_inicial;

    alunos[total] = novo;
    total++;
    printf("Aluno ID %d cadastrado com sucesso.\n", novo.id);
}

void cadastrarTreino() {
    int id, i;
    printf("\nID do aluno: ");
    if (scanf("%d", &id) != 1) {
        limparBuffer();
        printf("Valor invalido. Digite apenas numeros.\n");
        return;
    }

    if (id < 1 || id > total) {
        printf("Aluno nao encontrado.\n");
        return;
    }

    id--;
    if (!validarSenha(id)) return;

    printf("\n--- Agenda de Treino para %s ---\n", alunos[id].nome);
    for (i = 0; i < DIAS; i++) {
        do {
            printf("%s treina? (1-Sim, 0-Nao): ", nomes_dias[i]);
            if (scanf("%d", &alunos[id].treino[i]) != 1) {
                limparBuffer();
                alunos[id].treino[i] = -1;
            }
            if (alunos[id].treino[i] != 0 && alunos[id].treino[i] != 1) {
                printf("Valor invalido. Digite 1 para Sim ou 0 para Nao.\n");
            }
        } while (alunos[id].treino[i] != 0 && alunos[id].treino[i] != 1);
        
        limparBuffer(); 
        
        if(alunos[id].treino[i] == 1) {
            printf("  Escreva o treino: ");
            fgets(alunos[id].descricao_treino[i], 50, stdin);
            alunos[id].descricao_treino[i][strcspn(alunos[id].descricao_treino[i], "\n")] = '\0';
        } else {
            strcpy(alunos[id].descricao_treino[i], "Descanso");
        }
    }
    
    printf("Treino salvo com sucesso.\n");
}

void registrarPeso() {
    int id;
    printf("\nID do aluno: ");
    if (scanf("%d", &id) != 1) {
        limparBuffer();
        printf("Valor invalido. Digite apenas numeros.\n");
        return;
    }

    if (id < 1 || id > total) {
        printf("Aluno nao encontrado.\n");
        return;
    }

    id--;
    if (!validarSenha(id)) return;

    do {
        printf("Novo peso (kg): ");
        if (scanf("%f", &alunos[id].peso_atual) != 1) {
            limparBuffer();
            alunos[id].peso_atual = 0;
        }
        if (alunos[id].peso_atual <= 0) {
            printf("Valor invalido. O peso deve ser maior que zero.\n");
        }
    } while (alunos[id].peso_atual <= 0);

    printf("Peso atualizado com sucesso.\n");
}

void consultarRecomendacaoNutricional() {
    int id;
    float imc;
    
    printf("\nID do aluno: ");
    if (scanf("%d", &id) != 1) {
        limparBuffer();
        printf("Valor invalido. Digite apenas numeros.\n");
        return;
    }

    if (id < 1 || id > total) {
        printf("Aluno nao encontrado.\n");
        return;
    }

    id--;
    if (!validarSenha(id)) return;
    
    if (alunos[id].altura <= 0) {
        printf("Altura invalida cadastrada.\n");
        return;
    }

    imc = alunos[id].peso_atual / (alunos[id].altura * alunos[id].altura);

    printf("\n--- Recomendacao para %s ---\n", alunos[id].nome);
    printf("Peso Atual: %.2f kg | Altura: %.2f m | IMC: %.2f\n", 
           alunos[id].peso_atual, alunos[id].altura, imc);
    
    if (imc < 18.5) {
        printf("Status: Baixo peso.\n");
        printf("Objetivo: Ganho de Massa.\n");
        printf("Recomendacao: 3000 kcal/dia. Carboidratos complexos e gorduras boas.\n");
    } else if (imc >= 18.5 && imc < 25.0) {
        printf("Status: Peso normal.\n");
        printf("Objetivo: Manutencao e Hipertrofia.\n");
        printf("Recomendacao: 2500 kcal/dia. Balancear carboidratos e proteinas.\n");
    } else {
        printf("Status: Sobrepeso/Obesidade.\n");
        printf("Objetivo: Deficit Calorico.\n");
        printf("Recomendacao: 2000 kcal/dia. Proteinas magras, evitar doce.\n");
    }
    
    printf("Agua recomendada: %.2f Litros por dia.\n", alunos[id].peso_atual * 0.035);
}

void listarAlunos() {
    int i;
    printf("\n--- Lista de Alunos (Resumo) ---\n");
    for (i = 0; i < total; i++) {
        printf("ID: %d | %s | Unidade: ", alunos[i].id, alunos[i].nome);
        
        if (alunos[i].unidade == 1) printf("Jaguare");
        else if (alunos[i].unidade == 2) printf("Cotia");
        else printf("Osasco");
        
        printf(" | Altura: %.2fm | Peso Atual: %.2f kg\n", alunos[i].altura, alunos[i].peso_atual);
    }
}

void buscarAluno() {
    int id, i;
    printf("\nID do aluno: ");
    if (scanf("%d", &id) != 1) {
        limparBuffer();
        printf("Valor invalido. Digite apenas numeros.\n");
        return;
    }

    if (id < 1 || id > total) {
        printf("Aluno nao encontrado.\n");
        return;
    }

    id--;
    if (!validarSenha(id)) return;

    printf("\n--- Dados do Aluno ---\n");
    printf("Nome: %s\n", alunos[id].nome);
    printf("Unidade: ");
    if (alunos[id].unidade == 1) printf("Jaguare\n");
    else if (alunos[id].unidade == 2) printf("Cotia\n");
    else printf("Osasco\n");
    
    printf("Altura: %.2f m\n", alunos[id].altura);
    printf("Peso Inicial: %.2f | Atual: %.2f\n", 
           alunos[id].peso_inicial, alunos[id].peso_atual);
    printf("Atraso mensalidade: %d dia(s)\n", alunos[id].dias_atraso);
    
    printf("Agenda da Semana:\n");
    for (i = 0; i < DIAS; i++) {
        printf("  %s: %s\n", nomes_dias[i], alunos[id].descricao_treino[i]);
    }
}

void verificarMensalidadesEmAtraso() {
    int i;
    int encontrou_atraso = 0;
    
    printf("\n--- Mensalidades em Atraso ---\n");
    for (i = 0; i < total; i++) {
        if (alunos[i].dias_atraso > 0) {
            printf("ID %d - %s: %d dia(s) de atraso.\n", alunos[i].id, alunos[i].nome, alunos[i].dias_atraso);
            encontrou_atraso = 1;
        }
    }
    if (!encontrou_atraso) {
        printf("Nenhum aluno com mensalidade atrasada.\n");
    }
}

void salvarArquivo() {
    int j, i;
    FILE *arq = fopen("alunos.txt", "w");
    if (arq == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    for (j = 0; j < total; j++) {
        fprintf(arq, "--- Dados do Aluno ---\n");
        fprintf(arq, "ID: %d\n", alunos[j].id);
        fprintf(arq, "Nome: %s\n", alunos[j].nome);
        
        fprintf(arq, "Unidade: ");
        if (alunos[j].unidade == 1) fprintf(arq, "Jaguare\n");
        else if (alunos[j].unidade == 2) fprintf(arq, "Cotia\n");
        else fprintf(arq, "Osasco\n");
        
        fprintf(arq, "Altura: %.2f m\n", alunos[j].altura);
        fprintf(arq, "Peso Inicial: %.2f | Atual: %.2f\n", 
                alunos[j].peso_inicial, alunos[j].peso_atual);
        fprintf(arq, "Atraso mensalidade: %d dia(s)\n", alunos[j].dias_atraso);
        
        fprintf(arq, "Agenda da Semana:\n");
        for (i = 0; i < DIAS; i++) {
            fprintf(arq, "  %s: %s\n", nomes_dias[i], alunos[j].descricao_treino[i]);
        }
        fprintf(arq, "\n");
    }
    
    fclose(arq);
    printf("Dados salvos em alunos.txt no formato de relatorio.\n");
}

int main() {
    int opcao;

    do {
        printf("\n===== BeyondFit - Menu Principal =====\n");
        printf("1 - Cadastrar novo aluno\n");
        printf("2 - Cadastrar/Alterar treino de aluno\n");
        printf("3 - Registrar novo peso\n");
        printf("4 - Listar todos os alunos\n");
        printf("5 - Buscar aluno por ID\n");
        printf("6 - Consultar recomendacao nutricional\n");
        printf("7 - Verificar mensalidades em atraso\n");
        printf("8 - Gerar relatorio e salvar arquivo\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        if (scanf("%d", &opcao) != 1) {
            limparBuffer();
            printf("Opcao invalida. Digite um numero do menu.\n");
            opcao = -1;
            continue;
        }
        limparBuffer(); 

        switch (opcao) {
            case 1: cadastrarAluno(); break;
            case 2: cadastrarTreino(); break;
            case 3: registrarPeso(); break;
            case 4: listarAlunos(); break;
            case 5: buscarAluno(); break;
            case 6: consultarRecomendacaoNutricional(); break;
            case 7: verificarMensalidadesEmAtraso(); break;
            case 8: salvarArquivo(); break;
            case 0: printf("Encerrando...\n"); break;
            default: printf("Opcao invalida. Escolha um numero do menu.\n");
        }
    } while (opcao != 0);

    return 0;
}