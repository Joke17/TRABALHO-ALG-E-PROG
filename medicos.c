#include <stdio.h>      // Biblioteca padrão de entrada e saída (printf, scanf, arquivos)
#include <stdlib.h>     // Biblioteca para gerenciar memória (malloc, realloc, free)
#include <string.h>     // Biblioteca para manipular textos (strcpy, strcmp)
#include "cabecalho.h"  // Inclui as definições das structs (medico, IndexMedico)

// --- VARIÁVEIS GLOBAIS (Visíveis apenas dentro deste arquivo) ---
// Ponteiro que vai guardar o endereço da nossa lista de índices na memória RAM
IndexMedico *tabelaIndices = NULL; 

// Contador para saber quantos médicos existem atualmente no sistema
int qtdMedicos = 0;    

// Variável de controle para saber o tamanho atual da memória alocada (para saber quando usar realloc)
int capIndices = 0;    


int buscaBinariaMedico(char *crmBusca) {
    
    if (tabelaIndices == NULL) {
        printf("BUSCA: ERRO - Tabela de indices nao inicializada.\n");
        return -1;
    }
    // -------------------------
    
    int inicio = 0;             
    int fim = qtdMedicos - 1;   
    int meio;                   


    printf("\nBUSCA: CRM Alvo: %s\n", crmBusca);
    printf("BUSCA: Qtd Medicos: %d, Fim do Vetor: %d\n", qtdMedicos, fim);
    
    if (qtdMedicos == 0) {
        printf("BUSCA: Vetor vazio, retornando -1.\n");
        return -1;
    }

   while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        
        printf("BUSCA: Comparando com indice %d: [%s]\n", meio, tabelaIndices[meio].chave); 
        
        int cmp = strcmp(crmBusca, tabelaIndices[meio].chave);

        if (cmp == 0) {
            printf("BUSCA: ACHOU!\n");
            return meio; 
        } else if (cmp < 0) {
            
            fim = meio - 1; 
        } else { // (cmp > 0)
           
            inicio = meio + 1; 
        }
    }
    printf("BUSCA: N�o encontrado.\n");
    return -1;
}
// --- FUNÇÃO 1: CARREGAR ÍNDICES ---
// Objetivo: Ler o arquivo de índices do HD e passar para a RAM ao iniciar o programa.
void CarregarIndicesMedicos() {
    // Tenta abrir o arquivo de índices em modo leitura binária ("rb")
    FILE *arqIndex = fopen("output/indices_medicos.bin", "rb");
    
    // Se o arquivo não existir (primeira vez que roda o programa), retorna NULL
    if (arqIndex == NULL) {
        qtdMedicos = 0; // Começamos com zero médicos
        capIndices = 10; // Definimos uma capacidade inicial pequena
        // malloc pede memória ao computador para guardar 10 índices
        tabelaIndices = (IndexMedico *) malloc(capIndices * sizeof(IndexMedico));
        return; // Sai da função pois não tem nada para ler do disco
    }

    // -- Descobrindo quantos índices existem no arquivo --
    fseek(arqIndex, 0, SEEK_END); // Pula o cursor para o final do arquivo
    long tamanhoBytes = ftell(arqIndex); // Pergunta: "quantos bytes tem até aqui?"
    
    // Divide o total de bytes pelo tamanho de um índice para saber a quantidade exata
    qtdMedicos = tamanhoBytes / sizeof(IndexMedico);
    
    // -- Preparando a memória RAM --
    capIndices = qtdMedicos + 10;
tabelaIndices = (IndexMedico *) malloc(capIndices * sizeof(IndexMedico));

// NOVO: CHECAGEM CR�TICA DE ALOCA��O AQUI
if (tabelaIndices == NULL) {
    printf("ERRO FATAL: Falha ao alocar memoria para carregar indices.\n");
    fclose(arqIndex); 
    qtdMedicos = 0; // Se falhou, o vetor est� vazio
    return;
}
// --------------------------------------------------------

// -- Lendo os dados --
fseek(arqIndex, 0, SEEK_SET);
fread(tabelaIndices, sizeof(IndexMedico), qtdMedicos, arqIndex);
    
    fclose(arqIndex); // Fecha o arquivo pois já está tudo na memória
    printf("Sistema: %d medicos carregados na memoria.\n", qtdMedicos);
}

// --- FUNÇÃO 2: SALVAR ÍNDICES ---
// Objetivo: Gravar o que está na RAM de volta no HD antes de fechar o programa.
void SalvarIndicesMedicos() {
    // Se a tabela está vazia (NULL), não faz nada
    if (tabelaIndices == NULL) return;

    // Abre o arquivo em modo de escrita binária ("wb"). 
    // O "w" zera o arquivo e escreve tudo novo por cima.
    FILE *arqIndex = fopen("output/indices_medicos.bin", "wb");
    
    if (arqIndex == NULL) {
        printf("Erro grave: Nao foi possivel salvar os indices!\n");
        return;
    }

    // Escreve o conteúdo do vetor tabelaIndices inteiro no arquivo
    fwrite(tabelaIndices, sizeof(IndexMedico), qtdMedicos, arqIndex);
    
    fclose(arqIndex); // Fecha e salva as alterações no disco
    
    // Limpeza final: libera a memória RAM que pedimos emprestada
    free(tabelaIndices);
    tabelaIndices = NULL; // Zera o ponteiro por segurança
}

// --- FUNÇÃO 3: INSERIR NOVO MÉDICO ---
// Objetivo: Cadastrar dados no arquivo e atualizar o índice de forma ordenada.
void InserirNovoMedico() {
    Medico m;
    int c; // Variável auxiliar para limpeza de buffer quando necessário

    printf("\n--- CADASTRO DE MEDICO ---\n");
    
    // --- 1. CRM ---
    printf("Digite o CRM: ");
    scanf("%s", m.CRM); // Use scanf para o CRM (simples, sem espaços)
    // LIMPEZA OBRIGATÓRIA DO BUFFER APÓS SCANF
    while ((c = getchar()) != '\n' && c != EOF);

    // Verifica duplicidade
    if (buscaBinariaMedico(m.CRM) != -1) {
        printf("Erro: Ja existe um medico com este CRM!\n");
        return;
    }

    // --- 2. NOME ---
    printf("Nome: ");
    // Como limpamos o buffer após o CRM, o fgets vai funcionar perfeitamente
    fgets(m.nome, 50, stdin); 
    m.nome[strcspn(m.nome, "\n")] = 0; 

    // --- 3. ESPECIALIDADE ---
    printf("Especialidade: ");
    fgets(m.especialidade, 20, stdin);
    m.especialidade[strcspn(m.especialidade, "\n")] = 0;

    // --- 4. VALOR ---
    printf("Valor Hora (ex: 100.50): ");
    scanf("%f", &m.valor_hora_trabalho);
    // LIMPEZA APÓS LER NÚMERO
    while ((c = getchar()) != '\n' && c != EOF);

    // --- GRAVAÇÃO (Igual ao seu código) ---
    FILE *arqDados = fopen("output/medicos.bin", "ab");
    if (arqDados == NULL) { printf("Erro ao abrir medicos.bin!\n"); return; }

    fseek(arqDados, 0, SEEK_END);
    long posicaoNoDisco = ftell(arqDados);
    fwrite(&m, sizeof(Medico), 1, arqDados);
    fclose(arqDados);

    // --- ATUALIZAÇÃO ÍNDICE (Igual ao seu código) ---
    if (qtdMedicos >= capIndices) {
        capIndices += 10;
        tabelaIndices = (IndexMedico *) realloc(tabelaIndices, capIndices * sizeof(IndexMedico));
    }

    int i = qtdMedicos - 1;
    while (i >= 0 && strcmp(m.CRM, tabelaIndices[i].chave) < 0) {
        tabelaIndices[i + 1] = tabelaIndices[i]; 
        i--;
    }

    strcpy(tabelaIndices[i + 1].chave, m.CRM);
    tabelaIndices[i + 1].posicao = posicaoNoDisco;
    qtdMedicos++;

    printf("Medico cadastrado com sucesso!\n");
}
// --- FUNÇÃO EXTRA: LISTAR TUDO ---
// Objetivo: Mostrar que a ligação Índice -> Dados está funcionando
void ListarMedicos() {
    if (qtdMedicos == 0) {
        printf("Nenhum medico cadastrado.\n");
        return;
    }

    // Abre o arquivo de dados apenas para leitura
    FILE *arqDados = fopen("output/medicos.bin", "rb");
    if (!arqDados) { printf("Erro ao ler dados.\n"); return; }

    Medico m;
    printf("\n--- LISTA DE MEDICOS (Ordenada por CRM) ---\n");
    
    // Percorre o vetor de índices (que já mantivemos ordenado na RAM)
    for (int i = 0; i < qtdMedicos; i++) {
        // A MÁGICA: Pula direto para o byte onde os dados desse médico estão gravados
        fseek(arqDados, tabelaIndices[i].posicao, SEEK_SET);
        
        // Lê os dados do médico nessa posição
        fread(&m, sizeof(Medico), 1, arqDados);
        
        // Mostra na tela
        printf("CRM: %s | Nome: %s | Esp: %s\n", m.CRM, m.nome, m.especialidade);
    }

}

    // --- FUNÇÃO 4: EDITAR MÉDICO (Update) ---
// Objetivo: Alterar dados de um médico já existente (menos o CRM).
void EditarMedico() {
    char crmBusca[20];
    int indice, c;
    FILE *arqDados;
    Medico m;
    long posicao;

    printf("\n--- EDITAR MEDICO ---\n");
    printf("Digite o CRM do medico que deseja alterar: ");
    scanf("%s", crmBusca);
    // LIMPA BUFFER IMEDIATAMENTE APÓS SCANF
    while ((c = getchar()) != '\n' && c != EOF);

    indice = buscaBinariaMedico(crmBusca);
    if (indice == -1) {
        printf("Erro: Medico nao encontrado!\n");
        return;
    }

    arqDados = fopen("output/medicos.bin", "r+b"); 
    if (arqDados == NULL) { printf("Erro no arquivo.\n"); return; }

    posicao = tabelaIndices[indice].posicao;
    fseek(arqDados, posicao, SEEK_SET);
    fread(&m, sizeof(Medico), 1, arqDados);

    printf("\n--- Dados Atuais: %s | %s | %.2f ---\n", m.nome, m.especialidade, m.valor_hora_trabalho);
    printf("AVISO: O CRM nao pode ser alterado.\n");
    
    // --- LEITURA DOS NOVOS DADOS ---
    // Como o buffer foi limpo lá em cima, o fgets não vai pular
    printf("Novo Nome: ");
    fgets(m.nome, 50, stdin);
    m.nome[strcspn(m.nome, "\n")] = 0;

    printf("Nova Especialidade: ");
    fgets(m.especialidade, 20, stdin);
    m.especialidade[strcspn(m.especialidade, "\n")] = 0;

    printf("Novo Valor Hora: ");
    scanf("%f", &m.valor_hora_trabalho);
    // LIMPA BUFFER FINAL (Para não atrapalhar o menu depois)
    while ((c = getchar()) != '\n' && c != EOF);

    fseek(arqDados, posicao, SEEK_SET); 
    fwrite(&m, sizeof(Medico), 1, arqDados);
    fclose(arqDados);
    
    printf("Dados atualizados!\n");
}
// --- FUNÇÃO 5: EXCLUIR MÉDICO (Delete) ---
// Objetivo: Apagar o médico do sistema.
// Estratégia: Exclusão Lógica. Apagamos apenas o ÍNDICE da memória.
void ExcluirMedico() {
    char crmBusca[20];
    int indice, confirmacao, i, c;

    printf("\n--- EXCLUIR MEDICO ---\n");
    printf("Digite o CRM do medico a ser excluido: ");
    scanf("%s", crmBusca);
    // LIMPA BUFFER
    while ((c = getchar()) != '\n' && c != EOF);

    indice = buscaBinariaMedico(crmBusca);

    if (indice == -1) {
        printf("Erro: Medico nao encontrado!\n");
        return;
    }

    printf("Tem certeza que deseja excluir o CRM %s? (1-Sim / 0-Nao): ", crmBusca);
    scanf("%d", &confirmacao);
    // --- CORREÇÃO: LIMPAR O BUFFER APÓS O NÚMERO ---
    // Se não limpar aqui, o 'Enter' sobra e pula o menu principal depois
    while ((c = getchar()) != '\n' && c != EOF); 

    if (confirmacao != 1) {
        printf("Operacao cancelada.\n");
        return;
    }

    // Shift Left (Remove do índice)
    for (i = indice; i < qtdMedicos - 1; i++) {
        tabelaIndices[i] = tabelaIndices[i + 1];
    }

    qtdMedicos--; 
    SalvarIndicesMedicos(); // Salva a alteração no disco imediatamente
    
    printf("Medico excluido com sucesso!\n");
}

// --- FUN��O EXTRA: DEBUG ---
// Objetivo: Mostrar os índices carregados em memória
void DebugListarIndices() {
    printf("\n--- DEBUG: INDICES DE MEDICOS CARREGADOS ---\n");
    if (qtdMedicos == 0) {
        printf("Nenhum indice carregado.\n");
        return;
    }
    for (int i = 0; i < qtdMedicos; i++) {
        printf("Posicao %d: CRM [%s]\n", i, tabelaIndices[i].chave);
    }

    printf("------------------------------------------\n");
}
// --- FUNÇÃO 6: BUSCAR MÉDICO POR NOME (Pesquisa Sequencial) ---
void BuscarMedicoPorNome() {
    char nomeBusca[50];
    int i, c;
    int encontrou = 0; // Contador de resultados
    Medico m;
    FILE *arqDados;

    // 1. Entrada de dados
    printf("\n--- BUSCA POR NOME (Parcial) ---\n");
    printf("Digite parte do nome: ");
    
    // Limpeza de buffer preventiva antes de ler string
    // (Caso venha de um menu que deixou sujeira)
    // Se o seu menu já limpa, pode tirar o setbuf, mas mal não faz.
    setbuf(stdin, NULL); 
    
    fgets(nomeBusca, 50, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0; // Remove o Enter (\n)

    // Se o usuário der Enter sem digitar nada, sai
    if (strlen(nomeBusca) == 0) return;

    // 2. Abrir arquivo para leitura
    arqDados = fopen("output/medicos.bin", "rb");
    if (arqDados == NULL) {
        printf("Erro ao ler banco de dados.\n");
        return;
    }

    printf("\nResultados para '%s':\n", nomeBusca);
    printf("--------------------------------------------------\n");

    // 3. Loop: Percorre TODOS os médicos ativos no índice
    // (Usamos o índice para garantir que não mostremos médicos excluídos)
    for (i = 0; i < qtdMedicos; i++) {
        
        // Vai no HD buscar os dados completos deste médico
        fseek(arqDados, tabelaIndices[i].posicao, SEEK_SET);
        fread(&m, sizeof(Medico), 1, arqDados);

        // 4. A Mágica: strstr (String String)
        // Verifica se 'nomeBusca' existe DENTRO de 'm.nome'
        // Retorna um ponteiro se achar, ou NULL se não achar.
        if (strstr(m.nome, nomeBusca) != NULL) {
            printf("CRM: %-6s | Nome: %-25s | Esp: %s\n", m.CRM, m.nome, m.especialidade);
            encontrou++;
        }
    }

    printf("--------------------------------------------------\n");
    if (encontrou == 0) {
        printf("Nenhum medico encontrado com esse nome.\n");
    } else {
        printf("Total encontrados: %d\n", encontrou);
    }

    fclose(arqDados);
}