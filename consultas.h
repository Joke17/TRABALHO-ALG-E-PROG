#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cabecalho.h" 




// inserir consulta 

/*void InserirNovaConsulta() {
    Consulta nova_consulta;
    FILE *arq_consultas;
    int crm_existe, cpf_existe;

    printf("\nCadastrar Nova Consulta \n");

    printf("Digite o CRM do Mï¿½dico: ");
    scanf("%5s", nova_consulta.crm_medico); 

    printf("Digite o CPF do Paciente: ");
    scanf("%11s", nova_consulta.cpf_paciente); 

    //pra validar se um medico existe usando a fucnao de busca por crm 
    crm_existe = buscarMedicoPorCRM(nova_consulta.crm_medico); 

    //considerando q a funcao vai me retornar -1 se n achar 
    
    if (crm_existe < 0) {
        printf("ERRO: O CRM %s nï¿½o estï¿½ cadastrado. Abortando consulta.\n", nova_consulta.crm_medico);
        return; 
    }
     


}

*/

//buceta
void ListarConsultasPorMedico() {
    printf("\nListar Consultas por Médicos\n");    // Implementaï¿½ï¿½o da funï¿½ï¿½o
}

void ListarConsultasPorPaciente(); 
void ListarConsultasPorData();







