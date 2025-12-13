#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "cabecalho.h"

int main() {
    setlocale(LC_ALL, "Portuguese");

    AbreVetores();

    Paciente p;
    strcpy(p.nome, "João");

    InserirNovoPaciente(p);

    IndexPaciente i;
    i.posicao = 10;

    int aux;

    printf("1- Efetuar Login\n");
    printf("2- Cadastrar Usuário\n");
    printf("3- Encerrar Programa\n");

    scanf("%d", &aux);

    if(aux==1){
        char userAux[20], senhaAux[20];
        printf("Usuário: ");
        scanf("%s", userAux);

        printf("Senha: ");
        scanf("%s", senhaAux);
    }

    return 0;
}
