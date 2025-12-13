#ifndef CABECALHO_H  
#define CABECALHO_H 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct Login{
    char usuario[20];
    char senha[10];
} Login;


typedef struct Medico{
    char CRM[6];
    char nome[50];
    char especialidade[20];
    char data_de_nascimento[12];
    float valor_hora_trabalho; 
    char telefone[14];
} Medico;

typedef struct Paciente{
    char CPF[12];
    char nome[30];
    char data_de_nascimento[12]; 
    char telefone[14];
} Paciente;

// alequis: estrutura da consulta 
typedef struct Consulta{
    char crm_medico[6];
    char cpf_paciente[12];
    char data[12];
    char sintomas[100];
    char encaminhamentos[100];
} Consulta;


typedef struct {
    char chave[12]; // CPF ou CRM
    int posicao;    // posição do registro no arquivo binário
} IndexPaciente, IndexMedico;

//Vetores carregados do .bin
//Pacientes
void AbreVetores(){
    //char cwd[1024];
    //_getcwd(cwd, sizeof(cwd));
    // printf("Diretório de trabalho atual: %s\n", cwd);
    
    // Pacientes
    FILE *ptpacientes;
    ptpacientes = fopen("pacientes.bin", "rb");
    if(ptpacientes == NULL){
        printf("deu merda\n");
    }

    fseek(ptpacientes, 0, SEEK_END);
    long tamanho = (int)ftell(ptpacientes);
    rewind(ptpacientes);
    fclose(ptpacientes);

    int quantidade = tamanho / sizeof(Paciente);
    //printf("%d", quantidade);
    Paciente *vetPacientes = (Paciente *) malloc(quantidade * sizeof(Paciente));
    char *vetCPF = (char *) malloc(quantidade * sizeof(char[12]));

    for(int i = 0; i<quantidade; i++){
        fread(&vetPacientes[quantidade], sizeof(Paciente), quantidade, ptpacientes);
        fread(&vetCPF[quantidade], sizeof(char[12]), quantidade, ptpacientes);
    }
    for(int i = 0; i<quantidade; i++)
        printf("nome %s\ncpf %s\n", vetPacientes[quantidade].nome, vetCPF[0]);
    //printf("\n vet %ld\n", tamanho);

}

int BuscarMedicoPorCRM(char crm_alvo[]);
int BuscarPacientePorCPF(char cpf_alvo[]);


//Funçoes Joke
void InserirNovoPaciente(Paciente paciente){
    FILE *ptarq;
    ptarq = fopen("pacientes.bin", "a+");
    // ptarq = fopen("pacientes.bin", "wb");

    if(ptarq == NULL){
        printf("deu merda\n");
    }
    fwrite(&paciente, sizeof(Paciente), 1, ptarq);
    fclose(ptarq);


    printf("du bao\n");
}
void AlterarDadosPaciente(){
    printf("\ndeu bao\n");
}
void BuscarPacientePorNome();
void ListaPacientes();


//funcoes alex - consultas
void InserirNovaConsulta(); 
void ListarConsultasPorMedico(); 
void ListarConsultasPorPaciente(); 
void ListarConsultasPorData();

#endif