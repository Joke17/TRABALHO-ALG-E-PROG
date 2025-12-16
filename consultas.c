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

    //limpar buffer do teclado
    char limpar;
    while ((limpar = getchar()) != '\n' && limpar != EOF); 
   
    // teste de Busca
    crm_existe = buscaBinariaMedico(nova_consulta.crm_medico); 

    if (crm_existe < 0) {
        printf("ERRO: O CRM %s não está cadastrado.\n", nova_consulta.crm_medico);
        return; 
    }
     
    printf("Digite o CPF do Paciente: ");
    scanf("%11s", nova_consulta.cpf_paciente); 

   
    while ((limpar = getchar()) != '\n' && limpar != EOF); 
   

    printf("Digite a Data da Consulta (DD/MM/AAAA): ");
    scanf("%11s", nova_consulta.data); 
    
    // limpeza original (que é mt importante antes do fgets)
    while ((limpar = getchar()) != '\n' && limpar != EOF); 
    
    printf("Digite os Sintomas (máx 99 caracteres): ");
   
    fgets(nova_consulta.sintomas, 100, stdin);
    // remove o \n que o fgets adiciona no final
    nova_consulta.sintomas[strcspn(nova_consulta.sintomas, "\n")] = 0; 

    printf("Digite os Encaminhamentos (máx 99 caracteres): ");
    fgets(nova_consulta.encaminhamentos, 100, stdin);
    nova_consulta.encaminhamentos[strcspn(nova_consulta.encaminhamentos, "\n")] = 0;
    // gravar no arquivo consultas.bin
    arq_consultas = fopen("output/consultas.bin", "ab"); // 'ab': append binary (adiciona so no final)
    if (arq_consultas == NULL) {
        perror("Erro ao abrir o arquivo consultas.bin para escrita");
        return;
    }

    // fwrite(endereço da struct, tamanho da struct, quant, ponteiro do arquivo)
    fwrite(&nova_consulta, sizeof(Consulta), 1, arq_consultas);

    fclose(arq_consultas);
    printf("\nConsulta cadastrada com sucesso!\n");

}
 
void ListarConsultasPorMedico() {
    printf("\nListar Consultas por Médicos\n");  
    FILE *arq_consultas;
    Consulta c;
    char crm_busca[6];
    int consultas_encontradas = 0;

    printf("\n--- Listar Consultas por Médico ---\n");
    printf("Digite o CRM do Médico para busca: ");
    scanf("%5s", crm_busca);
    int limpar;
    while ((limpar = getchar()) != '\n' && limpar != EOF);

    arq_consultas = fopen("output/consultas.bin", "rb"); // 'rb': read binary
    if (arq_consultas == NULL) {
        printf("Nenhuma consulta registrada.\n");
        return;
    }

    printf("\nConsultas para o CRM %s:\n", crm_busca);
   
    //  fread retorna 1 se leu um registro completo e 0 se chegou ao fim.
    while (fread(&c, sizeof(Consulta), 1, arq_consultas) == 1) {
       
        // comparação de string, strcmp retorna 0 se as strings são iguais.
        if (strcmp(c.crm_medico, crm_busca) == 0) {
            printf("-------------------------------------------\n");
            printf("Data: %s\n", c.data);
            printf("Paciente (CPF): %s\n", c.cpf_paciente);
            printf("Sintomas: %s\n", c.sintomas);
            printf("Encaminhamentos: %s\n", c.encaminhamentos);
            consultas_encontradas++;
        }
    }
   
    fclose(arq_consultas);
   
    if (consultas_encontradas == 0) {
        printf("Nenhuma consulta encontrada para este médico.\n");
    } else {
        printf("-------------------------------------------\n");
    } 
}

void ListarConsultasPorPaciente() {
    FILE *arq_consultas;
    Consulta c;
    char cpf_busca[12];
    int consultas_encontradas = 0;

    printf("\n--- Listar Consultas por Paciente ---\n");
    printf("Digite o CPF do Paciente para busca: ");
    scanf("%11s", cpf_busca);

    int limpar;
    while ((limpar = getchar()) != '\n' && limpar != EOF);

    arq_consultas = fopen("output/consultas.bin", "rb");
    if (arq_consultas == NULL) {
        printf("Nenhuma consulta registrada.\n");
        return;
    }

    printf("\nConsultas para o CPF %s:\n", cpf_busca);
    
    while (fread(&c, sizeof(Consulta), 1, arq_consultas) == 1) {
        // filtrar pelo CPF
        if (strcmp(c.cpf_paciente, cpf_busca) == 0) {
            printf("-------------------------------------------\n");
            printf("Data: %s\n", c.data);
            printf("Médico (CRM): %s\n", c.crm_medico);
            printf("Sintomas: %s\n", c.sintomas);
            printf("Encaminhamentos: %s\n", c.encaminhamentos);
            consultas_encontradas++;
        }
    }
    
    fclose(arq_consultas);
    
    if (consultas_encontradas == 0) {
        printf("Nenhuma consulta encontrada para este paciente.\n");
    } else {
        printf("-------------------------------------------\n");
    }
}

void ListarConsultasPorData() {
    FILE *arq_consultas;
    Consulta c;
    char data_busca[12];
    int consultas_encontradas = 0;

    printf("\n--- Listar Consultas por Data ---\n");
    printf("Digite a Data para busca (DD/MM/AAAA): ");
    scanf("%11s", data_busca);

    int limpar;
    while ((limpar = getchar()) != '\n' && limpar != EOF);


    arq_consultas = fopen("output/consultas.bin", "rb");
    if (arq_consultas == NULL) {
        printf("Nenhuma consulta registrada.\n");
        return;
    }

    printf("\nConsultas na data %s:\n", data_busca);

    //fread retorna 1 se leu um registro completo, 0 se chegou ao fim.
    while (fread(&c, sizeof(Consulta), 1, arq_consultas) == 1) {
        // filtrar pela data
        if (strcmp(c.data, data_busca) == 0) {
            printf("-------------------------------------------\n");
            printf("Médico (CRM): %s\n", c.crm_medico);
            printf("Paciente (CPF): %s\n", c.cpf_paciente);
            printf("Sintomas: %s\n", c.sintomas);
            printf("Encaminhamentos: %s\n", c.encaminhamentos);
            consultas_encontradas++;
        }
    }
    
    fclose(arq_consultas);
    
    if (consultas_encontradas == 0) {
        printf("Nenhuma consulta encontrada nesta data.\n");
    } else {
        printf("-------------------------------------------\n");
    }
}