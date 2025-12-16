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
    printf("------------------------\nINICIO\n------------------------\n\n");

    //carregando indices de pacientes e medicos para testes
    CarregarIndicePacientes(); 
    CarregarIndicesMedicos();
    //DebugListarIndices();

    MenuLogin();

    printf("---------------\nFIM.\n------------------------");
    return 0;
}