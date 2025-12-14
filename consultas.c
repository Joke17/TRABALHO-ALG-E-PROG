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

    printf("Digite o CRM do Mï¿½dico: ");
    scanf("%5s", nova_consulta.crm_medico); 

    printf("Digite o CPF do Paciente: ");
    scanf("%11s", nova_consulta.cpf_paciente); 

    //pra validar se um medico existe usando a fucnao de busca por crm 
    crm_existe = buscaBinariaMedico(nova_consulta.crm_medico); 

    
    if (crm_existe < 0) {
        printf("ERRO: O CRM %s não está cadastrado.\n", nova_consulta.crm_medico);
        return; 
    }
     
    printf("Digite a Data da Consulta (DD/MM/AAAA): ");
    scanf("%11s", nova_consulta.data); 
    
    // usar fgetc(stdin) para limpar o buffer antes de ler strings longas com gets/fgets
    char dummy;
    while ((dummy = getchar()) != '\n' && dummy != EOF); 
    
    printf("Digite os Sintomas (máx 99 caracteres): ");
    // fgets é mais seguro que scanf para strings
    fgets(nova_consulta.sintomas, 100, stdin);
    // remove o \n que o fgets adiciona no final
    nova_consulta.sintomas[strcspn(nova_consulta.sintomas, "\n")] = 0; 

    printf("Digite os Encaminhamentos (máx 99 caracteres): ");
    fgets(nova_consulta.encaminhamentos, 100, stdin);
    nova_consulta.encaminhamentos[strcspn(nova_consulta.encaminhamentos, "\n")] = 0;

    // gravar no arquivo consultas.bin
    arq_consultas = fopen("consultas.bin", "ab"); // 'ab': Append Binary (Adicionar no final)
    if (arq_consultas == NULL) {
        perror("Erro ao abrir o arquivo consultas.bin para escrita");
        return;
    }

    // fwrite(endereço da struct, tamanho da struct, quantidade, ponteiro do arquivo)
    fwrite(&nova_consulta, sizeof(Consulta), 1, arq_consultas);

    fclose(arq_consultas);
    printf("\nConsulta cadastrada com sucesso!\n");

}


//buceta
void ListarConsultasPorMedico() {
    printf("\nListar Consultas por Médicos\n");   
}

void ListarConsultasPorPaciente(); 
void ListarConsultasPorData();







