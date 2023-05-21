#include <stdio.h>
#include <string.h>

//Struct que armazena os dias das semanas e se já tiver sendo utilizado o turno recebe 1,se não permanece o valor que estava
typedef struct{
}dia;

//Struct que armazena as informações das salas
typedef struct{
char Bloco_sala[6],Tipo_sala[14],sala[15],vaga[3][6];
int capacidade;
}sala;

typedef struct{
int turma,num_alunos;
char codigo[20],disciplina[50],horario[10],tipo[14],bloco_turma[6],turmas_alocadas[50];
}turma;

int main(void) {

//Declarando as variáveis  
  FILE *resposta,*arquivo1,*arquivo2;
  dia dias[80];
  sala salas[24];
  turma turmas[200];
  int count=0,i,j,k,l,x;
  char *p,*p2, linha[23][256],linha2[120][256];

//Abrindo o arquivo csv com as turmas e lendo as informações  
  arquivo1 = fopen("Turmas_final.csv","r");

if (arquivo1) {
  count = 23;
  while (count < 147) {
  p2 = fgets(linha2[count], sizeof(linha2), arquivo1);
   fscanf(arquivo1,"%[^,],%d,%[^,],%[^,],%d,%[^,],%[^,],",turmas[count].codigo,&turmas[count].turma,turmas[count].disciplina,turmas[count].horario,&turmas[count].num_alunos,turmas[count].tipo,turmas[count].bloco_turma);
    
/* Para printar todas as informações de turmas e ver se tá funcionando 
printf("%s,%d,%s,%s,%d,%s,%s",turmas[count].codigo,turmas[count].turma,turmas[count].disciplina,turmas[count].horario,turmas[count].num_alunos,turmas[count].tipo,turmas[count].bloco_turma); 
printf("\n");
*/
    count++;
    p2++;
  }

} else {
  printf("Rolou um erro");
}
fclose(arquivo1);
count=0;
arquivo2 = fopen("Salas.csv","r"); 
while(count<23){
p = fgets(linha[count], sizeof(linha2), arquivo2);
  fscanf(arquivo2,"%[^,],%[^,],%[^,],%d",salas[count].Bloco_sala,salas[count].sala,salas[count].Tipo_sala,&salas[count].capacidade);
  
/*Para printar as salas e ver se tá funcionado:
printf("%s,%s,%s,%d",salas[count].Bloco_sala,salas[count].sala,salas[count].Tipo_sala,salas[count].capacidade);printf("\n");*/
p++;
count++;
}
fclose(arquivo1);
//Criando um arquivo as possíveis salas alocadas:
resposta = fopen("Resultado.txt","w");
for(i=23;i<147;i++){
  for(j=0;j<23;j++){
  if(turmas[i].num_alunos==salas[j].capacidade){
  for(k=0;k<3;k++){
  if(strcmp(salas[j].vaga[k],turmas[i].horario)==0){
    continue;
  }else{
  strcpy(turmas[l].turmas_alocadas,turmas[i].disciplina);
  strcpy(salas[j].vaga[k],turmas[i].horario);
  }
  }  
 fprintf(resposta,"%s(turma %d): %s %s",turmas[i].disciplina,turmas[i].turma,salas[j].Bloco_sala,salas[j].sala);
  fprintf(resposta,"\n");
  break;
  }
  }
}
}
