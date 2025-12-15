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
    //DebugListarIndices();
    // A função AbreVetores() está na cabecalho.h e pode ser mantida
   CarregarIndicePacientes();
    InserirNovoPaciente();

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

    MenuLogin();

    printf("---------------\nFIM.\n------------------------");
    return 0;
    exit(0);
}
