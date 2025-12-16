#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cabecalho.h" 

void CargaInicial(){
    FILE *loginIni = fopen("output/login.bin", "ab");
    fseek(loginIni, 0, SEEK_END);
    long tamanho = ftell(loginIni);
    if(tamanho == 0){
        Login l1 = {"Teste1", "123"};
        Login l2 = {"Teste2", "1234"};
        Login l3 = {"Teste3", "12345"};

        fwrite(&l1, sizeof(Login), 1, loginIni);
        fwrite(&l2, sizeof(Login), 1, loginIni);
        fwrite(&l3, sizeof(Login), 1, loginIni);
        printf("Logins de teste criados.\n");
    }
    fclose(loginIni);

    FILE *medicoIni = fopen("output/medicos.bin", "ab");
    fseek(medicoIni, 0, SEEK_END);
    if(ftell(medicoIni) == 0){
        Medico m1 = {"11111", "Medico Teste1", "Geral", "01/01/1980", 100.0, "11111111111"};
        Medico m2 = {"22222", "Medico Teste2", "Geral", "02/02/1980", 200.0, "22222222222"};
        Medico m3 = {"33333", "Medico Teste3", "Geral", "03/03/1980", 300.0, "33333333333"};

        fwrite(&m1, sizeof(Medico), 1, medicoIni);
        fwrite(&m2, sizeof(Medico), 1, medicoIni);
        fwrite(&m3, sizeof(Medico), 1, medicoIni);
        printf("Medicos de teste criados.\n");
    }
    fclose(medicoIni);

    FILE *pacienteIni = fopen("output/pacientes.bin", "ab");
    fseek(pacienteIni, 0, SEEK_END);
    if(ftell(pacienteIni) == 0){
        Paciente p1 = {"11111111111", "Paciente Teste1", "01/01/2000", "11111111111"};
        Paciente p2 = {"22222222222", "Paciente Teste2", "02/02/2000", "22222222222"};
        Paciente p3 = {"33333333333", "Paciente Teste3", "03/03/2000", "33333333333"};

        fwrite(&p1, sizeof(Paciente), 1, pacienteIni);
        fwrite(&p2, sizeof(Paciente), 1, pacienteIni);
        fwrite(&p3, sizeof(Paciente), 1, pacienteIni);
        printf("Pacientes de teste criados.\n");
    }
    fclose(pacienteIni);

    FILE *consultaIni = fopen("output/consultas.bin", "ab");
    fseek(consultaIni, 0, SEEK_END);
    if(ftell(consultaIni) == 0){
        Consulta c1 = {"11111", "11111111111", "01/01/2025", "Sintoma Teste1", "Encaminhamento Teste1"};
        Consulta c2 = {"22222", "22222222222", "02/02/2025", "Sintoma Teste2", "Encaminhamento Teste2"};
        Consulta c3 = {"33333", "33333333333", "03/03/2025", "Sintoma Teste3", "Encaminhamento Teste3"};

        fwrite(&c1, sizeof(Consulta), 1, consultaIni);
        fwrite(&c2, sizeof(Consulta), 1, consultaIni);
        fwrite(&c3, sizeof(Consulta), 1, consultaIni);
        printf("Consultas de teste criadas.\n");
    }
    fclose(consultaIni);
}