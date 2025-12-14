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