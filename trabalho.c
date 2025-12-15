#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "cabecalho.h"


int main() {
    setlocale(LC_ALL, "PORTUGUESE");
    
    printf("---------------\nINICIO\n------------------------\n\n");
    printf("DEBUG: CHAMA CARREGAR INDICES\n");
    CarregarIndicesMedicos();

    // Comente TUDO o que for InserirNovaConsulta() ou InserirNovoMedico()

    // ------------------------------------------------------------------
    // --- 3. TESTE DA SUA FUNÃÃO DE LISTAGEM (ÃNICA ATIVA) ---
    // ------------------------------------------------------------------
    printf("\nDEBUG: INICIO DO TESTE ListarConsultasPorMedico\n");
    ListarConsultasPorMedico();
    printf("\nDEBUG: FIM DO TESTE ListarConsultasPorMedico\n");
    
    // --- 4. FINALIZAÃÃO ---
    printf("DEBUG: SALVA INDICES\n");
    SalvarIndicesMedicos();
/*
   
   // --- 1. PREPARAÃÃO: CARREGA ÃNDICES DOS MÃDICOS ---
    CarregarIndicesMedicos();
    //DebugListarIndices();
    // A funÃ§Ã£o AbreVetores() estÃ¡ na cabecalho.h e pode ser mantida
    CarregarIndicePacientes();
    InserirNovoPaciente();

    // ------------------------------------------------------------w-------------------------
    // --- 2. TESTE DE CADASTRO DE MÃDICO (Execute SÃ A PRIMEIRA VEZ, DEPOIS COMENTE) ---
    // -------------------------------------------------------------------------------------
    
    // ATENÃÃO: Descomente a linha abaixo, compile, execute. 
    // Cadastre um mÃ©dico (ex: CRM 12345) e depois COMENTE de novo para fazer o teste da consulta.
    InserirNovoMedico(); 


    // ---------------------------------------------
    // --- 3. TESTE DA SUA FUNÃÃO DE CONSULTA ---
    // ---------------------------------------------
    // Aqui vocÃª testarÃ¡:
    // a) Se digitar o CRM cadastrado (ex: 12345), deve prosseguir.
    // b) Se digitar um CRM invÃ¡lido (ex: 99999), deve dar ERRO.
    printf("\n--- Testando InserirNovaConsulta ---\n");
    InserirNovaConsulta();
    printf("------------------------------------\n");
    
    
    // --- 4. FINALIZAÃÃO: SALVA ÃNDICES E LIMPA MEMÃRIA ---
    SalvarIndicesMedicos();
    */
   
    //Paciente p;
    //strcpy(p.nome, "JoÃ£o");

    //InserirNovoPaciente(p);
    //ListarConsultasPorMedico();

    MenuLogin();

    printf("---------------\nFIM.\n------------------------");
    return 0;
    exit(0);
}
