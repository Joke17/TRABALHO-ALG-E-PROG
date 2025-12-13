#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "cabecalho.h"

int VerificarLogin(char user[], char senha[]){
    FILE *loginArq = fopen("login.bin", "rb");
    fseek(loginArq,0,SEEK_END);
    long bytes = ftell(loginArq);
    int tam = bytes/sizeof(Login);
    Login *logins = (Login *) malloc (bytes);
    rewind(loginArq);

    fread(logins, sizeof(Login), tam, loginArq);
    int verificaLogin = 0;

    for(int i=0; i<tam; i++){
        if(user == logins[i].usuario){
            if(senha == logins[i].senha){
                verificaLogin = 1;
                break;
            }
        }
    }
    free(logins);
    fclose(loginArq);

    return 0;
}