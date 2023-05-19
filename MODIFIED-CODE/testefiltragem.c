#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
} Sala;

typedef struct {
    int id_turma;
    int numero_alunos;
    char horario[10];
    TipoSala tipo_sala;
} Turma;

// Filtra salas
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

Sala atribuir_sala(Turma turma, Sala* salas, int n_salas) 
{
    for (int i = 0; i < n_salas; i++) 
    {
        if ((strcmp(salas[i].horario, turma.horario) == 0) && (turma.numero_alunos <= salas[i].capacidade)) 
        {
			return salas[i];  // Sala alocada com sucesso
        }
    }
    Sala sala_vazia = {0, 0, 0, 0, ""};
    return sala_vazia;  // Sala não encontrada
}

int main() {

    // Ler as informações das turmas
    Turma turmas[] = 
    {
        {01, 65, "08h-10h", AULA},
        {02, 65, "10h-12h", LABORATORIO},
        {03, 65, "14h-16h", AULA},

        {05, 45, "14h-16h", LABORATORIO},
        {06, 45, "14h-16h", LABORATORIO},

    };
    int n_turmas = sizeof(turmas) / sizeof(Turma);

    // Ler as informações das salas disponíveis
    Sala salas[] = 
    {
        {CI, LABORATORIO, 101, 37, "08h-10h"},
        {CI, LABORATORIO, 101, 37, "10h-12h"},
        {CI, LABORATORIO, 101, 37, "14h-16h"},
        {CI, LABORATORIO, 101, 37, "16h-18h"},

        {CI, AULA, 102, 27, "08h-10h"},
        {CI, AULA, 102, 57, "10h-12h"},
        {CI, AULA, 102, 57, "14h-16h"},
        {CI, AULA, 102, 57, "16h-18h"},

        {CTDR, AULA, 103, 90, "08h-10h"},
        {CTDR, AULA, 103, 90, "10H-12h"},
        {CTDR, AULA, 103, 90, "14h-16h"},
        {CTDR, AULA, 103, 90, "16h-18h"},

        {LIEPE, AULA, 104, 65, "08h-10h"},
        {LIEPE, AULA, 104, 65, "10h-12h"},
        {LIEPE, AULA, 104, 65, "14h-16h"},
        {LIEPE, AULA, 104, 65, "16h-18h"},
    };
    int n_salas = sizeof(salas) / sizeof(Sala);

// Filtrar as salas para as turmas

for (int i = 0; i < n_turmas; i++) 
{
    Turma turma = turmas[i];
    Sala* salas_filtradas;
    int n_salas_filtradas;

    salas_filtradas = filtrar_salas(turma, salas, n_salas, &n_salas_filtradas);
    printf("\n%d, %d, %d, %d, %s", salas_filtradas[i].bloco, salas_filtradas[i].tipo, salas_filtradas[i].sala, salas_filtradas[i].capacidade, salas_filtradas[i].horario);
    free(salas_filtradas);
}

}