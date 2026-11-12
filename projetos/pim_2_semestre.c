#include <stdio.h>
#include <string.h>

#define MAX_ALUNOS 100
#define DIAS 7

const char nomes_dias[DIAS][15] = {
    "Segunda", "Terca", "Quarta", 
    "Quinta", "Sexta", "Sabado", "Domingo"
};

const char nomes_unidades[3][15] = {
    "Jaguare", "Cotia", "Osasco"
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
} Aluno;

Aluno alunos[MAX_ALUNOS];
int total = 0;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void carregarDados() {
    FILE *arq = fopen("dados.txt", "r");
    if (arq == NULL) {
        return; 
    }

    total = 0;
    while (fscanf(arq, "%d\n", &alunos[total].id) == 1) {
        fgets(alunos[total].nome, 60, arq);
        alunos[total].nome[strcspn(alunos[total].nome, "\n")] = '\0';
        
        fscanf(arq, "%d\n", &alunos[total].senha);
        fscanf(arq, "%d\n", &alunos[total].unidade);
        fscanf(arq, "%f\n", &alunos[total].altura);
        fscanf(arq, "%f\n", &alunos[total].peso_inicial);
        fscanf(arq, "%f\n", &alunos[total].peso_atual);

        for (int i = 0; i < DIAS; i++) {
            fscanf(arq, "%d\n", &alunos[total].treino[i]);
            fgets(alunos[total].descricao_treino[i], 50, arq);
            alunos[total].descricao_treino[i][strcspn(alunos[total].descricao_treino[i], "\n")] = '\0';
        }
        total++;
    }

    fclose(arq);
    printf("Sistema: %d aluno(s) carregado(s) com sucesso.\n", total);
}

void salvarDados() {
    int j, i;
    FILE *arq = fopen("dados.txt", "w");
    if (arq == NULL) return;

    for (j = 0; j < total; j++) {
        fprintf(arq, "%d\n", alunos[j].id);
        fprintf(arq, "%s\n", alunos[j].nome);
        fprintf(arq, "%d\n", alunos[j].senha);
        fprintf(arq, "%d\n", alunos[j].unidade);
        fprintf(arq, "%.2f\n", alunos[j].altura);
        fprintf(arq, "%.2f\n", alunos[j].peso_inicial);
        fprintf(arq, "%.2f\n", alunos[j].peso_atual);

        for (i = 0; i < DIAS; i++) {
            fprintf(arq, "%d\n", alunos[j].treino[i]);
            fprintf(arq, "%s\n", alunos[j].descricao_treino[i]);
        }
    }
    fclose(arq);
}

void gerarRelatorio() {
    int j, i;
    FILE *arq = fopen("relatorio.txt", "w");
    if (arq == NULL) {
        printf("Erro ao criar o relatorio visual.\n");
        return;
    }

    for (j = 0; j < total; j++) {
        fprintf(arq, "--- Dados do Aluno ---\n");
        fprintf(arq, "ID: %d\n", alunos[j].id);
        fprintf(arq, "Nome: %s\n", alunos[j].nome);
        fprintf(arq, "Unidade: %s\n", nomes_unidades[alunos[j].unidade - 1]);
        fprintf(arq, "Altura: %.2f m\n", alunos[j].altura);
        fprintf(arq, "Peso Inicial: %.2f | Atual: %.2f\n", 
                alunos[j].peso_inicial, alunos[j].peso_atual);

        fprintf(arq, "Agenda da Semana:\n");
        for (i = 0; i < DIAS; i++) {
            fprintf(arq, "  %s: %s\n", nomes_dias[i], alunos[j].descricao_treino[i]);
        }
        fprintf(arq, "\n");
    }

    fclose(arq);
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

int localizarAluno() {
    int id_buscado, i, idx_encontrado = -1;
    
    printf("\nID do aluno: ");
    if (scanf("%d", &id_buscado) != 1) {
        limparBuffer();
        printf("Valor invalido. Digite apenas numeros.\n");
        return -1;
    }

    for (i = 0; i < total; i++) {
        if (alunos[i].id == id_buscado) {
            idx_encontrado = i;
            break;
        }
    }

    if (idx_encontrado == -1) {
        printf("Aluno nao encontrado.\n");
        return -1;
    }

    return idx_encontrado;
}

int autenticarAluno() {
    int idx_encontrado = localizarAluno();

    if (idx_encontrado == -1) {
        return -1;
    }

    if (!validarSenha(idx_encontrado)) {
        return -1;
    }

    return idx_encontrado;
}

void cadastrarAluno() {
    Aluno novo;
    int i, maior_id = 0;

    if (total >= MAX_ALUNOS) {
        printf("Limite de alunos atingido.\n");
        return;
    }

    printf("\n--- Novo Aluno ---\n");
    printf("Nome completo: ");
    fgets(novo.nome, 60, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    do {
        printf("Defina um PIN numerico de acesso (4 digitos, de 1000 a 9999): ");
        if (scanf("%d", &novo.senha) != 1) {
            limparBuffer();
            novo.senha = 0;
        }
        if (novo.senha < 1000 || novo.senha > 9999) {
            printf("Valor invalido. O PIN deve ter 4 digitos sem zeros a esquerda.\n");
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

    for (i = 0; i < DIAS; i++) {
        novo.treino[i] = 0;
        strcpy(novo.descricao_treino[i], "Sem treino");
    }

    for (i = 0; i < total; i++) {
        if (alunos[i].id > maior_id) {
            maior_id = alunos[i].id;
        }
    }
    
    novo.id = maior_id + 1;
    novo.peso_atual = novo.peso_inicial;

    alunos[total] = novo;
    total++;
    printf("Aluno ID %d cadastrado com sucesso.\n", novo.id);
    
    salvarDados();
    gerarRelatorio();
}

void atualizarAluno() {
    int id = autenticarAluno();
    int opcao_update;
    int alterou = 0;

    if (id == -1) return;

    do {
        printf("\n--- Atualizar Dados de %s ---\n", alunos[id].nome);
        printf("1 - Alterar Nome\n");
        printf("2 - Alterar Unidade\n");
        printf("3 - Alterar Altura\n");
        printf("4 - Alterar Peso Atual\n");
        printf("0 - Voltar ao menu principal\n");
        printf("Escolha o que deseja alterar: ");
        
        if (scanf("%d", &opcao_update) != 1) {
            limparBuffer();
            printf("Opcao invalida. Digite um numero.\n");
            opcao_update = -1;
            continue;
        }
        limparBuffer();

        switch (opcao_update) {
            case 1:
                printf("Novo nome completo: ");
                fgets(alunos[id].nome, 60, stdin);
                alunos[id].nome[strcspn(alunos[id].nome, "\n")] = '\0';
                printf("Nome atualizado com sucesso.\n");
                alterou = 1;
                break;
                
            case 2:
                do {
                    printf("Nova Unidade (1-Jaguare, 2-Cotia, 3-Osasco): ");
                    if (scanf("%d", &alunos[id].unidade) != 1) {
                        limparBuffer();
                        alunos[id].unidade = 0;
                    }
                    if (alunos[id].unidade < 1 || alunos[id].unidade > 3) {
                        printf("Valor invalido. Escolha 1, 2 ou 3.\n");
                    }
                } while (alunos[id].unidade < 1 || alunos[id].unidade > 3);
                printf("Unidade atualizada com sucesso.\n");
                alterou = 1;
                break;
                
            case 3:
                do {
                    printf("Nova altura (em metros, ex: 1.75): ");
                    if (scanf("%f", &alunos[id].altura) != 1) {
                        limparBuffer();
                        alunos[id].altura = 0;
                    }
                    if (alunos[id].altura <= 0) {
                        printf("Valor invalido. A altura deve ser maior que zero.\n");
                    }
                } while (alunos[id].altura <= 0);
                printf("Altura atualizada com sucesso.\n");
                alterou = 1;
                break;
                
            case 4:
                do {
                    printf("Novo peso atual (kg): ");
                    if (scanf("%f", &alunos[id].peso_atual) != 1) {
                        limparBuffer();
                        alunos[id].peso_atual = 0;
                    }
                    if (alunos[id].peso_atual <= 0) {
                        printf("Valor invalido. O peso deve ser maior que zero.\n");
                    }
                } while (alunos[id].peso_atual <= 0);
                printf("Peso atualizado com sucesso.\n");
                alterou = 1;
                break;
                
            case 0:
                printf("Retornando ao menu...\n");
                break;
                
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao_update != 0);

    if (alterou) {
        salvarDados();
        gerarRelatorio();
    }
}

void cadastrarTreino() {
    int id = localizarAluno();
    int i;

    if (id == -1) return;

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

        if (alunos[id].treino[i] == 1) {
            printf("  Escreva o treino: ");
            fgets(alunos[id].descricao_treino[i], 50, stdin);
            alunos[id].descricao_treino[i][strcspn(alunos[id].descricao_treino[i], "\n")] = '\0';
        } else {
            strcpy(alunos[id].descricao_treino[i], "Descanso");
        }
    }

    printf("Treino salvo com sucesso.\n");
    salvarDados();
    gerarRelatorio();
}

void consultarRecomendacaoNutricional() {
    int id = localizarAluno();
    float imc;

    if (id == -1) return;

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
        printf("ID: %d | %s | Unidade: %s | Altura: %.2fm | Peso Atual: %.2f kg\n", 
               alunos[i].id, 
               alunos[i].nome, 
               nomes_unidades[alunos[i].unidade - 1], 
               alunos[i].altura, 
               alunos[i].peso_atual);
    }
}

void buscarAluno() {
    int id = localizarAluno();
    int i;

    if (id == -1) return;

    printf("\n--- Dados do Aluno ---\n");
    printf("Nome: %s\n", alunos[id].nome);
    printf("Unidade: %s\n", nomes_unidades[alunos[id].unidade - 1]);
    printf("Altura: %.2f m\n", alunos[id].altura);
    printf("Peso Inicial: %.2f | Atual: %.2f\n", 
           alunos[id].peso_inicial, alunos[id].peso_atual);

    printf("Agenda da Semana:\n");
    for (i = 0; i < DIAS; i++) {
        printf("  %s: %s\n", nomes_dias[i], alunos[id].descricao_treino[i]);
    }
}

void deletarAluno() {
    int id = autenticarAluno();
    int i;

    if (id == -1) return;

    printf("Removendo o aluno: %s (ID: %d)...\n", alunos[id].nome, alunos[id].id);
    
    for (i = id; i < total - 1; i++) {
        alunos[i] = alunos[i + 1];
    }
    
    total--;
    printf("Aluno deletado com sucesso.\n");
    
    salvarDados();
    gerarRelatorio();
}

int main() {
    int opcao;

    carregarDados();

    do {
        printf("\n===== BeyondFit - Menu Principal =====\n");
        printf("1 - Cadastrar novo aluno\n");
        printf("2 - Atualizar dados do aluno\n");
        printf("3 - Cadastrar/Alterar treino\n");
        printf("4 - Listar todos os alunos\n");
        printf("5 - Buscar aluno por ID\n");
        printf("6 - Consultar recomendacao nutricional\n");
        printf("7 - Deletar aluno\n");
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
            case 2: atualizarAluno(); break;
            case 3: cadastrarTreino(); break;
            case 4: listarAlunos(); break;
            case 5: buscarAluno(); break;
            case 6: consultarRecomendacaoNutricional(); break;
            case 7: deletarAluno(); break;
            case 0: printf("Encerrando...\n"); break;
            default: printf("Opcao invalida. Escolha um numero do menu.\n");
        }
    } while (opcao != 0);

    return 0;
}
