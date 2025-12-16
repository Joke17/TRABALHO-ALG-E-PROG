#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "cabecalho.h"
#include <unistd.h>  //biblioteca pesquisada por alequis para usar a função sleep que da uma mini pausa na execução do programa.

void LimparTela() {
    system("cls");
}


void MenuLogin(){
    int aux;
    do{
        sleep(2);
        LimparTela();
        printf("1- Efetuar Login\n");
        printf("2- Cadastrar Usuário\n");
        printf("0- Encerrar Programa\n");

        scanf("%d", &aux);

        switch(aux){
            case 1:{
                LimparTela();
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
                        MenuPrincipal();
                        break;
                    }
                    if(auxErro == 2){
                        printf("Terceira tentativa de login inválida, encerrando o programa...");
                        return;
                    }
                }
                break;
            }

            case 2:{
                LimparTela();
                Login novo;
                printf("Usuário:");
                scanf("%s", novo.usuario);
                printf("Senha:");
                scanf("%s", novo.senha);
                CadastrarNovoUsuario(novo);
                break;
            }

            case 0:{
                return;
            }
        }
    }while(aux!=0);
}

void MenuPrincipal(){
    int aux;

    do{
        sleep(0.5);
        LimparTela();
        printf("1- Pacientes\n");
        printf("2- Médicos\n");
        printf("3- Consultas\n");
        printf("0- Voltar para a página anterior\n");

        scanf("%d", &aux);

        switch(aux){
            case 1:{
               LimparTela();
                MenuPacientes();
                break;
            }
            case 2:{
               LimparTela();
                MenuMedicos();
                break;
            }
            case 3:{
               LimparTela();
                MenuConsultas();
                break;
            }
            case 0:{
                return;
            }
        }
    }while(aux!=0);
}

void MenuPacientes(){
    int aux;
    do{
        //LimparTela();
        printf("1- Inserir novo paciente\n");
        printf("2- Buscar paciente por nome\n");
        printf("3- Alterar dados do paciente\n"); 
        printf("4- Excluir paciente\n");
        printf("5- Listar pacientes\n");
        printf("0- Voltar para a página anterior\n");

        scanf("%d", &aux);

        switch(aux){
            case 1:{
                LimparTela();
                InserirNovoPaciente();
                break;
            }

            case 2:{
                LimparTela();
                BuscarPacientePorNome();
                break;
            }

            case 3:{
                LimparTela();
                AlterarDadosPaciente();
                break;
            }
            case 4:{
                LimparTela();
                ExcluirPaciente();
                break;
            }
            case 5:{
                LimparTela();
                ListaPacientes();
                break;
            }

            case 0:{
                return;
            }
        }
    }while(aux!=0);
}

void MenuMedicos(){
    int aux;
    do{
       //LimparTela();
        printf("1- Inserir novo médico\n");
        printf("2- Buscar médico por nome\n");
        printf("3- Listar médicos por especialidade\n"); 
        printf("4- Alterar dados do médico\n"); 
        printf("5- Excluir médico\n");
        printf("0- Voltar para a página anterior\n");

        scanf("%d", &aux);

        switch(aux){
            case 1:{
                LimparTela();
                InserirNovoMedico();
                break;
            }

            case 2:{
                LimparTela();
                BuscarMedicoPorNome();
                break;
            }

            case 3:{
               LimparTela();
                ListarMedicos();
                break;
            }

            case 4:{
                LimparTela();
                EditarMedico(); 
                break;
            }

            case 5:{
               LimparTela();
               ExcluirMedico();
                break;
            }

            case 0:{
                return;
            }
        }
    }while(aux!=0);
}

void MenuConsultas(){
    int aux;

    do{
        //LimparTela();
        printf("1- Agendar nova consulta\n");
        printf("2- Listar consultas por médico(CRM)\n");
        printf("3- Listar consultas por paciente(CPF)\n"); 
        printf("4- Listar consultas por data\n"); 
        printf("0- Voltar para a página anterior\n");

        scanf("%d", &aux);
        switch(aux){
            case 1:{
                LimparTela();
                InserirNovaConsulta();
                break;
            }

            case 2:{
                LimparTela();
                ListarConsultasPorMedico();
                break;
            }

            case 3:{
                LimparTela();
                ListarConsultasPorPaciente();
                break;
            }

            case 4:{
               LimparTela();
               ListarConsultasPorData();
               break; 
            }

            case 0:{
                return;
            }
        }
    }while(aux!=0);
}