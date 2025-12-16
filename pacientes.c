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
    printf("CPF: ");
    scanf("%s", &paciente.CPF);
    printf("Data de Nascimento: ");
    scanf("%s", &paciente.data_de_nascimento);
    printf("Telefone: ");
    scanf("%s", &paciente.telefone);

    if(quantidadePacientes > 2){
        printf("aq ofi");
        int p = BuscarPacientePorCPF(paciente.CPF);
        ReordenaPacientes(p);
    
        fseek(ptarq,(p * sizeof(Paciente)), 0);
    }

    
    fwrite(&paciente, sizeof(Paciente), 1, ptarq);


    fclose(ptarq);

    // OrdenaCPF();
    //BuscarPacientePorCPF(1);
    CarregarIndicePacientes();
}
void AlterarDadosPaciente()
{
    printf("\n----------ALTERAÇÃO DE DADOS PACIENTE----------\n");
    int posicao = BuscarPacientePorCPF(0);
    printf("%d", posicao);
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
        printf("Telefone: %s\n",vetPacientes[i].telefone);
    }
    printf("----------------------------------");
    printf("Fim");
    printf("----------------------------------\n");
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