```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME_ARQUIVO 50
#define MAX_TAMANHO_LINHA 100

typedef struct {
    int bloco;
    int numero;
    int capacidade;
    int tipo;
    char horario[10];
} Sala;

typedef struct {
    char nome[50];
    int numero_alunos;
} Turma;

void ler_salas(char* nome_arquivo, Sala** salas, int* n_salas) {
    FILE* fp = fopen(nome_arquivo, "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nome_arquivo);
        exit(1);
    }
    int capacidade, tipo;
    char bloco[5], numero[5], horario[10];
    int i = 0;
    while (fgets(bloco, 5, fp)) {
        fgets(numero, 5, fp);
        fscanf(fp, "%d", &capacidade);
        fscanf(fp, "%d", &tipo);
        fgets(horario, 10, fp);
        horario[strcspn(horario, "\n")] = '\0';
        (*salas)[i].bloco = atoi(bloco);
        (*salas)[i].numero = atoi(numero);
        (*salas)[i].capacidade = capacidade;
        (*salas)[i].tipo = tipo;
        strcpy((*salas)[i].horario, horario);
        i++;
    }
    *n_salas = i;
    fclose(fp);
}

void ler_turmas(char* nome_arquivo, Turma** turmas, int* n_turmas) {
    FILE* fp = fopen(nome_arquivo, "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nome_arquivo);
        exit(1);
    }
    char nome[50];
    int numero_alunos;
    int i = 0;
    while (fscanf(fp, "%s %d", nome, &numero_alunos) != EOF) {
        strcpy((*turmas)[i].nome, nome);
        (*turmas)[i].numero_alunos = numero_alunos;
        i++;
    }
    *n_turmas = i;
    fclose(fp);
}

void escrever_horarios(char* nome_arquivo, Turma* turmas, int n_turmas) {
    FILE* fp = fopen(nome_arquivo, "w");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nome_arquivo);
        exit(1);
    }
    for (int i = 0; i < n_turmas; i++) {
        Turma turma = turmas[i];
        fprintf(fp, "%s:\n", turma.nome);
        for (int j = 0; j < 5; j++) {
            Sala sala = turma.salas[j];
            fprintf(fp, "\tSala %d-%d (%s): %s\n", sala.bloco, sala.numero, sala.horario, (
            sala.tipo == 0 ? "Teórica" : "Prática");
        }
        fprintf(fp, "\n");
}
fclose(fp);
}

int main() {
char nome_arquivo_salas[MAX_NOME_ARQUIVO] = "salas.txt";
char nome_arquivo_turmas[MAX_NOME_ARQUIVO] = "turmas.txt";
char nome_arquivo_horarios[MAX_NOME_ARQUIVO] = "horarios.txt";
Sala* salas = malloc(sizeof(Sala) * 100);
int n_salas = 0;
ler_salas(nome_arquivo_salas, &salas, &n_salas);

Turma* turmas = malloc(sizeof(Turma) * 50);
int n_turmas = 0;
ler_turmas(nome_arquivo_turmas, &turmas, &n_turmas);

// alocar salas para turmas...

escrever_horarios(nome_arquivo_horarios, turmas, n_turmas);

// liberar memória alocada
free(salas);
free(turmas);

return 0;
```