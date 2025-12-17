#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "cabecalho.h"

int quantidadePacientes = 0;
Paciente *vetPacientes;
IndexPaciente *vetIndexPaciente;

int BuscarPacientePorCPF(char CPF[])
{
    int inicio = 0;                    // Começa no primeiro elemento
    int fim = quantidadePacientes - 1; // Termina no último elemento válido
    int meio;                          // Variável para guardar a posição central

    while (inicio <= fim)
    {

        
        meio = (inicio + fim) / 2; // Calcula o índice bem no meio da lista

        // strcmp compara duas strings:
        // Retorna 0 se forem iguais
        // Retorna < 0 se a primeira vier antes no alfabeto
        // Retorna > 0 se a primeira vier depois no alfabeto
        int cmp = strcmp(CPF, vetIndexPaciente[meio].chave);
        
        if (cmp == 0)
        {
            printf("CPF no sistema\n", meio);
            return meio; // achou

        }
        else if (cmp < 0)
        {
            fim = meio - 1; // Se é menor, descarta a metade da direita e foca na esquerda
        }
        else
        {
            inicio = meio + 1; // Se é maior, descarta a metade da esquerda e foca na direita
        }
    }

    printf("\nCPF não cadastrado %d\n", meio);
    return -1; // Se saiu do loop, é pq não encontrou nada

    
}

void InserirNovoPaciente()
{
    Paciente paciente;
    FILE *ptarq;
    ptarq = fopen("output/pacientes.bin", "a+b");

    if (ptarq == NULL)
    {
        printf("deu merda1\n");
    }

    printf("----------CADASTRO DE PACIENTES----------\n");
    printf("Nome: ");
    scanf(" %[^\n]", &paciente.nome);
    int limpar;
    while ((limpar = getchar()) != '\n' && limpar != EOF);
    printf("CPF: ");
    scanf("%s", &paciente.CPF);
    while ((limpar = getchar()) != '\n' && limpar != EOF);
    printf("Data de Nascimento: ");
    scanf("%s", &paciente.data_de_nascimento);
    while ((limpar = getchar()) != '\n' && limpar != EOF);
    printf("Telefone: ");
    scanf("%s", &paciente.telefone);
    while ((limpar = getchar()) != '\n' && limpar != EOF);
    
    fwrite(&paciente, sizeof(Paciente), 1, ptarq);


    fclose(ptarq);
    printf("\n Paciente cadastrado com sucesso!\n");

    CarregarIndicePacientes();
}
void AlterarDadosPaciente()
{
    char CPF[12];
    printf("\n----------ALTERAÇÃO DE DADOS PACIENTE----------\n");
    printf("Digite o CPF do paciente que deseja Alterar: ");
    scanf("%s", CPF);

    int p = BuscarPacientePorCPF(CPF);
    if (p == -1) {
        printf("Erro: Paciente nao encontrado!\n");
        return;
    }
    int edicao = -1;

    long posicao = vetIndexPaciente[p].posicao;
    p = posicao / sizeof(Paciente);

    printf("\nPaciente:\n");
    printf("Nome: %s\n",vetPacientes[p].nome);
    printf("CPF: %s\n",vetPacientes[p].CPF);
    printf("Data de Nascimento: %s\n",vetPacientes[p].data_de_nascimento);
    printf("Telefone: %s\n\n",vetPacientes[p].telefone);

    printf("Digite o dado que deseja aterar: \n");
    printf("Para Alterar o Nome digite 1; \n");
    printf("Para Alterar o Telefone digite 2; \n");
    printf("Para Alterar data de nascmiento digite 3. \n");
    scanf("%d", &edicao);

    switch (edicao){
        case 1:
            printf("Digite o novo Nome: ");
            scanf(" %[^\n]", vetPacientes[p].nome);
        break;
        case 2:
            printf("Digite o novo Telefone: ");
            scanf("%s", vetPacientes[p].telefone);
        break;
        case 3:
            printf("Digite a nova data de nascimento: ");
            scanf("%s", vetPacientes[p].data_de_nascimento);
        break;
    }

    FILE *ptarq;
    ptarq = fopen("output/pacientes.bin", "r+b");
    
    fseek(ptarq, posicao , SEEK_SET);
    fwrite(&vetPacientes[p], sizeof(Paciente), 1 , ptarq);
    fclose(ptarq);

    CarregarIndicePacientes();

}

void ExcluirPaciente(){
    char CPF[12];
    printf("\n----------EXCLUSÃO DE PACIENTE----------\n");
    printf("Digite o CPF do paciente que deseja excluir: ");
    scanf("%s", CPF);

    FILE *arqLer;
    arqLer = fopen("output/pacientes.bin", "r+b");
    Paciente *ler = (Paciente *)malloc(quantidadePacientes * sizeof(Paciente));
    fread(ler,sizeof(Paciente),quantidadePacientes,arqLer);
    fclose(arqLer);

    FILE *arqNv;
    arqNv = fopen("output/pacientes.bin", "w+b");
    for(int i=0;i<quantidadePacientes; i++){
        if(strcmp(CPF, ler[i].CPF) != 0){
            fwrite(&ler[i], sizeof(Paciente), 1, arqNv);
        }
    }
    fclose(arqNv);

    CarregarIndicePacientes();
    free(ler);
}

void ListaPacientes()
{
    CarregarIndicePacientes();

    FILE *arq = fopen("output/pacientes.bin", "r+b");
    if (arq == NULL) return; 

    Paciente p; 

    printf("----------------------------------");
    printf("Lista de Pacientes");
    printf("----------------------------------\n");
    
    for (int i = 0; i < quantidadePacientes; i++)
    {
        fseek(arq, vetIndexPaciente[i].posicao, SEEK_SET);
        
        fread(&p, sizeof(Paciente), 1, arq);

        printf("Nome: %s\n", p.nome);
        printf("CPF: %s\n", p.CPF);
        printf("Data de Nascimento: %s\n", p.data_de_nascimento);
        printf("Telefone: %s\n\n", p.telefone);
    }

    printf("----------------------------------");
    printf("Fim");
    printf("----------------------------------\n");

    fclose(arq);
    CarregarIndicePacientes();
}

void CarregarIndicePacientes()
{
    FILE *ptpacientes = fopen("output/pacientes.bin", "rb"); //le apenas
    if (ptpacientes == NULL)
    {
        // aqui so trata o erro e sai, garantindo quantidadepacientes = 0
        quantidadePacientes = 0;
        return; 
    }

    fseek(ptpacientes, 0, SEEK_END);
    long tamanho = ftell(ptpacientes);
    rewind(ptpacientes);

    quantidadePacientes = tamanho / sizeof(Paciente);
    vetPacientes = (Paciente *)malloc(quantidadePacientes * sizeof(Paciente));
    vetIndexPaciente = (IndexPaciente *)malloc(quantidadePacientes * sizeof(IndexPaciente));

    fread(vetPacientes, sizeof(Paciente), quantidadePacientes, ptpacientes);

    for (int i = 0; i < quantidadePacientes; i++)
    {
        strcpy(vetIndexPaciente[i].chave, vetPacientes[i].CPF);
        vetIndexPaciente[i].posicao = i*sizeof(Paciente);
    }

    fclose(ptpacientes);

    quicksort(vetIndexPaciente, 0, quantidadePacientes-1);

    FILE *indexPac = fopen("output/indices_pacientes.bin", "w+b");
    fwrite(vetIndexPaciente, sizeof(IndexPaciente), quantidadePacientes, indexPac);
    fclose(indexPac);

    printf("Sistema: %d pacientes carregados na memoria.\n", quantidadePacientes);
}

void troca(IndexPaciente *v, int i, int j) {
  IndexPaciente aux;
  aux = v[i];
  v[i] = v[j];
  v[j] = aux;
}

void quicksort(IndexPaciente *v, int L, int R){
  int i, j;
  char pivo[20]; 
  i = L;
  j = R;
  strcpy(pivo, v[(i+j)/2].chave); 
  
  do {
    while (strcmp(v[i].chave, pivo) < 0) i++;
    while (strcmp(v[j].chave, pivo) > 0) j--;
    
    if (i <= j){
      troca(v, i, j); 
      i++;
      j--;
     }
   } while (i <= j);
   
   if (L < j) quicksort(v, L, j);
   if (R > i) quicksort(v, i, R);
 }

 void BuscarPacientePorNome(){
    char nomeBusca[50];
    int i;
    int encontrou = 0; 
    Paciente p;
    FILE *arqDados;

    printf("\n--- BUSCA POR NOME (Parcial) ---\n");
    printf("Digite parte do nome: ");
    // limepeza de buffer antes de ler string
    int limpar;
    while ((limpar = getchar()) != '\n' && limpar != EOF);
    fgets(nomeBusca, 50, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0; 
    // se o usuário der Enter sem digitar nada, sai
    if (strlen(nomeBusca) == 0) return;
    arqDados = fopen("output/pacientes.bin", "rb"); 
    if (arqDados == NULL) {
        printf("Erro ao ler banco de dados de pacientes.\n");
        return;
    }
    printf("\nResultados para '%s':\n", nomeBusca);
    printf("--------------------------------------------------\n");

    for (i = 0; i < quantidadePacientes; i++) {
        fseek(arqDados, vetIndexPaciente[i].posicao, SEEK_SET);
        fread(&p, sizeof(Paciente), 1, arqDados);
        if (strstr(p.nome, nomeBusca) != NULL) {
            printf("CPF: %-11s | Nome: %-25s | Telefone: %s\n", p.CPF, p.nome, p.telefone);
            encontrou++;
        }
    }

    printf("--------------------------------------------------\n");

    if (encontrou == 0) {
        printf("Nenhum paciente encontrado com esse nome.\n"); 
    }
    else {
        printf("Total encontrados: %d\n", encontrou);
    }
    fclose(arqDados);
}
