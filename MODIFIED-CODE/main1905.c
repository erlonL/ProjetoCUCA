#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum{
    
} TipoSala;

// Estruturas de dados das turmas e salas.
typedef enum{
    AULA,
    LABORATORIO
} TipoSala;

typedef enum{
    CI,
    LIEPE,
    CTDR
} TipoBloco;

typedef struct {
    TipoBloco bloco;
    TipoSala tipo;
    int sala;
    int capacidade;
    char horario[10];
    int id_turma;
} Sala;

typedef struct {
    int id_turma;
    int numero_alunos;
    char horario[10];
    TipoSala tipo_sala;
} Turma;

// Filtrar salas 
Sala* filtrar_salas(Turma turma, Sala* salas, int n_salas, int* n_salas_filtradas) 
{
    Sala* salas_filtradas = malloc(n_salas * sizeof(Sala));
    *n_salas_filtradas = 0;

    for (int i = 0; i < n_salas; i++) 
    {
        if (salas[i].tipo == turma.tipo_sala) 
        {
            salas_filtradas[*n_salas_filtradas] = salas[i];
            (*n_salas_filtradas)++;
        }
    }
    return salas_filtradas;
}


int comparar_salas(const void* a, const void* b) {
    Sala* sala_a = (Sala*) a;
    Sala* sala_b = (Sala*) b;
    int diferenca_capacidade = sala_b->capacidade - sala_a->capacidade;
    return diferenca_capacidade;
}

void ordenar_salas(Turma turma, Sala* salas, int n_salas) {
	qsort(salas, n_salas, sizeof(Sala), comparar_salas);
}

void remover_sala(Sala* salas, int* n_salas, int index) {
    if (index >= 0 && index < *n_salas) {
        // Movendo as salas à direita do índice para a esquerda
        for (int i = index; i < (*n_salas - 1); i++) {
            salas[i] = salas[i + 1];
        }
        (*n_salas)--;
    }
}

Sala atribuir_sala(Turma turma, Sala* salas, int n_salas) 
{
    for (int i = 0; i < n_salas; i++) 
    {
        if(salas[i].id_turma == 0)
        {
            if ((strcmp(salas[i].horario, turma.horario) == 0) && (turma.numero_alunos <= salas[i].capacidade)) 
            {
            salas[i].id_turma = turma.id_turma;
			return salas[i];  // Sala alocada com sucesso
            }
        }
    }
    Sala sala_vazia = {0, 0, 0, 0, ""};
    return sala_vazia;  // Sala não encontrada
}

int main() {
    // Ler as informações das salas disponíveis
    Sala salas[] = 
    {
        {CI, LABORATORIO, 101, 37, "08h-10h", 0},
        {CI, LABORATORIO, 101, 37, "10h-12h", 0},
        {CI, LABORATORIO, 101, 37, "14h-16h", 0},
        {CI, LABORATORIO, 101, 37, "16h-18h", 0},

        {CI, AULA, 102, 27, "08h-10h", 0},
        {CI, AULA, 102, 57, "10h-12h", 0},
        {CI, AULA, 102, 57, "14h-16h", 0},
        {CI, AULA, 102, 57, "16h-18h", 0},

        {CTDR, AULA, 103, 90, "08h-10h", 0},
        {CTDR, AULA, 103, 90, "10H-12h", 0},
        {CTDR, AULA, 103, 90, "14h-16h", 0},
        {CTDR, AULA, 103, 90, "16h-18h", 0},

        {LIEPE, AULA, 104, 90, "08h-10h", 0},
        {LIEPE, AULA, 104, 65, "10h-12h", 0},
        {LIEPE, AULA, 104, 65, "14h-16h", 0},
        {LIEPE, AULA, 104, 65, "16h-18h", 0},
    };
    int n_salas = sizeof(salas) / sizeof(Sala);

    // Definir uma turma de exemplo
    Turma turmas[] = 
    {
        {01, 90, "08h-10h", AULA},
        {02, 90, "10h-12h", LABORATORIO},
        {03, 90, "08h-10h", AULA},
        {04, 90, "14h-16h", LABORATORIO},
        {05, 90, "14h-16h", LABORATORIO},
    };
    int n_turmas = sizeof(turmas) / sizeof(Turma);

for (int i = 0; i < n_turmas; i++)
{
    // Filtrar salas com base no tipo de sala da turma
    Sala* salas_filtradas;
    int n_salas_filtradas;
    Turma turma = turmas[i];
    salas_filtradas = filtrar_salas(turma, salas, n_salas, &n_salas_filtradas);

    // Ordenar salas filtradas por capacidade
    ordenar_salas(turma, salas_filtradas, n_salas_filtradas);

    // Atribuir sala à turma
    Sala sala_alocada = atribuir_sala(turma, salas_filtradas, n_salas_filtradas);

    // Exibir resultado
    if (sala_alocada.sala != 0) {
        printf("\nTurma %d: \nSala alocada: Bloco %d, Sala %d\n", turma.id_turma, sala_alocada.bloco, sala_alocada.sala);
    } else {
        printf("\nNenhuma sala disponível para a turma %d.\n", turma.id_turma);
    }

    // Liberar memória alocada para as salas filtradas
    free(salas_filtradas);
}


}
