#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "cabecalho.h"
#include <unistd.h>


int main() {
    setlocale(LC_ALL, "PORTUGUESE");
    CargaInicial();
    //LimparTela();

    /*  Comandos para rodar:
    gcc *.c -o output/trabalho.exe
    .\output\trabalho.exe
    */

    printf("------------------------\nINICIO\n------------------------\n\n");

    //carregando indices de pacientes e medicos para testes
    //mostra quantidade ja cadastrada
    printf("Carregando indices de médicos e pacientes...\n");
    CarregarIndicePacientes(); 
    CarregarIndicesMedicos();
    //DebugListarIndices();

    MenuLogin();

    printf("---------------\nFIM.\n------------------------");
    return 0;
}