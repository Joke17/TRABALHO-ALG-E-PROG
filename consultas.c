#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cabecalho.h" 

// IA pura o cara tem nem vergonha kkkkkkkkkkkkk

// Inserir Nova Consulta 

void InserirNovaConsulta() {
    Consulta nova_consulta;
    FILE *arq_consultas;
    int crm_existe, cpf_existe;

    printf("\n--- Cadastrar Nova Consulta ---\n");


    printf("Digite o CRM do M�dico: ");
    scanf("%5s", nova_consulta.crm_medico); 

    printf("Digite o CPF do Paciente: ");
    scanf("%11s", nova_consulta.cpf_paciente); 

    
    // Chamamos a fun��o de validacao do medico
    crm_existe = buscarMedicoPorCRM(nova_consulta.crm_medico); 
    
    if (crm_existe < 0) {
        printf("ERRO: O CRM %s n�o est� cadastrado. Abortando consulta.\n", nova_consulta.crm_medico);
        return; // Sai da fun��o
    }
     

    // Valida��o do Paciente 
   
    cpf_existe = buscarPacientePorCPF(nova_consulta.cpf_paciente); 
    
    if (cpf_existe < 0) {
        printf("ERRO: O CPF %s n�o est� cadastrado. Abortando consulta.\n", nova_consulta.cpf_paciente);
        return; // Sai da fun��o
    }

    //  Coletar o Resto dos Dados
    printf("Digite a Data da Consulta (DD/MM/AAAA): ");
    scanf("%11s", nova_consulta.data); 
    
    // Usar fgetc(stdin) para limpar o buffer antes de ler strings longas com gets/fgets
    char limpeza;
    while ((limpeza = getchar()) != '\n' && limpeza != EOF); 
    
    printf("Digite os Sintomas (m�x 99 caracteres): ");
    // fgets � mais seguro que scanf para strings
    fgets(nova_consulta.sintomas, 100, stdin);
    // Remover o \n que o fgets adiciona no final
    nova_consulta.sintomas[strcspn(nova_consulta.sintomas, "\n")] = 0; 

    printf("Digite os Encaminhamentos (m�x 99 caracteres): ");
    fgets(nova_consulta.encaminhamentos, 100, stdin);
    nova_consulta.encaminhamentos[strcspn(nova_consulta.encaminhamentos, "\n")] = 0;

    // Gravar no Arquivo
    arq_consultas = fopen("consultas.bin", "ab"); // 'ab': Append Binary (Adicionar no final)
    if (arq_consultas == NULL) {
        perror("Erro ao abrir o arquivo consultas.bin para escrita");
        return;
    }

    // fwrite(endere�o da struct, tamanho da struct, quantidade, ponteiro do arquivo)
    fwrite(&nova_consulta, sizeof(Consulta), 1, arq_consultas);

    fclose(arq_consultas);
    printf("\nConsulta cadastrada com sucesso!\n");
}






