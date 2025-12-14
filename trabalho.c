#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "cabecalho.h"


int main() {
    setlocale(LC_ALL, "PORTUGUESE");
    
    printf("---------------\nINICIO\n------------------------\n\n");


    AbreVetores();
    // ----------------------------------------------------
    // --- 1. PREPARAR O AMBIENTE (CARREGAR OS ÍNDICES) ---
    // ----------------------------------------------------
    CarregarIndicesMedicos();
    
    // OBS: Se você tiver a função AbreVetores() ela deve ser chamada antes de CarregarIndicesMedicos() 
    // ou você precisa garantir que CarregarIndicesMedicos() não sobrescreva a memória de outros vetores.

    
    // ----------------------------------------------------
    // --- 2. GARANTIR DADOS (Cadastrar Médico p/ Teste) ---
    // ----------------------------------------------------
    // * DESCOMENTE e execute UMA SÓ VEZ para cadastrar um médico com CRM (ex: 12345).
    // * DEPOIS COMENTE NOVAMENTE para evitar cadastrar o mesmo várias vezes.
    // InserirNovoMedico(); 


    // ----------------------------------------------------
    // --- 3. EXECUTAR O TESTE (A SUA FUNÇÃO) ---
    // ----------------------------------------------------
    InserirNovaConsulta();


    // ----------------------------------------------------
    // --- 4. FINALIZAR (Salvar e Liberar Memória) ---
    // ----------------------------------------------------
    // Salva o novo médico no índice (se ele foi cadastrado) e limpa a RAM.
    SalvarIndicesMedicos(); 

    printf("---------------\nFIM DO TESTE.\n------------------------");

    // ... O seu código de menu e login continua aqui ...
    // ... Aqui você pode chamar InserirNovaConsulta() novamente se o login for bem-sucedido ...
    
   
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
