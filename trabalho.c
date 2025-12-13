#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "cabecalho.h"

int main() {
    setlocale(LC_ALL, "Portuguese");

    abrevetores();

    Paciente p;
    strcpy(p.nome, "João");
    strcpy(p.CPF, "15");

    InserirNovoPaciente(p);

    IndexPaciente i;
    i.posicao = 10;

    printf("baguio doido  %d \n", i.posicao);
    return 0;
}
