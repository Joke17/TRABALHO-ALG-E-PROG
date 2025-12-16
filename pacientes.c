#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "cabecalho.h"

int quantidadePacientes = 0;
Paciente *vetPacientes;
IndexPaciente *vetIndexPaciente;
/*
void OrdenaCPF(){
    IndexPaciente aux;
    int ordenado = 0;
    while (ordenado != 1){
        if(strcmp(vetIndexPaciente[i].chave, vetIndexPaciente[i + 1].chave) == 1){
            aux = vetIndexPaciente[i];
            vetIndexPaciente[i] = vetIndexPaciente[i + 1];
            vetIndexPaciente[i + 1] = aux;
        }
    }
}
*/

int BuscarPacientePorCPF(char CPF[])
{
    // char CPF[12];
    // if(modo == 0){
    //     printf("DIGITE O CFP PACIENTE DESEJADO: ");
    //     scanf("%s", CPF);  
    // } else {
        //strcpy(CPF,vetIndexPaciente[quantidadePacientes].chave);
    // }

    int achou = 0;

    for(int i = 0; i < quantidadePacientes; i++){
        if(strcmp(CPF,vetIndexPaciente[i].chave) == 0){
            //achou = 1;
            return i;
        }
    }

    

    /*

    int inicio = 0;                    // Começa no primeiro elemento
    int fim = quantidadePacientes - 1; // Termina no último elemento válido
    int meio;                          // Variável para guardar a posição central

    // Enquanto o início não ultrapassar o fim, continuamos procurando
    while (inicio <= fim)
    {

        
        meio = (inicio + fim) / 2; // Calcula o índice bem no meio da lista

        // strcmp compara duas strings:
        // Retorna 0 se forem iguais
        // Retorna < 0 se a primeira vier antes no alfabeto
        // Retorna > 0 se a primeira vier depois no alfabeto
        int cmp = strcmp(CPF, vetIndexPaciente[meio].chave);

        printf("cmp %d\n", cmp);
        printf("m %d\n", meio);
        
        if (cmp == 0)
        {
            printf("CPF no sistema\n", meio);
            return meio; // ACHOU! Retorna a posição onde está.

        }
        else if (cmp < 0)
        {
            fim = meio - 1; // Se é menor, descarta a metade da direita e foca na esquerda.
        }
        else
        {
            inicio = meio + 1; // Se é maior, descarta a metade da esquerda e foca na direita.
        }
    }
    // if(modo == 1){
    //     ReordenaPacientes(meio);
    // }
    printf("\nCPF não cadastrado %d\n", meio);
    return meio; // Se saiu do loop, é porque não encontrou nada.

    */
}

void ReordenaPacientes(int posicao){
    Paciente aux;
    vetPacientes = (Paciente *)realloc(vetPacientes, (quantidadePacientes + 1) * sizeof(Paciente));
    for(posicao;posicao < quantidadePacientes; posicao++){
        aux = vetPacientes[posicao + 1];
        vetPacientes[posicao + 1] = vetPacientes[posicao];
        vetPacientes[posicao] = aux;
        // printf("aq eu\n");
    }
    
    FILE *ptarq;
    ptarq = fopen("output/pacientes.bin", "w+b");
    
    fwrite(vetPacientes, sizeof(Paciente), (quantidadePacientes + 1), ptarq);
    fclose(ptarq);

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
    scanf("%s", &paciente.nome);
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

    // if(quantidadePacientes > 2){
    //     printf("aq ofi");
    //     int p = BuscarPacientePorCPF(paciente.CPF);
    //     ReordenaPacientes(p);
    
    //     fseek(ptarq,(p * sizeof(Paciente)), 0);
    // }
    
    fwrite(&paciente, sizeof(Paciente), 1, ptarq);


    fclose(ptarq);
    printf("\n Paciente cadastrado com sucesso!\n");

    // OrdenaCPF();
    //BuscarPacientePorCPF(1);
    CarregarIndicePacientes();
}
void AlterarDadosPaciente()
{
    char CPF[12];
    printf("\n----------ALTERAÇÃO DE DADOS PACIENTE----------\n");
    printf("Digite o CPF do paciente que deseja Alterar: ");
    scanf("%s", CPF);

    
    
    int p = BuscarPacientePorCPF(CPF);
    int edicao = -1;



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
            scanf("%s", vetPacientes[p].nome);
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
    ptarq = fopen("output/pacientes.bin", "w+b");
    
    //fseek(ptarq, p, SEEK_SET);
    fwrite(vetPacientes, sizeof(Paciente), quantidadePacientes , ptarq);
    fclose(ptarq);

    CarregarIndicePacientes();

}

void ExcluirPaciente(){
    char CPF[12];
    printf("\n----------EXCLUSÃO DE PACIENTE----------\n");
    printf("Digite o CPF do paciente que deseja Alterar: ");
    scanf("%s", CPF);

    int p = BuscarPacientePorCPF(CPF), qt = quantidadePacientes;

    Paciente aux;
    vetPacientes[p] = aux;
    for(p ; p < quantidadePacientes; p++){
        aux = vetPacientes[p + 1];
        vetPacientes[p] = vetPacientes[p + 1];
        vetPacientes[p + 1] = aux;
        // printf("aq eu\n");
    }
    
    FILE *ptarq;
    ptarq = fopen("output/pacientes.bin", "w+b");
    
    fwrite(vetPacientes, sizeof(Paciente), (quantidadePacientes - 1), ptarq);
    fclose(ptarq);

    CarregarIndicePacientes();

}

void ListaPacientes()
{
    printf("----------------------------------");
    printf("Lista de Pacientes");
    printf("----------------------------------\n");
    for (int i = 0; i < quantidadePacientes; i++)
    {
        printf("Nome: %s\n",vetPacientes[i].nome);
        printf("CPF: %s\n",vetPacientes[i].CPF);
        printf("Data de Nascimento: %s\n",vetPacientes[i].data_de_nascimento);
        printf("Telefone: %s\n\n",vetPacientes[i].telefone);
    }
    printf("----------------------------------");
    printf("Fim");
    printf("----------------------------------\n");

    CarregarIndicePacientes();
}

void CarregarIndicePacientes()
{
    // Pacientes
    FILE *ptpacientes = fopen("output/pacientes.bin", "r+b");
    if (ptpacientes == NULL)
    {
        printf("deu merda\n");
    }

    fseek(ptpacientes, 0, SEEK_END);
    long tamanho = (int)ftell(ptpacientes);
    rewind(ptpacientes);

    quantidadePacientes = tamanho / sizeof(Paciente);
    vetPacientes = (Paciente *)malloc(quantidadePacientes * sizeof(Paciente));
    vetIndexPaciente = (IndexPaciente *)malloc(quantidadePacientes * sizeof(IndexPaciente));

    fread(vetPacientes, sizeof(Paciente), quantidadePacientes, ptpacientes);

    for (int i = 0; i < quantidadePacientes; i++)
    {
        strcpy(vetIndexPaciente[i].chave, vetPacientes[i].CPF);
    }

    fclose(ptpacientes);
    printf("Sistema: %d pacientes carregados na memoria.\n", quantidadePacientes);
}

void AdicionarNaMao()
{
    Paciente p;

    // Preenchendo dados falsos pra teste
    strcpy(p.CPF, "123.456.789-00");
    strcpy(p.nome, "Laercio da Silva"); // O brabo
    strcpy(p.data_de_nascimento, "01/01/1980");
    strcpy(p.telefone, "38999999999");

    // "ab" = Append Binary (Adiciona no final ou cria se não existir)
    FILE *arq = fopen("output/pacientes.bin", "ab");

    if (arq != NULL)
    {
        fwrite(&p, sizeof(Paciente), 1, arq);
        fclose(arq);
        printf("Paciente adicionado com sucesso!\n");
    }
    else
    {
        printf("Erro ao abrir arquivo pra escrita.\n");
    }
}