#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cabecalho.h" 

#define QUANT_TESTE 3

 //função auxiliar para verificar se o arquivo existe e está vazio.
 //fiz isso aqui para evitar que toda vez que o programa rodar ele adicione os mesmosarquivos de dados de teste
 //assim evita problemas de duplicidade de CRM e CPF que sao chaves primarias

int VerificarSeDeveCriar(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "rb"); 
    
    if (arquivo == NULL) {
        return 1; 
    }
    
    fseek(arquivo, 0, SEEK_END);
    long tamanho = ftell(arquivo);
    fclose(arquivo);
    
    if (tamanho == 0) {
        return 1; 
    }
    
    return 0; 
}


void CargaInicial(){

    IndexMedico indicesMedicos[QUANT_TESTE];
    IndexPaciente indicesPacientes[QUANT_TESTE];
    long posicaoAtual = 0; 

    if(VerificarSeDeveCriar("output/login.bin")) {
        FILE *loginIni = fopen("output/login.bin", "wb");  // abre o arquivo (sobrescreve o vazio/cria o novo)
        
        Login l1 = {"Teste1", "123"};
        Login l2 = {"Teste2", "1234"};
        Login l3 = {"Teste3", "12345"};

        fwrite(&l1, sizeof(Login), 1, loginIni);
        fwrite(&l2, sizeof(Login), 1, loginIni);
        fwrite(&l3, sizeof(Login), 1, loginIni);
        printf("Logins de teste criados.\n");
        
        fclose(loginIni);
    }
    //cria apenas se os dados ou os ÍNDICES não existirem/estiverem vazios.
    if(VerificarSeDeveCriar("output/medicos.bin") || VerificarSeDeveCriar("output/indices_medicos.bin")){
        
        FILE *medicoIni = fopen("output/medicos.bin", "wb"); 
        FILE *indicesMedicoIni = fopen("output/indices_medicos.bin", "wb");
        
        Medico m1 = {"11111", "Medico Teste1", "Geral", "01/01/1980", 100.0, "11111111111"};
        Medico m2 = {"22222", "Medico Teste2", "Geral", "02/02/1980", 200.0, "22222222222"};
        Medico m3 = {"33333", "Medico Teste3", "Geral", "03/03/1980", 300.0, "33333333333"};

        fseek(medicoIni, 0, SEEK_SET);

        posicaoAtual = ftell(medicoIni);
        fwrite(&m1, sizeof(Medico), 1, medicoIni);
        strcpy(indicesMedicos[0].chave, m1.CRM);
        indicesMedicos[0].posicao = posicaoAtual;

        posicaoAtual = ftell(medicoIni);
        fwrite(&m2, sizeof(Medico), 1, medicoIni);
        strcpy(indicesMedicos[1].chave, m2.CRM);
        indicesMedicos[1].posicao = posicaoAtual;
        
        posicaoAtual = ftell(medicoIni);
        fwrite(&m3, sizeof(Medico), 1, medicoIni);
        strcpy(indicesMedicos[2].chave, m3.CRM);
        indicesMedicos[2].posicao = posicaoAtual;
        
        fwrite(indicesMedicos, sizeof(IndexMedico), QUANT_TESTE, indicesMedicoIni);
        
        printf("Medicos de teste e índices criados.\n");
        
        fclose(medicoIni);
        fclose(indicesMedicoIni);
    }

    if(VerificarSeDeveCriar("output/pacientes.bin") || VerificarSeDeveCriar("output/indices_pacientes.bin")){
        
        FILE *pacienteIni = fopen("output/pacientes.bin", "wb"); 
        FILE *indicesPacienteIni = fopen("output/indices_pacientes.bin", "wb");
        
        Paciente p1 = {"11111111111", "Paciente Teste1", "01/01/2000", "38777777777"};
        Paciente p2 = {"22222222222", "Paciente Teste2", "02/02/2000", "38888888888"};
        Paciente p3 = {"33333333333", "Paciente Teste3", "03/03/2000", "38999999999"};

        fseek(pacienteIni, 0, SEEK_SET); 

        posicaoAtual = ftell(pacienteIni);
        fwrite(&p1, sizeof(Paciente), 1, pacienteIni);
        strcpy(indicesPacientes[0].chave, p1.CPF);
        indicesPacientes[0].posicao = posicaoAtual;

        posicaoAtual = ftell(pacienteIni);
        fwrite(&p2, sizeof(Paciente), 1, pacienteIni);
        strcpy(indicesPacientes[1].chave, p2.CPF);
        indicesPacientes[1].posicao = posicaoAtual;
        
        posicaoAtual = ftell(pacienteIni);
        fwrite(&p3, sizeof(Paciente), 1, pacienteIni);
        strcpy(indicesPacientes[2].chave, p3.CPF);
        indicesPacientes[2].posicao = posicaoAtual;

        fwrite(indicesPacientes, sizeof(IndexPaciente), QUANT_TESTE, indicesPacienteIni);
        
        printf("Pacientes de teste e índices criados.\n");
        
        fclose(pacienteIni);
        fclose(indicesPacienteIni);
    }

    if(VerificarSeDeveCriar("output/consultas.bin")) {
        FILE *consultaIni = fopen("output/consultas.bin", "wb"); 

        Consulta c1 = {"11111", "11111111111", "01/01/2025", "Sintoma Teste1", "Encaminhamento Teste1"};
        Consulta c2 = {"22222", "22222222222", "02/02/2025", "Sintoma Teste2", "Encaminhamento Teste2"};
        Consulta c3 = {"33333", "33333333333", "03/03/2025", "Sintoma Teste3", "Encaminhamento Teste3"};

        fwrite(&c1, sizeof(Consulta), 1, consultaIni);
        fwrite(&c2, sizeof(Consulta), 1, consultaIni);
        fwrite(&c3, sizeof(Consulta), 1, consultaIni);
        printf("Consultas de teste criadas.\n");
        
        fclose(consultaIni);
    }
}