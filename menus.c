#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "cabecalho.h"

void MenuLogin(){
    int aux;

    printf("1- Efetuar Login\n");
    printf("2- Cadastrar Usuário\n");
    printf("0- Encerrar Programa\n");

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
                    MenuPrincipal();
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

        case 0:{
            return;
            break;
        }
    }
}

void MenuPrincipal(){
    int aux;

    printf("1- Pacientes\n");
    printf("2- Médicos\n");
    printf("3- Consultas\n");

    scanf("%d", &aux);

    switch(aux){
        case 1:{
            MenuPacientes();
            break;
        }
        case 2:{
            MenuMedicos();
            break;
        }
        case 3:{
            MenuConsultas();
            break;
        }
    }
}

void MenuPacientes(){
    int aux;
    printf("1- Inserir novo paciente\n");
    printf("2- Buscar paciente por nome\n");
    printf("3- Alterar dados do paciente\n"); 

    scanf("%d", &aux);

    switch(aux){
        case 1:{
            Paciente paciente;
            printf("Digite o nome do paciente: ");
            scanf(" %[^\n]", paciente.nome);

            printf("Digite o CPF do paciente: ");
            scanf(" %s", paciente.CPF);

            printf("Digite a data de nascimento do paciente: ");
            scanf(" %s", paciente.data_de_nascimento);

            printf("Digite o telefone do paciente: ");
            scanf(" %s", paciente.telefone);

            InserirNovoPaciente(paciente);
            break;
        }

        case 2:{
            char nome[50];
            printf("Digite o nome do paciente que deseja buscar: ");
            scanf(" %[^\n]", nome);
            BuscarPacientePorNome(nome);
            break;
        }

        case 3:{
            char cpf[12];
            printf("Digite o CPF do paciente que deseja alterar: ");
            scanf(" %s", cpf);
            AlterarDadosPaciente(cpf);
            break;
        }
    }
}

void MenuMedicos(){
    int aux;
    printf("1- Inserir novo médico\n");
    printf("2- Buscar médico por nome\n");
    printf("3- Listar médicos por especialidade\n"); 
    printf("4- Alterar dados do médico\n"); 

    scanf("%d", &aux);

    switch(aux){
        case 1:{
            Paciente paciente;
            printf("Digite o nome do paciente: ");
            scanf(" %[^\n]", paciente.nome);

            printf("Digite o CPF do paciente: ");
            scanf(" %s", paciente.CPF);

            printf("Digite a data de nascimento do paciente: ");
            scanf(" %s", paciente.data_de_nascimento);

            printf("Digite o telefone do paciente: ");
            scanf(" %s", paciente.telefone);

            InserirNovoPaciente(paciente);
            break;
        }

        case 2:{
            char nome[50];
            printf("Digite o nome do paciente que deseja buscar: ");
            scanf(" %[^\n]", nome);
            BuscarPacientePorNome(nome);
            break;
        }

        case 3:{
            char especialidade[20];
            printf("Digite a especialidade para fazer a busca: ");
            scanf(" %[^\n]",especialidade);
            ListarMedicos(especialidade);
            break;
        }

        case 4:{
            char crm[12];
            printf("Digite o CPF do médico que deseja alterar: ");
            scanf(" %s", crm);
            //funcao editar heros
            break;
        }
    }
}

void MenuConsultas(){
    int aux;
    printf("1- Agendar nova consulta\n");
    printf("2- Listar consultas por médico(CRM)\n");
    printf("3- Listar consultas por paciente(CPF)\n"); 
    printf("4- Listar consultas por data\n"); 

    scanf("%d", &aux);

    switch(aux){
        case 1:{
            Consulta nova;

            printf("CRM do Medico: ");
            scanf("%s", nova.crm_medico);
                
            printf("CPF do Paciente: ");
            scanf("%s", nova.cpf_paciente);
                
            printf("Data (dd/mm/aaaa): ");
            scanf("%s", nova.data); 
                
            printf("Sintomas: ");
            scanf(" %[^\n]", nova.sintomas); 
                
            printf("Encaminhamento/Observação: ");
            scanf(" %[^\n]", nova.encaminhamentos);
                
            InserirNovaConsulta(nova);
            break;
        }

        case 2:{
            char crm[6];
            printf("Digite o CRM do médico para fazer a busca: ");
            scanf(" %[^\n]", crm);
            ListarConsultasPorMedico(crm);
            break;
        }

        case 3:{
            char cpf[12];
            printf("Digite o CPF do médico para fazer a busca: ");
            scanf(" %[^\n]", cpf);
            ListarConsultasPorPaciente(cpf);
            break;
        }

        case 4:{
            char data[12];
            printf("Digite a data para fazer a busca: ");
            scanf(" %s", data);
            ListarConsultasPorData(data);
            break;
        }
    }
}