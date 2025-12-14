#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "cabecalho.h"


int main() {
    setlocale(LC_ALL, "PORTUGUESE");
    
    printf("---------------\nINICIO\n------------------------\n\n");


    //AbreVetores();
   // --- 1. PREPARAÇÃO: CARREGA ÍNDICES DOS MÉDICOS ---
    CarregarIndicesMedicos();
    // A função AbreVetores() está na cabecalho.h e pode ser mantida
    CarregarIndicePacientes();

    // ------------------------------------------------------------w-------------------------
    // --- 2. TESTE DE CADASTRO DE MÉDICO (Execute SÓ A PRIMEIRA VEZ, DEPOIS COMENTE) ---
    // -------------------------------------------------------------------------------------
    
    // ATENÇÃO: Descomente a linha abaixo, compile, execute. 
    // Cadastre um médico (ex: CRM 12345) e depois COMENTE de novo para fazer o teste da consulta.
    InserirNovoMedico(); 


    // ---------------------------------------------
    // --- 3. TESTE DA SUA FUNÇÃO DE CONSULTA ---
    // ---------------------------------------------
    // Aqui você testará:
    // a) Se digitar o CRM cadastrado (ex: 12345), deve prosseguir.
    // b) Se digitar um CRM inválido (ex: 99999), deve dar ERRO.
    printf("\n--- Testando InserirNovaConsulta ---\n");
    InserirNovaConsulta();
    printf("------------------------------------\n");
    
    
    // --- 4. FINALIZAÇÃO: SALVA ÍNDICES E LIMPA MEMÓRIA ---
    SalvarIndicesMedicos();
    
   
    //Paciente p;
    //strcpy(p.nome, "João");

    //InserirNovoPaciente(p);
    //ListarConsultasPorMedico();

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
            return 0;
            break;
        }
    }

    printf("---------------\nFIM.\n------------------------");
    return 0;
    exit(0);
}
