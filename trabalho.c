#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "cabecalho.h"


int main() {
    setlocale(LC_ALL, "PORTUGUESE");
    printf("---------------\nINICIO\n------------------------\n\n");

    // --- 1. PREPARAÇÃO: CARREGA ÍNDICES DOS MÉDICOS ---
    CarregarIndicesMedicos();
    
    // ------------------------------------------------------------------
    // --- A. CRIAR DADOS DE TESTE (Rode SÓ NA PRIMEIRA VEZ, DEPOIS COMENTE) ---
    // ------------------------------------------------------------------
    
    //printf("\n--- Criando Consultas de Teste (Use as datas 01/12/2025 e 15/12/2025) ---\n");
    
    // 1ª Chamada: Use a data 01/12/2025
   // InserirNovaConsulta(); 
    
    // 2ª Chamada: Use a data 15/12/2025
    //InserirNovaConsulta(); 
    
    // 3ª Chamada: Use a data 01/12/2025 novamente
    //InserirNovaConsulta(); 
    
    //printf("\n--- FIM da Criação de Dados ---\n");
    

    // ------------------------------------------------------------------
    // --- B. LISTAR DADOS (Rode na SEGUNDA VEZ, comentando a seção A) ---
    // ------------------------------------------------------------------
    printf("\n--- TESTANDO ListarConsultasPorData ---\n");
    ListarConsultasPorData();
    printf("-----------------------------------------\n");

    // --- 4. FINALIZAÇÃO: SALVA ÍNDICES E LIMPA MEMÓRIA ---
    SalvarIndicesMedicos();


     
  /* // --- 1. PREPARAÇÃO: CARREGA ÍNDICES DOS MÉDICOS ---
    CarregarIndicesMedicos();
    
    // ------------------------------------------------------------------
    // --- A. CRIAR DADOS DE TESTE (Rode SÓ NA PRIMEIRA VEZ, DEPOIS COMENTE) ---
    // ------------------------------------------------------------------
    
    printf("\n--- Criando Consultas de Teste para o Paciente (Use o CPF 12345678900) ---\n");
    // Rode 2 vezes: na primeira, use o CPF de teste (Ex: 12345678900).
    InserirNovaConsulta(); 
    // Na segunda, use o mesmo CPF e dados diferentes.
    InserirNovaConsulta(); 
    printf("\n--- FIM da Criação de Dados ---\n");
    

    // ------------------------------------------------------------------
    // --- B. LISTAR DADOS (Rode na SEGUNDA VEZ, comentando a seção A) ---
    // ------------------------------------------------------------------
    printf("\n--- TESTANDO ListarConsultasPorPaciente ---\n");
    ListarConsultasPorPaciente();
    printf("-----------------------------------------\n");

    // --- 4. FINALIZAÇÃO: SALVA ÍNDICES E LIMPA MEMÓRIA ---
    SalvarIndicesMedicos();
 */ 
/*
   
   // --- 1. PREPARAÇÃO: CARREGA ÍNDICES DOS MÉDICOS ---
    CarregarIndicesMedicos();
    //DebugListarIndices();
    // A função AbreVetores() está na cabecalho.h e pode ser mantida
   CarregarIndicePacientes();
   InserirNovoPaciente();
   AlterarDadosPaciente();
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
    */
   
    //Paciente p;
    //strcpy(p.nome, "João");

    //InserirNovoPaciente(p);
    //ListarConsultasPorMedico();

    //MenuLogin();

    printf("---------------\nFIM.\n------------------------");
    return 0;
    exit(0);
}
