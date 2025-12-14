#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "cabecalho.h"

void InserirNovoPaciente(Paciente paciente){
    FILE *ptarq;
    ptarq = fopen("output/pacientes.bin", "wb");
    // ptarq = fopen("pacientes.bin", "wb");

    if(ptarq == NULL){
        printf("deu merda1\n");
    }
    fwrite(&paciente, sizeof(Paciente), 1, ptarq);
    fclose(ptarq);


    printf("du bao\n");
}
void AlterarDadosPaciente(){
    printf("\ndeu bao\n");
}
void AbreVetores(){
    //char cwd[1024];
    //_getcwd(cwd, sizeof(cwd));
    // printf("Diretório de trabalho atual: %s\n", cwd);
    
    // Pacientes
    FILE *ptpacientes = fopen("output/pacientes.bin", "rb");
    //FILE *ptpacientes;
    //ptpacientes = fopen("pacientes.bin", "rb");
    if(ptpacientes == NULL){
        printf("deu merda\n");
    }

    fseek(ptpacientes, 0, SEEK_END);
    long tamanho = (int)ftell(ptpacientes);
    rewind(ptpacientes);
    
    int quantidade = tamanho / sizeof(Paciente);
    //printf("%d\n", quantidade);
    Paciente *vetPacientes = (Paciente *) malloc(quantidade * sizeof(Paciente));
    char *vetCPF = (char *) malloc(quantidade * sizeof(char[12]));
    
    //printf("ate aq veio");

    fread(vetPacientes, sizeof(Paciente), quantidade, ptpacientes);

    for(int i=0; i<quantidade; i++){
        printf("%s\n",vetPacientes[i].nome);
    }

    fclose(ptpacientes);
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