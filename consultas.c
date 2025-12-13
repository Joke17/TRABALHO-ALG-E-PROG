#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cabecalho.h" 


// inserir consulta 

void InserirNovaConsulta() {
    Consulta nova_consulta;
    FILE *arq_consultas;
    int crm_existe, cpf_existe;

    printf("\nCadastrar Nova Consulta \n");

    printf("Digite o CRM do Médico: ");
    scanf("%5s", nova_consulta.crm_medico); 

    printf("Digite o CPF do Paciente: ");
    scanf("%11s", nova_consulta.cpf_paciente);  
    //pra validar se um medico existe usando a fucnao de busca por crm 
    crm_existe = buscarMedicoPorCRM(nova_consulta.crm_medico); 
    
    if (crm_existe < 0) {
        printf(" O CRM %s não está cadastrado.\n", nova_consulta.crm_medico);
        return; 
    }


    
}


void ListarConsultasPorMedico(); 
void ListarConsultasPorPaciente(); 
void ListarConsultasPorData();







