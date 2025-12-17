#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cabecalho.h"

IndexMedico *listaIndices = NULL;
int totalMedicos = 0;
int capacidade = 0;

// --- FUNCOES AUXILIARES ---
void limpaBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// remove o \n do final da string lida pelo fgets
void removeEnter(char *str) {
    size_t tam = strlen(str);
    if (tam > 0 && str[tam - 1] == '\n') {
        str[tam - 1] = '\0';
    }
}

// --- BUSCA BINARIA ---
int buscaBinariaMedico(char *crm) {
    if (listaIndices == NULL || totalMedicos == 0) return -1;
    
    int inicio = 0;
    int fim = totalMedicos - 1;
    int meio;
    int cmp;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        cmp = strcmp(crm, listaIndices[meio].chave);

        if (cmp == 0) {
            return meio; // achou
        } else if (cmp < 0) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }
    return -1; // Nao achou
}

// --- CARREGAR ---
void CarregarIndicesMedicos() {
    FILE *fp = fopen("output/indices_medicos.bin", "rb");
    long tamBytes;

    if (fp == NULL) {
        // arquivo nao existe, cria lista vazia
        totalMedicos = 0;
        capacidade = 10;
        listaIndices = (IndexMedico *) malloc(capacidade * sizeof(IndexMedico));
        return;
    }

    // Calcula tamanho do arquivo
    fseek(fp, 0, SEEK_END);
    tamBytes = ftell(fp);
    rewind(fp); // volta pro inicio

    totalMedicos = tamBytes / sizeof(IndexMedico);
    capacidade = totalMedicos + 10;
    
    listaIndices = (IndexMedico *) malloc(capacidade * sizeof(IndexMedico));

    if (listaIndices == NULL) {
        printf("Erro fatal: Falha de memoria ao carregar indices.\n");
        fclose(fp);
        exit(1); // Fecha o programa se der erro de memoria
    }

    fread(listaIndices, sizeof(IndexMedico), totalMedicos, fp);
    fclose(fp);
    
    printf("Sistema: %d medicos carregados na memoria.\n", totalMedicos);
}

// --- SALVAR ---
void SalvarIndicesMedicos() {
    if (listaIndices == NULL) return;

    FILE *fp = fopen("output/indices_medicos.bin", "wb");
    if (fp == NULL) {
        printf("Erro grave: Nao foi possivel salvar os indices!\n");
        return;
    }

    fwrite(listaIndices, sizeof(IndexMedico), totalMedicos, fp);
    fclose(fp);
    
    // Libera memoria ao sair
    free(listaIndices);
    listaIndices = NULL;
}

// --- INSERIR ---
void InserirNovoMedico() {
    Medico aux;
    FILE *fp;
    long pos;
    int i;

    printf("\n--- CADASTRO DE MEDICO ---\n");
    
    printf("Digite o CRM: ");
    scanf("%s", aux.CRM);
    limpaBuffer();

    if (buscaBinariaMedico(aux.CRM) != -1) {
        printf("Erro: Ja existe um medico com este CRM!\n");
        return;
    }

    printf("Nome: ");
    fgets(aux.nome, 50, stdin);
    removeEnter(aux.nome);

    printf("Especialidade: ");
    fgets(aux.especialidade, 20, stdin);
    removeEnter(aux.especialidade);

    printf("Valor Hora (ex: 100.50): ");
    scanf("%f", &aux.valor_hora_trabalho);
    limpaBuffer();

    // grava no arquivo de dados
    fp = fopen("output/medicos.bin", "ab");
    if (fp == NULL) {
        printf("Erro ao abrir medicos.bin!\n");
        return;
    }

    fseek(fp, 0, SEEK_END);
    pos = ftell(fp); // guarda posicao
    fwrite(&aux, sizeof(Medico), 1, fp);
    fclose(fp);

    // Atualiza indice na RAM
    if (totalMedicos >= capacidade) {
        capacidade += 10;
        listaIndices = (IndexMedico *) realloc(listaIndices, capacidade * sizeof(IndexMedico));
    }

    i = totalMedicos - 1;
    while (i >= 0 && strcmp(aux.CRM, listaIndices[i].chave) < 0) {
        listaIndices[i + 1] = listaIndices[i]; 
        i--;
    }

    strcpy(listaIndices[i + 1].chave, aux.CRM);
    listaIndices[i + 1].posicao = pos;
    totalMedicos++;

    printf("Medico cadastrado com sucesso!\n");
}

// --- LISTAR ---
void ListarMedicos() {
    FILE *fp;
    Medico m;
    int i;

    if (totalMedicos == 0) {
        printf("Nenhum medico cadastrado.\n");
        return;
    }

    fp = fopen("output/medicos.bin", "rb");
    if (!fp) {
        printf("Erro ao ler dados.\n");
        return;
    }

    printf("\n--- LISTA DE MEDICOS ---\n");
    for (i = 0; i < totalMedicos; i++) {
        fseek(fp, listaIndices[i].posicao, SEEK_SET);
        fread(&m, sizeof(Medico), 1, fp);
        printf("CRM: %s | Nome: %s | Esp: %s\n", m.CRM, m.nome, m.especialidade);
    }
    printf("-------------------------\n");
    fclose(fp);
}

// --- EDITAR ---
void EditarMedico() {
    char busca[20];
    int idx;
    FILE *fp;
    Medico m;
    long pos;

    printf("\n--- EDITAR MEDICO ---\n");
    printf("Digite o CRM do medico que deseja alterar: ");
    scanf("%s", busca);
    limpaBuffer();

    idx = buscaBinariaMedico(busca);
    if (idx == -1) {
        printf("Erro: Medico nao encontrado!\n");
        return;
    }

    pos = listaIndices[idx].posicao;

    fp = fopen("output/medicos.bin", "r+b"); 
    if (fp == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    fseek(fp, pos, SEEK_SET);
    fread(&m, sizeof(Medico), 1, fp);

    printf("\n--- Dados Atuais ---\n");
    printf("Nome: %s | Valor: %.2f\n", m.nome, m.valor_hora_trabalho);
    printf("AVISO: O CRM nao pode ser alterado.\n");
    
    printf("Novo Nome: ");
    fgets(m.nome, 50, stdin);
    removeEnter(m.nome);

    printf("Nova Especialidade: ");
    fgets(m.especialidade, 20, stdin);
    removeEnter(m.especialidade);

    printf("Novo Valor Hora: ");
    scanf("%f", &m.valor_hora_trabalho);
    limpaBuffer();
    
    fseek(fp, pos, SEEK_SET); 
    fwrite(&m, sizeof(Medico), 1, fp);
    fclose(fp);
    
    printf("Dados do medico atualizados com sucesso!\n");
}

// --- EXCLUIR ---
void ExcluirMedico() {
    char busca[20];
    int idx, op, i;

    printf("\n--- EXCLUIR MEDICO ---\n");
    printf("Digite o CRM do medico a ser excluido: ");
    scanf("%s", busca);
    limpaBuffer();
    
    idx = buscaBinariaMedico(busca);
    if (idx == -1) {
        printf("Erro: Medico nao encontrado!\n");
        return;
    }
    
    printf("Tem certeza que deseja excluir o CRM %s? (1-Sim / 0-Nao): ", busca);
    scanf("%d", &op);
    limpaBuffer(); 
    
    if (op != 1) {
        printf("Operacao cancelada.\n");
        return;
    }

    // Remove do vetor puxando os da frente pra tras
    for (i = idx; i < totalMedicos - 1; i++) {
        listaIndices[i] = listaIndices[i + 1];
    }

    totalMedicos--; 
    SalvarIndicesMedicos();
    
    printf("Medico excluido com sucesso!\n");
}

// --- BUSCAR POR NOME ---
void BuscarMedicoPorNome() {
    char nome[50];
    int i, cont = 0;
    Medico m;
    FILE *fp;

    printf("\n--- BUSCA POR NOME ---\n");
    printf("Digite parte do nome: ");
    limpaBuffer();
    
    fgets(nome, 50, stdin);
    removeEnter(nome);

    if (strlen(nome) == 0) return;

    fp = fopen("output/medicos.bin", "rb");
    if (fp == NULL) {
        printf("Erro: Banco de dados vazio ou inexistente.\n");
        return;
    }

    printf("\nResultados para '%s':\n", nome);
    printf("--------------------------------------------------\n");

    for (i = 0; i < totalMedicos; i++) {
        fseek(fp, listaIndices[i].posicao, SEEK_SET);
        fread(&m, sizeof(Medico), 1, fp);

        if (strstr(m.nome, nome) != NULL) {
            printf("CRM: %-6s | Nome: %-25s | Esp: %s\n", m.CRM, m.nome, m.especialidade);
            cont++;
        }
    }
    printf("--------------------------------------------------\n");

    if (cont == 0) printf("Nenhum medico encontrado com esse nome.\n");
    else printf("Total encontrados: %d\n", cont);
    
    fclose(fp);
}

void ListarMedicosPorEspecialidade() {
    FILE *fp;
    Medico m;
    int i;
    char especialidadeBusca[20];
    int encontrou = 0;

    if (totalMedicos == 0) {
        printf("Nenhum medico cadastrado.\n");
        return;
    }

    printf("\n--- LISTAR MEDICOS POR ESPECIALIDADE ---\n");
    printf("Digite a especialidade: ");
    limpaBuffer();
    fgets(especialidadeBusca, 20, stdin);
    removeEnter(especialidadeBusca);

    fp = fopen("output/medicos.bin", "rb");
    if (!fp) {
        printf("Erro ao ler dados.\n");
        return;
    }

    printf("\nMedicos com especialidade '%s':\n", especialidadeBusca);
    printf("--------------------------------------------------\n");

    for (i = 0; i < totalMedicos; i++) {
        fseek(fp, listaIndices[i].posicao, SEEK_SET);
        fread(&m, sizeof(Medico), 1, fp);

        if (strcmp(m.especialidade, especialidadeBusca) == 0) {
            printf("CRM: %-6s | Nome: %-25s\n", m.CRM, m.nome);
            encontrou++;
        }
    }

    printf("--------------------------------------------------\n");
    if (encontrou == 0) {
        printf("Nenhum medico encontrado com essa especialidade.\n");
    } else {
        printf("Total encontrados: %d\n", encontrou);
    }

    fclose(fp);
}