# ProjetoCUCA

## Integrantes

- Erlon Lacerda Avelino (20220071286)
- Maria Eduarda Bandeira Hora de Vasconcelos (20220007230)
- Thiago Rodrigues Cruz Justino (20220007276)
- Gisele de Freitas Menezes (20220055765)
- Daniele Vitoria Morais Silva (20220007392)

## O que é o Projeto CUCA?

Classroom Utilization and Capacity Allocation tem como base o sistema SACI da UFPB, é baseado em um **algoritmo de otimização** feito para **alocação de salas** e aulas para turmas, a fim de diminuir intercorrências e comportar a demanda do Centro.

### Qual a vantagem da alocação automática de salas?

Seus resultados são feitos por algoritmo, ou seja, terão maior qualidade, maior performance e não serão baseados na experiência do decisor. 

### Como funciona o Sistema CUCA?

- Recebe as informações de cada turma, como o número de alunos, o horário da aula e o tipo de sala necessária (por exemplo, sala de aula, laboratório, auditório, etc).
- Lê as informações das salas disponíveis, como o bloco, número da sala, capacidade e tipo.
- Filtra as salas que atendem aos requisitos da turma em relação ao tipo de sala, horário e capacidade necessária.
- Ordena as salas disponíveis de acordo com a proximidade da turma e a capacidade da sala.
- Atribui a sala mais adequada para a turma, levando em consideração a disponibilidade da sala naquele horário.
- Registra a alocação da sala na tabela de horários da turma e atualiza a disponibilidade da sala.

### Funções necessárias
- Ler salas
- Filtrar salas
- Comparar salas
- Atribuir sala
- Registrar horario

[![Run on Repl.it](https://replit.com/badge/github/erlonL/ProjetoCUCA)](https://replit.com/new/github/erlonL/ProjetoCUCA)
