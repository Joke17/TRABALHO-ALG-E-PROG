#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "cabecalho.h"

int main() {
    setlocale(LC_ALL, "Portuguese");
    AlterarDadosPaciente();

    IndexPaciente i;
    i.posicao = 10;

    printf("baguio doido\n");
    return 0;
}
