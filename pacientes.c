#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "cabecalho.h"

int quantidadePacientes = 0;
Paciente *vetPacientes;
IndexPaciente *vetIndexPaciente;
  

int BuscarPacientePorCPF(){
    char CPF[12];
    printf("DIGITE O CFP PACIENTE DESEJADO: ");
    scanf("%s", CPF);

    int inicio = 0;             // Começa no primeiro elemento
    int fim = quantidadePacientes - 1;   // Termina no último elemento válido
    int meio;                   // Variável para guardar a posição central

    // Enquanto o início não ultrapassar o fim, continuamos procurando
    while (inicio <= fim) {
        meio = (inicio + fim) / 2; // Calcula o índice bem no meio da lista
        
        // strcmp compara duas strings:
        // Retorna 0 se forem iguais
        // Retorna < 0 se a primeira vier antes no alfabeto
        // Retorna > 0 se a primeira vier depois no alfabeto
        int cmp = strcmp(CPF, vetIndexPaciente[meio].chave);

        if (cmp == 0) {
            return meio; // ACHOU! Retorna a posição onde está.
        } else if (cmp < 0) {
            fim = meio - 1; // Se é menor, descarta a metade da direita e foca na esquerda.
        } else {
            inicio = meio + 1; // Se é maior, descarta a metade da esquerda e foca na direita.
        }
    }
    return -1; // Se saiu do loop, é porque não encontrou nada.
}




void InserirNovoPaciente(){
    Paciente paciente;
    FILE *ptarq;
    ptarq = fopen("output/pacientes.bin", "a+");

    if(ptarq == NULL){
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

    fwrite(&paciente, sizeof(Paciente), 1, ptarq);
    fclose(ptarq);

    CarregarIndicePacientes();
}
void AlterarDadosPaciente(){
    printf("\n----------ALTERAÇÃO DE DADOS PACIENTE----------\n");
    int posicao = BuscarPacientePorCPF();
    printf("%d", posicao);

}
void CarregarIndicePacientes(){
    // Pacientes
    FILE *ptpacientes = fopen("output/pacientes.bin", "rb");
    if(ptpacientes == NULL){
        printf("deu merda\n");
    }

    fseek(ptpacientes, 0, SEEK_END);
    long tamanho = (int)ftell(ptpacientes);
    rewind(ptpacientes);
    
    quantidadePacientes = tamanho / sizeof(Paciente);
    vetPacientes = (Paciente *) malloc(quantidadePacientes * sizeof(Paciente));
    vetIndexPaciente = (IndexPaciente *) malloc(quantidadePacientes * sizeof(IndexPaciente));
    
    fread(vetPacientes, sizeof(Paciente), quantidadePacientes, ptpacientes);

    for(int i = 0; i < quantidadePacientes; i++){
        strcpy(vetIndexPaciente[i].chave, vetPacientes[i].CPF);
    }

    fclose(ptpacientes);
    printf("Sistema: %d pacientes carregados na memoria.\n", quantidadePacientes);

}

void AdicionarNaMao() {
    Paciente p;
    
    // Preenchendo dados falsos pra teste
    strcpy(p.CPF, "123.456.789-00");
    strcpy(p.nome, "Laercio da Silva"); // O brabo
    strcpy(p.data_de_nascimento, "01/01/1980");
    strcpy(p.telefone, "38999999999");

    // "ab" = Append Binary (Adiciona no final ou cria se não existir)
    FILE *arq = fopen("output/pacientes.bin", "ab"); 
    
    if (arq != NULL) {
        fwrite(&p, sizeof(Paciente), 1, arq);
        fclose(arq);
        printf("Paciente adicionado com sucesso!\n");
    } else {
        printf("Erro ao abrir arquivo pra escrita.\n");
    }
}