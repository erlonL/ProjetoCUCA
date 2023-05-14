#pe
O projeto CUCA conta com:
- <b>4 funções diferentes</b> referentes a alocação de turmas e salas.
- <b>2 estruturas diferentes</b> de turma e sala e 2 enum's para o TipoSala e TipoBloco.

Para cada dia da semana diferente, uma nova iteração do algoritmo teria que ser rodada, pois as solicitações seriam diferentes.

## Definição das Estruturas
``enum`` TipoSala:
```c 
typedef enum{
	AULA,
	LABORATORIO
} TipoSala;
```
- 0: (não é apenas SALA pois daria conflito com outras estruturas) Sala de aula comum, com carteiras, projetor e quadro branco;
- 1: Laboratório com computadores.

`enum` TipoBloco:
```c
typedef enum{
	CI,
	LIEPE,
	CTDR
} TipoBloco;
```
- 0: CI - Centro de Informática;
- 1: LIEPE - Laboratório Interdisciplinar de Ensino, Pesquisa e Extensão;
- 2: CTDR - Centro de Tecnologia e Desenvolvimento Regional.

`struct` Turma:
```c
typedef struct {
	int id_turma;
	int numero_alunos;
	char horario[10];
	TipoSala tipo_sala;
} Turma;
```
- `int id_turma` - id da turma (servirá para identificar a turma alocada);
- `int numero_alunos` - número de alunos da turma (importante para alocação em salas que tenham capacidade);
- `char horario[10]` - "8h-10h" período de horário formatado em string; 
- `TipoSala tipo_sala`  - Tipo da sala solicitada pela turma (0: sala, 1: lab).

`struct` Sala:
```c
typedef struct {
	TipoBloco bloco;
	TipoSala tipo;
	int sala;
	int capacidade;
	char horario[10];
} Sala;
```
- `TipoBloco bloco` - (CI, LIEPE, CTDR) localização da Sala
- `TipoSala tipo` - (AULA, LABORATORIO) tipo da sala
- `int sala` - número da sala
- `int capacidade` - capacidade da sala
- `char horario[10]` - horários disponíveis da sala

## Definição das Funções

### Filtrar Salas
```c
Sala* filtrar_salas(Turma turma, Sala* salas, int n_salas, int* n_salas_filtradas) 
{
    Sala* salas_filtradas = malloc(n_salas * sizeof(Sala));
    *n_salas_filtradas = 0;

    for (int i = 0; i < n_salas; i++) 
    {
        if (salas[i].tipo == turma.tipo_sala && salas[i].capacidade >= turma.numero_alunos) 
        {
            salas_filtradas[*n_salas_filtradas] = salas[i];
            (*n_salas_filtradas)++;
        }
    }
    return salas_filtradas;
```
- Filtra as salas disponíveis de acordo com as solicitações das turmas.