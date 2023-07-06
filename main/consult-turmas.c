#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct{
    char bloco[6];
    char sala[16];
    char tipo[16];
    int capacidade;
    int id_sala;
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

void show_classes(Sala* salas, int snr)
{
    for(int i = 0; i < snr; i++)
    {
        if(salas[i].id_turma != 0)
        {
            printf("id %d - %s %s, %s (%d)\n", salas[i].id_sala, salas[i].bloco, salas[i].sala, salas[i].tipo, salas[i].capacidade);
        }
    }
}

int main(){

    int tnr = 250;
    int snr = 23;
    int count = 0;

    FILE *arquivo1;
    FILE *arquivo2;

    Sala* salas = malloc(snr * sizeof(Sala));
    Turma* turmas = malloc(tnr * sizeof(Turma));

    char linha[177];


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

        count++;
    }
    fclose(arquivo1);

    count = 0;

    arquivo2 = fopen("salas_alocadas.csv", "r");
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
        sscanf(linha, "%d,%d,%[^,],%d,%[^,],%d,%[^\n]",
        &turmas[count].id_sala,
        &turmas[count].id_turma,
        turmas[count].disciplina,
        &turmas[count].n_turma,
        turmas[count].horario,
        &turmas[count].num_alunos,
        turmas[count].tipo);

        for(int i = 0; i < snr; i++)
        {
            if(salas[i].id_sala == turmas[count].id_sala)
            {
                salas[i].id_turma = turmas[count].id_turma;
            }
        }

        count++;
    }
    fclose(arquivo2);

    char p;
    do{

        printf("\nConsultar informações para Turmas ou Salas? (t/S) ");
        printf(">>  ");
        scanf(" %c", &p);
        p = tolower(p);

        switch(p)
        {
            case('t'):
            {
            int ch = 0;
            printf("\n----- CONSULTAR TURMAS -----");
            do{
            printf("\n1 - Ver turmas alocadas // 2 - Ver informações por id // -1 - Sair\n");
            printf(">>  ");
            scanf("%d", &ch);

            switch(ch)
            {
                case(1):
                {
                    for(int i = 0; i < tnr; i++)
                    {
                        if(turmas[i].id_sala != 0)
                        {
                            printf("id %d - %d (%s - %d)\n", turmas[i].id_turma, turmas[i].num_alunos, turmas[i].tipo, turmas[i].id_sala);
                        }
                    }
                    printf("\nNúmero de turmas = %d\n", tnr);
                    break;
                }
                case(2):
                {
                    int id;
                    printf("Digite o id da turma:\n");
                    printf(">>  ");
                    scanf("%d", &id);
                    for(int i = 0; i < tnr; i++)
                    {
                        if(turmas[i].id_turma == id)
                        {
                            printf("\n----- INFORMAÇÕES PARA A TURMA DE ID %d -----\n", turmas[i].id_turma);
                            printf("%s | %d alunos | %s %d\n", turmas[i].disciplina, turmas[i].num_alunos, turmas[i].tipo, turmas[i].id_sala);
                        }
                    }
                    break;
                }
            }

            }while(ch != -1);
            break;
        }
            case('s'):
            {
            int ch = 0;
            printf("\n----- CONSULTAR SALAS -----");
            do{
            printf("\n1 - Ver salas // 2 - Ver informações por id da sala // -1 - Sair\n");
            printf(">>  ");
            scanf("%d", &ch);

            switch(ch)
            {
                case(1):
                {
                    show_classes(salas, snr);
                    
                    // Não funciona por enquanto :)
                    /*
                    printf("\nHorários: ");

                    char horarios[20][30];
                    strcpy(horarios[0], turmas[0].horario);
                    printf("%s", horarios[0]);

                    int counter = 0;
                    
                    for(int i = 0 ; i < tnr; i++)
                    {
                        for(int j = 0 ; j < counter; j++)
                        {
                            if(strcmp(turmas[i].horario, horarios[j]) != 0)
                            {
                                counter++;
                                strcpy(horarios[counter], turmas[i].horario);
                                printf(", %s", horarios[counter]);
                            }
                        }
                    }
                    */
                    break;
                }
                case(2):
                {
                    int id;
                    printf("Digite o id da sala:\n");
                    printf(">>  ");
                    scanf("%d", &id);
                    for(int i = 0; i < snr; i++)
                    {
                        if(salas[i].id_sala == id)
                        {
                            printf("\n----- TURMAS ALOCADAS PARA O ID %d (%s %s %s) -----\n", salas[i].id_sala, salas[i].tipo, salas[i].bloco, salas[i].sala);
                            for(int j = 0; j < tnr; j++)
                            {
                                if(turmas[j].id_sala == id)
                                {
                                    printf("id %d | %s | %2d alunos | %s\n", turmas[j].id_turma, turmas[j].disciplina, turmas[j].num_alunos, turmas[j].horario);
                                }
                            }
                        }
                    }
                    break;
                }
            }

            }while(ch != -1);
            }
        };
        }while(p == 't' || p == 's');





    free(salas);
    free(turmas);

}