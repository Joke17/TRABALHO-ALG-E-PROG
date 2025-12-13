#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cabecalho.h" 


// inserir Nova Consulta 

void InserirNovaConsulta() {
    Consulta nova_consulta;
    FILE *arq_consultas;
    int crm_existe, cpf_existe;

    printf("\nCadastrar Nova Consulta \n");

    printf("Digite o CRM do Médico: ");
    scanf("%5s", nova_consulta.crm_medico); 

    printf("Digite o CPF do Paciente: ");
    scanf("%11s", nova_consulta.cpf_paciente); 


    
}


void ListarConsultasPorMedico(); 
void ListarConsultasPorPaciente(); 
void ListarConsultasPorData();







