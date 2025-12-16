#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cabecalho.h" 

void CargaInicial(){

    IndexMedico indicesMedicos[3];
    IndexPaciente indicesPacientes[3];
    long posicaoAtual = 0;

    FILE *loginIni = fopen("output/login.bin", "a+b");
    fseek(loginIni, 0, SEEK_SET); 
    long tamanho = ftell(loginIni);
    if(tamanho == 0){
        Login l1 = {"Teste1", "123"};
        Login l2 = {"Teste2", "1234"};
        Login l3 = {"Teste3", "12345"};

        fseek(loginIni, 0, SEEK_END); 

        fwrite(&l1, sizeof(Login), 1, loginIni);
        fwrite(&l2, sizeof(Login), 1, loginIni);
        fwrite(&l3, sizeof(Login), 1, loginIni);
        printf("Logins de teste criados.\n");
    }
    fclose(loginIni);

    FILE *medicoIni = fopen("output/medicos.bin", "a+b");
    FILE *indicesMedicoIni = fopen("output/indices_medicos.bin", "a+b");
    
    fseek(medicoIni, 0, SEEK_SET);
    fseek(indicesMedicoIni, 0, SEEK_SET);
    
    if(ftell(medicoIni) == 0 && ftell(indicesMedicoIni) == 0){
        
        Medico m1 = {"11111", "Medico Teste1", "Geral", "01/01/1980", 100.0, "11111111111"};
        Medico m2 = {"22222", "Medico Teste2", "Geral", "02/02/1980", 200.0, "22222222222"};
        Medico m3 = {"33333", "Medico Teste3", "Geral", "03/03/1980", 300.0, "33333333333"};

        fseek(medicoIni, 0, SEEK_END);

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
        
        fseek(indicesMedicoIni, 0, SEEK_END); 
        fwrite(indicesMedicos, sizeof(IndexMedico), 3, indicesMedicoIni);
        
        printf("Medicos de teste e índices criados.\n");
    }
    fclose(medicoIni);
    fclose(indicesMedicoIni);

    FILE *pacienteIni = fopen("output/pacientes.bin", "a+b");
    FILE *indicesPacienteIni = fopen("output/indices_pacientes.bin", "a+b");
    
    fseek(pacienteIni, 0, SEEK_SET);
    fseek(indicesPacienteIni, 0, SEEK_SET);

    if(ftell(pacienteIni) == 0 && ftell(indicesPacienteIni) == 0){
        
        Paciente p1 = {"11111111111", "Paciente Teste1", "01/01/2000", "11111111111"};
        Paciente p2 = {"22222222222", "Paciente Teste2", "02/02/2000", "22222222222"};
        Paciente p3 = {"33333333333", "Paciente Teste3", "03/03/2000", "33333333333"};

        fseek(pacienteIni, 0, SEEK_END); 

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

        fseek(indicesPacienteIni, 0, SEEK_END); 
        fwrite(indicesPacientes, sizeof(IndexPaciente), 3, indicesPacienteIni);
        
        printf("Pacientes de teste e índices criados.\n");
    }
    fclose(pacienteIni);
    fclose(indicesPacienteIni);

    FILE *consultaIni = fopen("output/consultas.bin", "a+b");
    fseek(consultaIni, 0, SEEK_SET);
    if(ftell(consultaIni) == 0){
        Consulta c1 = {"11111", "11111111111", "01/01/2025", "Sintoma Teste1", "Encaminhamento Teste1"};
        Consulta c2 = {"22222", "22222222222", "02/02/2025", "Sintoma Teste2", "Encaminhamento Teste2"};
        Consulta c3 = {"33333", "33333333333", "03/03/2025", "Sintoma Teste3", "Encaminhamento Teste3"};

        fseek(consultaIni, 0, SEEK_END); 

        fwrite(&c1, sizeof(Consulta), 1, consultaIni);
        fwrite(&c2, sizeof(Consulta), 1, consultaIni);
        fwrite(&c3, sizeof(Consulta), 1, consultaIni);
        printf("Consultas de teste criadas.\n");
    }
    fclose(consultaIni);
}