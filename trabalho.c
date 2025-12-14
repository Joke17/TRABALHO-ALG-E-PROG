#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "cabecalho.h"
#include "consultas.h"

int main() {
    setlocale(LC_ALL, "PORTUGUESE");
    printf("---------------\nINICIO\n------------------------\n\n");
     


    AbreVetores();

    Paciente p;
    strcpy(p.nome, "João");

    InserirNovoPaciente(p);
    ListarConsultasPorMedico();

    int aux;

    printf("1- Efetuar Login\n");
    printf("2- Cadastrar Usuário\n");
    printf("3- Encerrar Programa\n");

    scanf("%d", &aux);

    switch(aux){
        case 1:{
            int auxErro;
            for(auxErro=0;auxErro<=2;auxErro++){
                char userAux[20], senhaAux[20];
                printf("\nUsuário: ");
                scanf("%s", userAux);

                printf("Senha: ");
                scanf("%s", senhaAux);

                int teste = VerificarLogin(userAux, senhaAux);
                if(teste == 0){
                    printf("Login ou senha inválidos\n");
                }else{
                    break;
                }
                if(auxErro == 2){
                    printf("Terceira tentativa de login inválida, encerrando o programa...");
                    return 0;
                }
            }
            break;
        }

        case 2:{
            Login novo;
            printf("Usuário:");
            scanf("%s", novo.usuario);
            printf("Senha:");
            scanf("%s", novo.senha);
            CadastrarNovoUsuario(novo);
            break;
        }

        case 3:{
            return 0;
            break;
        }
    }

    printf("---------------\nFIM.\n------------------------");
    return 0;
    exit(0);
}
