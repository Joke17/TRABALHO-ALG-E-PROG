#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "cabecalho.h"

void InserirNovoPaciente(Paciente paciente){
    FILE *ptarq;
    ptarq = fopen("pacientes.bin", "wb");
    // ptarq = fopen("pacientes.bin", "wb");

    if(ptarq == NULL){
        printf("deu merda\n");
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
    FILE *ptpacientes;
    ptpacientes = fopen("pacientes.bin", "rb");
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
    for(int i = 0; i<quantidade; i++){
        fread(&vetPacientes[i], sizeof(Paciente), 1, ptpacientes);
    }

    fclose(ptpacientes);
}