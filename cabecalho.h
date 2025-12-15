#ifndef CABECALHO_H
#define CABECALHO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct Login
{
    char usuario[20];
    char senha[10];
} Login;

typedef struct Medico
{
    char CRM[6];
    char nome[50];
    char especialidade[20];
    char data_de_nascimento[12];
    float valor_hora_trabalho;
    char telefone[14];
} Medico;

typedef struct Paciente
{
    char CPF[12];
    char nome[30];
    char data_de_nascimento[12];
    char telefone[14];
} Paciente;

// alequis: estrutura da consulta
typedef struct Consulta
{
    char crm_medico[6];
    char cpf_paciente[12];
    char data[12];
    char sintomas[100];
    char encaminhamentos[100];
} Consulta;

typedef struct
{
    char chave[12]; // CPF ou CRM
    int posicao;    // posição do registro no arquivo binário
} IndexPaciente, IndexMedico;

//void OrdenaCPF();

int VerificarLogin(char user[], char senha[]);
void CadastrarNovoUsuario(Login novo);

// Vetores carregados do .bin
// Pacientes
// Funçoes Joke
void InserirNovoPaciente();
void AlterarDadosPaciente();
void AdicionarNaMao(); // SÓ PRA TESTE
void CarregarIndicePacientes();
// void BuscarPaciente();
void ListaPacientes();
int BuscarPacientePorCPF();

// funcoes medicos
void CarregarIndicesMedicos();
void SalvarIndicesMedicos();
void InserirNovoMedico();
void ListarMedicos();
int buscaBinariaMedico(char *crmBusca);

void DebugListarIndices(); // testando um bagui

// funcoes alex - consultas
void InserirNovaConsulta();
void ListarConsultasPorMedico();
void ListarConsultasPorPaciente();
void ListarConsultasPorData();

// funcoes menu
void MenuLogin();
void MenuPrincipal();
void MenuPacientes();
void MenuMedicos();
void MenuConsultas();

#endif