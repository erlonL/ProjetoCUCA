```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definir as estruturas de dados das turmas e salas
typedef struct {
    int numero_alunos;
    char horario[10];
    int tipo_sala;
} Turma;

typedef struct {
    int bloco;
    int sala;
    int capacidade;
    int tipo;
    char horario[10];
} Sala;

// Filtrar as salas que atendem aos requisitos da turma
Sala* filtrar_salas(Turma turma, Sala* salas, int n_salas, int* n_salas_filtradas) {
    Sala* salas_filtradas = malloc(n_salas * sizeof(Sala));
    *n_salas_filtradas = 0;
    for (int i = 0; i < n_salas; i++) {
        if (salas[i].tipo == turma.tipo_sala && salas[i].capacidade >= turma.numero_alunos) {
            salas_filtradas[*n_salas_filtradas] = salas[i];
            (*n_salas_filtradas)++;
        }
    }
    return salas_filtradas;
}

// Ordenar as salas disponíveis
int comparar_salas(const void* a, const void* b) {
    Sala* sala_a = (Sala*) a;
    Sala* sala_b = (Sala*) b;
    int diferenca_bloco = abs(sala_a->bloco - sala_b->bloco) * 100;
    int diferenca_capacidade = sala_b->capacidade - sala_a->capacidade;
    return diferenca_bloco + diferenca_capacidade;
}

void ordenar_salas(Turma turma, Sala* salas, int n_salas) {
    qsort(salas, n_salas, sizeof(Sala), comparar_salas);
}

// Atribuir a sala mais adequada para a turma
Sala atribuir_sala(Turma turma, Sala* salas, int n_salas) {
    for (int i = 0; i < n_salas; i++) {
        if (strcmp(salas[i].horario, turma.horario) == 0) {
            return salas[i];
        }
    }
    Sala sala_vazia = {0, 0, 0, 0, ""};
    return sala_vazia;
}

// Registrar a alocação da sala na tabela de horários da turma
void registrar_horario(Turma turma, Sala sala) {
    // implementar
}

int main() {
    // Ler as informações das turmas
    Turma turmas[] = {
        {28, "8h-10h", 0},
        {35, "10h-12h", 1},
        {16, "14h-16h", 1},
        {75, "16h-18h", 0},
        {23, "18h-20h", 1}
    };
    int n_turmas = sizeof(turmas) / sizeof(Turma);

    // Ler as informações das salas disponíveis
    Sala salas[] = {
        {3, 105, 28, 0, "8h-10h"},
        {0, 108, 35, 1, "10h-12h"},
        {0, 107, 16, 1, "14h-16h"},
        {0, 104, 75, 0, "16h-18h"},
        {1, 103, 23, 1, "18h-20h"}
};
int n_salas = sizeof(salas) / sizeof(Sala);

// Alocar as salas para as turmas
for (int i = 0; i < n_turmas; i++) {
    Turma turma = turmas[i];
    Sala* salas_filtradas;
    int n_salas_filtradas;
    salas_filtradas = filtrar_salas(turma, salas, n_salas, &n_salas_filtradas);
    ordenar_salas(turma, salas_filtradas, n_salas_filtradas);
    Sala sala_alocada = atribuir_sala(turma, salas_filtradas, n_salas_filtradas);
    if (sala_alocada.capacidade > 0) {
        registrar_horario(turma, sala_alocada);
    } else {
        printf("Nenhuma sala disponível para a turma %d.\n", i+1);
    }
    free(salas_filtradas);
}

return 0;
}
```