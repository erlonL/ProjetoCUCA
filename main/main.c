#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct{
    int id_sala;
    char bloco[6];
    char sala[16];
    int capacidade;
    char tipo[16];
    char horario[40];
    int id_turma;
}Sala;

typedef struct{
    int id_turma;
    char disciplina[100];
    int n_turma;
    char horario[20];
    int num_alunos;
    char tipo[20];
    int id_sala;
}Turma;

bool not_in(int element, int* array, int size) {
    for (int i = 0; i < size; i++) {
        if (array[i] == element) {
            return false;  // O elemento está presente no array
        }
    }
    return true;  // O elemento não está presente no array
}

bool idt_not_in(int element, Turma* turmas, int size) {
    for (int i = 0; i < size; i++) {
        if (turmas[i].id_sala == element) {
            return false;  // O elemento está presente no array
        }
    }
    return true;  // O elemento não está presente no array
}

bool ids_not_in(int element, Sala* salas, int size) {
    for (int i = 0; i < size; i++) {
        if (salas[i].id_turma == element) {
            return false;  // O elemento está presente no array
        }
    }
    return true;  // O elemento não está presente no array
}

int calcularDiferenca(int a, int b) {
    return (a > b) ? (a - b) : (b - a);
}

int encontrarMelhorSala(Turma turma, Sala* salas, int num_salas) {
    int melhor_sala = -1;
    int menor_diferenca = -1;

    for (int i = 0; i < num_salas; i++) 
    {
        if (turma.num_alunos <= salas[i].capacidade + 8 && strcmp(turma.tipo, salas[i].tipo) == 0 && salas[i].id_turma == 0) 
        {
            int diferenca = calcularDiferenca(turma.num_alunos, salas[i].capacidade);
            if (melhor_sala == -1 || diferenca < menor_diferenca) 
            {
                melhor_sala = salas[i].id_sala;
                menor_diferenca = diferenca;
            }
        }
    }

    return melhor_sala;
}

int comparar_turmas(const void* a, const void* b) {
    Turma* turma_a = (Turma*) a;
    Turma* turma_b = (Turma*) b;
    int diferenca_tamanho = turma_a->num_alunos - turma_b->num_alunos;
    return diferenca_tamanho;
}

void ordenar_turmas(Turma* turmas, int n_turmas) {
  qsort(turmas, n_turmas, sizeof(Turma), comparar_turmas);
}

void find_class_by_id(int id_turma, Sala* salas, int snr)
{
    for(int i = 0; i < snr; i++)
    {
        if(salas[i].id_turma == id_turma)
        {
            printf("id %d - %s %s %s (%d)\n", salas[i].id_sala, salas[i].tipo, salas[i].bloco, salas[i].sala, salas[i].capacidade);
            return;
        }
    }
    printf("Turma não encontrada.\n");
}

void infoby_id(int id, Turma* turmas, int tnr)
{
    for(int i = 0 ; i < tnr ; i++)
    {
        if(turmas[i].id_turma == id)
        {
            printf("\n----- INFORMAÇÕES PARA A TURMA DE ID %d -----\n", turmas[i].id_turma);
            printf("%s | %s | %d alunos \n", turmas[i].horario, turmas[i].disciplina, turmas[i].num_alunos);
            return;
        }   
    }
    printf("Turma não encontrada.\n");
}

void show_free_classes(Sala* salas, int snr)
{
    int count = 0;
    for(int i = 0; i < snr; i++)
    {
        if(salas[i].id_turma == 0)
        {
            char info[100];
            strcpy(info, "");
            strcat(info, salas[i].tipo);
            strcat(info, " ");
            strcat(info, salas[i].bloco);
            strcat(info, " ");
            strcat(info, salas[i].sala);

            printf("id %d | %-30s | %d | %s\n", salas[i].id_sala, info, salas[i].capacidade, salas[i].horario);
            strcpy(info, "");
            count++;
        }
    }
    printf("Número de salas livres = %d\n", count);
}

int main(){

    int tnr = 100;
    int snr = 23;
    int count = 0;

    FILE *arquivo1;
    FILE *arquivo2;
    FILE *salas_alocadas;

    Sala* salas = malloc(snr * sizeof(Sala));
    Turma* turmas = malloc(tnr * sizeof(Turma));

    int *restantes = malloc(23 * sizeof(int));
    int indx = 0;

    char linha[177];

    bool salas_restantes;

    char nome_arquivo[20];
    printf("Digite o nome do arquivo que deseja abrir: (ex: SQM45.csv)\n");
    printf(">>  ");
    scanf("%s", nome_arquivo);

    arquivo2 = fopen(nome_arquivo, "r");
    if(arquivo2 == NULL){
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    // Ler e descartar cabeçalho
    fgets(linha, sizeof(linha), arquivo2);
    while(count < tnr)
    {
        if(fgets(linha, sizeof(linha), arquivo2) == NULL){
            tnr = count;
            turmas = realloc(turmas, tnr * sizeof(Turma));
            break;
        }
        sscanf(linha, "%d,%[^,],%d,%[^,],%d,%[^\n]",
        &turmas[count].id_turma,
        turmas[count].disciplina,
        &turmas[count].n_turma,
        turmas[count].horario,
        &turmas[count].num_alunos,
        turmas[count].tipo);

        turmas[count].id_sala = 0;

        count++;
    }
    fclose(arquivo2);

    count = 0;


    arquivo1 = fopen("salas.csv", "r");
    if(arquivo1 == NULL){
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    // Ler e descartar cabeçalho
    fgets(linha, sizeof(linha), arquivo1);
    while(count < snr)
    {
        if(fgets(linha, sizeof(linha), arquivo1) == NULL){
            break;
        }
        sscanf(linha, "%[^,],%[^,],%d,%[^\n]",
        salas[count].bloco,
        salas[count].sala,
        &salas[count].capacidade,
        salas[count].tipo);

        salas[count].id_sala = count + 1;
        salas[count].id_turma = 0;
        strcpy(salas[count].horario, turmas[0].horario);

        count++;
    }
    fclose(arquivo1);



    ordenar_turmas(turmas, tnr);

    int melhores_salas[tnr];

    printf("\n*Pré alocação:\n");
    for(int i = 0; i < tnr; i++)
    {
        int melhor_sala = encontrarMelhorSala(turmas[i], salas, snr);
        melhores_salas[i] = melhor_sala;

        if(melhor_sala != -1 && not_in(melhor_sala, melhores_salas, i)){
            // printf("Turma %d (%d - %s) - id %d (%d)\n", turmas[i].id_turma, turmas[i].num_alunos, turmas[i].tipo, melhor_sala, salas[melhor_sala - 1].capacidade);
            salas[melhor_sala - 1].id_turma = turmas[i].id_turma;
            turmas[i].id_sala = melhor_sala;
            printf("ID: %d (%d alunos) - %s %s (%d lugares)\n", turmas[i].id_turma, turmas[i].num_alunos, salas[melhor_sala - 1].bloco, salas[melhor_sala - 1].sala, salas[turmas[i].id_sala - 1].capacidade); 
        }
    }

    if(ids_not_in(0, salas, snr))
    {
        printf("\nTodas as salas utilizadas.\n");
        salas_restantes = false;
    }else
    {
        salas_restantes = true;

        printf("\nSalas não utilizadas:\n");
        for(int i = 0; i < snr; i++)
        {
            if(salas[i].id_turma == 0)
            {
                printf("id %d - %s, %s %s (%d)\n", salas[i].id_sala, salas[i].tipo, salas[i].bloco, salas[i].sala, salas[i].capacidade);
                restantes[indx] = salas[i].id_sala;
                indx++;
            }
        }
        restantes = realloc(restantes, indx * sizeof(int));
    }   
    if(idt_not_in(0, turmas, tnr)){
        printf("\nTodas as turmas alocadas.\n");
    }else
    {
        printf("\nTurmas sem salas:\n");
        for(int i = 0 ; i < tnr; i++)
            {
                if(turmas[i].id_sala == 0)
                {
                    printf("id %d - %d (%s)\n", turmas[i].id_turma, turmas[i].num_alunos, turmas[i].tipo);
                }
            }
    }

    int ch1;
    do
    {
        printf("\n----- MENU -----\n");
        printf("\n1 - Consultar informações // 2 - Modificar alocação // 3 - Salvar Alocação // -1 - Sair\n");
        printf(">>  ");
        scanf("%d", &ch1);

        switch(ch1)
        {
            case(1): // Consultar informações
            {
                int ch = 0;
                printf("\n----- CONSULTA -----");
                do
                {
                    printf("\n1 - Ver turmas alocadas // 2 - Ver informações por id-turma // 3 - Ver salas não utilizadas // -1 - Sair\n");
                    printf(">>  ");
                    scanf("%d", &ch);

                    switch(ch)
                    {
                        case(1): // Ver turmas alocadas
                        {
                            for(int i = 0; i < tnr; i++)
                            {
                                if(turmas[i].id_sala != 0)
                                {
                                    printf("id %d - %s (%s)\n", turmas[i].id_turma, turmas[i].disciplina, turmas[i].tipo);
                                }
                            }
                            break;
                        }
                        case(2): // Ver informações por id-turma
                        {
                            int id;
                            printf("Digite o id da turma:\n");
                            printf(">>  ");
                            scanf("%d", &id);

                            infoby_id(id, turmas, tnr);
                            printf("Turma alocada em: ");
                            find_class_by_id(id, salas, snr);
                            break;
                        }
                        case(3): // Ver salas não utilizadas
                        {
                            show_free_classes(salas, snr);
                            break;
                        }
                    }

                }while(ch != -1);
            break;
            } 
            case(2): // Modificar alocação
            {
                printf("Digite o id da turma que deseja modificar:\n");
                printf(">>  ");
                int id;
                scanf("%d", &id);

                if((idt_not_in(id, turmas, tnr)) == false)
                {
                    printf("Turma não encontrada.\n");
                    break;
                }else
                {
                    infoby_id(id, turmas, tnr);
                    printf("Turma alocada em: ");
                    find_class_by_id(id, salas, snr);
                }
                printf("\nDigite o id da sala que deseja alocar a turma:\n");
                printf(">>  ");
                int id2;
                scanf("%d", &id2);

                for(int i = 0 ; i < snr ; i++)
                {
                    if(salas[i].id_sala == id2)
                    {
                        if(salas[i].id_turma != 0)
                        {
                            printf("Sala já alocada.\n");
                            break;
                        }else
                        {
                            int save_id;

                            salas[i].id_turma = id;
                            for(int j = 0 ; j < tnr ; j++)
                            {
                                if(turmas[j].id_turma == id)
                                {
                                    save_id = turmas[j].id_sala;
                                    turmas[j].id_sala = id2;
                                }
                            }
                            printf("Turma alocada em: ");
                            find_class_by_id(id, salas, snr);
                            for(int k = 0 ; k < snr ; k++)
                            {
                                if(salas[k].id_sala == save_id)
                                {
                                    salas[k].id_turma = 0;
                                }
                            }
                            break;
                        }
                    }
                }
                break;
            }
            case(3): // Salvar turmas
            {
                // -- Salvar turmas -- 
                salas_alocadas = fopen("salas_alocadas.csv", "a");
                if(salas_alocadas == NULL)
                {
                    printf("Erro ao abrir o arquivo salas_alocadas.\n");
                    exit(1);
                }

                printf("\nAlocação mantida, salvando em arquivo...\n");
                // fprintf(salas_alocadas,"id_sala,id_turma,disciplina,n_turma,horario,num_alunos,tipo\n");
                fprintf(salas_alocadas, "\n");
                for(int i = 0; i < tnr; i++)
                {
                    if(turmas[i].id_sala != 0)
                    {       
                        if(i != tnr-1)
                        {
                            fprintf(salas_alocadas, "%d,%d,%s,%d,%s,%d,%s\n", 
                            turmas[i].id_sala, 
                            turmas[i].id_turma, 
                            turmas[i].disciplina, 
                            turmas[i].n_turma, 
                            turmas[i].horario, 
                            turmas[i].num_alunos, 
                            turmas[i].tipo);
                        }else
                        {
                            fprintf(salas_alocadas, "%d,%d,%s,%d,%s,%d,%s", 
                            turmas[i].id_sala, 
                            turmas[i].id_turma, 
                            turmas[i].disciplina, 
                            turmas[i].n_turma, 
                            turmas[i].horario, 
                            turmas[i].num_alunos, 
                            turmas[i].tipo);
                        }
                    }
                }

                // -- Salvar salas livres --
                FILE* salas_livres = fopen("salas_livres.csv", "a");
                if(salas_livres == NULL)
                {
                    printf("Erro ao abrir o arquivo salas_livres.\n");
                    exit(1);
                }
                printf("Salvando salas com horário (%s) disponível...\n", turmas[0].horario);
            
                fprintf(salas_livres, "\n");
                for(int i = 0 ; i < indx; i++)
                {
                    for(int j = 0 ; j < snr ; j++)
                    {
                        if(salas[j].id_sala == restantes[i])
                        {
                            if(i < indx-1)
                            {
                                fprintf(salas_livres, "%d,%s,%s,%d,%s,%s\n", 
                                salas[j].id_sala,
                                salas[j].bloco,
                                salas[j].sala,
                                salas[j].capacidade,
                                salas[j].tipo,
                                turmas[0].horario);
                            }else
                            {
                                fprintf(salas_livres, "%d,%s,%s,%d,%s,%s", 
                                salas[j].id_sala,
                                salas[j].bloco,
                                salas[j].sala,
                                salas[j].capacidade,
                                salas[j].tipo,
                                turmas[0].horario);
                            }
                        }
                    }
                }
                
                free(salas);
                free(turmas);
                free(restantes);
                return 0;
            }
        }
    }while(ch1 != -1);



    free(salas);
    free(turmas);
    free(restantes);

}
