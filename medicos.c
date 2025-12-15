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

// --- FUNÇÃO AUXILIAR: BUSCA BINÁRIA ---
// Objetivo: Achar um médico muito rápido sem ler tudo.
// Retorna: A posição no vetor (0, 1, 2...) se achar, ou -1 se não achar.
int buscaBinariaMedico(char *crmBusca) {
    int inicio = 0;             // Começa no primeiro elemento
    int fim = qtdMedicos - 1;   // Termina no último elemento válido
    int meio;                   // Variável para guardar a posição central

    // Enquanto o início não ultrapassar o fim, continuamos procurando
    while (inicio <= fim) {
        meio = (inicio + fim) / 2; // Calcula o índice bem no meio da lista
        
        // strcmp compara duas strings:
        // Retorna 0 se forem iguais
        // Retorna < 0 se a primeira vier antes no alfabeto
        // Retorna > 0 se a primeira vier depois no alfabeto
        int cmp = strcmp(crmBusca, tabelaIndices[meio].chave);

        if (cmp == 0) {
            return meio; // ACHOU! Retorna a posição onde está.
        } else if (cmp < 0) {
            fim = meio - 1; // Se é menor, descarta a metade da direita e foca na esquerda.
        } else {
            inicio = meio + 1; // Se é maior, descarta a metade da esquerda e foca na direita.
        }
    }
    return -1; // Se saiu do loop, é porque não encontrou nada.
}

// --- FUNÇÃO 1: CARREGAR ÍNDICES ---
// Objetivo: Ler o arquivo de índices do HD e passar para a RAM ao iniciar o programa.
void CarregarIndicesMedicos() {
    // Tenta abrir o arquivo de índices em modo leitura binária ("rb")
    FILE *arqIndex = fopen("indices_medicos.bin", "rb");
    
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
    capIndices = qtdMedicos + 10; // Aloca o necessário + uma sobra de segurança
    tabelaIndices = (IndexMedico *) malloc(capIndices * sizeof(IndexMedico));

    // -- Lendo os dados --
    fseek(arqIndex, 0, SEEK_SET); // Volta o cursor para o início do arquivo
    // Copia tudo do arquivo (HD) para o vetor tabelaIndices (RAM) de uma vez só
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
    FILE *arqIndex = fopen("indices_medicos.bin", "wb");
    
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
    Medico m; // Cria uma variável temporária para receber os dados
    
   // --- 1. LEITURA E LIMPEZA DO CRM ---
printf("\n--- CADASTRO DE MEDICO ---\n");
printf("Digite o CRM: ");
// Usa fgets e garante que a string n�o tem mais que 5 caracteres + \0
if (fgets(m.CRM, sizeof(m.CRM), stdin) == NULL) return; 
m.CRM[strcspn(m.CRM, "\n")] = 0; // Remove o '\n'

// --- NOVO PASSO: LIMPEZA MANUAL AP�S FGETS DE CAMPO PEQUENO ---
// Se o usu�rio digitou mais caracteres do que o CRM[6] suporta, 
// os excessos ficam no buffer. Isso os remove para o pr�ximo fgets.
int c;
while ((c = getchar()) != '\n' && c != EOF);
// -----------------------------------------------------------------

// Antes de continuar, verifica se esse CRM j� existe
if (buscaBinariaMedico(m.CRM) != -1) {
    printf("Erro: Ja existe um medico com este CRM!\n");
    return; // Cancela o cadastro
}

// --- 2. LEITURA DO NOME (DEVE FUNCIONAR AGORA) ---
printf("Nome: ");
fgets(m.nome, 50, stdin); // L� o nome com espa�os
m.nome[strcspn(m.nome, "\n")] = 0; // Truque para remover o \n do final da string

// --- 3. LEITURA DA ESPECIALIDADE ---
printf("Especialidade: ");
fgets(m.especialidade, 20, stdin);
m.especialidade[strcspn(m.especialidade, "\n")] = 0;

    printf("Valor Hora (ex: 100.50): ");
    scanf("%f", &m.valor_hora_trabalho); // Lê o float
    getchar(); // Limpa buffer novamente

    // --- Passo 2: Gravar os DADOS no arquivo (HDD) ---
    // Abre o arquivo de DADOS em modo append ("ab"), adiciona ao final
    FILE *arqDados = fopen("medicos.bin", "ab");
    if (arqDados == NULL) {
        printf("Erro ao abrir medicos.bin!\n");
        return;
    }

    // ftell diz onde o cursor está. Como abrimos com "append", ele está no fim.
    // Guardamos essa posição pois ela será usada no índice!
    fseek(arqDados, 0, SEEK_END);
    long posicaoNoDisco = ftell(arqDados);

    // Escreve a struct do médico no arquivo de dados
    fwrite(&m, sizeof(Medico), 1, arqDados);
    fclose(arqDados);

    // --- Passo 3: Atualizar o ÍNDICE na memória (RAM) ---
    
    // Verifica se a memória está cheia. Se estiver, aumenta o tamanho.
    if (qtdMedicos >= capIndices) {
        capIndices += 10; // Aumenta a capacidade em 10 posições
        // realloc tenta aumentar o bloco de memória sem perder os dados que já tem lá
        tabelaIndices = (IndexMedico *) realloc(tabelaIndices, capIndices * sizeof(IndexMedico));
        printf("DEBUG: Memoria aumentada para caber %d indices.\n", capIndices);
    }

    // --- Lógica de INSERÇÃO ORDENADA (Sort) ---
    // Precisamos manter o vetor ordenado alfabeticamente pelo CRM para a busca binária funcionar.
    // Começamos do último elemento e vamos voltando.
    int i = qtdMedicos - 1;
    
    // Enquanto o CRM que estamos inserindo for "menor" (alfabeticamente) que o atual...
    while (i >= 0 && strcmp(m.CRM, tabelaIndices[i].chave) < 0) {
        // ...nós empurramos o índice atual uma casa para a direita
        tabelaIndices[i + 1] = tabelaIndices[i]; 
        i--;
    }

    // Quando o loop para, achamos o "buraco" correto para inserir o novo índice
    strcpy(tabelaIndices[i + 1].chave, m.CRM); // Copia o CRM para o índice
    tabelaIndices[i + 1].posicao = posicaoNoDisco; // Salva onde os dados estão no disco
    
    qtdMedicos++; // Incrementa o contador total de médicos

    printf("Medico cadastrado e indexado com sucesso!\n");
}

// --- FUNÇÃO EXTRA: LISTAR TUDO ---
// Objetivo: Mostrar que a ligação Índice -> Dados está funcionando
void ListarMedicos() {
    if (qtdMedicos == 0) {
        printf("Nenhum medico cadastrado.\n");
        return;
    }

    // Abre o arquivo de dados apenas para leitura
    FILE *arqDados = fopen("medicos.bin", "rb");
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

    // --- FUNÇÃO 4: EDITAR MÉDICO (Update) ---
// Objetivo: Alterar dados de um médico já existente (menos o CRM).
void EditarMedico() {
    // 1. DECLARAÇÃO DE VARIÁVEIS NO TOPO (Padrão C estrito)
    char crmBusca[20];  // Variável para guardar o CRM que o usuário digitar
    int indice;         // Vai guardar a posição do médico no vetor da RAM
    FILE *arqDados;     // Ponteiro para manipular o arquivo físico
    Medico m;           // Struct temporária para carregar os dados
    long posicao;       // Vai guardar o endereço (byte offset) do dado no HD

    // 2. INTERAÇÃO COM USUÁRIO
    printf("\n--- EDITAR MEDICO ---\n");
    printf("Digite o CRM do medico que deseja alterar: ");
    scanf("%s", crmBusca); // Lê o CRM
    getchar(); // Limpa o "Enter" que sobrou no buffer do teclado

    // 3. BUSCA NA MEMÓRIA RAM
    // Chama a busca binária para ver se esse médico existe no índice
    indice = buscaBinariaMedico(crmBusca);

    // Se a busca retornar -1, significa que não achou
    if (indice == -1) {
        printf("Erro: Medico nao encontrado!\n");
        return; // Sai da função
    }

    // 4. PREPARAÇÃO DO ARQUIVO
    // Abre o arquivo "medicos.bin" em modo "r+b"
    // "r+" = Leitura e Escrita (Update). Permite alterar dados sem apagar o arquivo todo.
    arqDados = fopen("medicos.bin", "r+b"); 
    
    // Verifica se o arquivo abriu corretamente
    if (arqDados == NULL) {
        printf("Erro ao abrir arquivo de dados.\n");
        return;
    }

    // 5. RECUPERAÇÃO DOS DADOS ANTIGOS
    // Pega a posição exata (onde o médico começa) guardada na struct do índice
    posicao = tabelaIndices[indice].posicao;

    // fseek: "Teletransporta" a cabeça de leitura para o byte exato
    fseek(arqDados, posicao, SEEK_SET);
    
    // fread: Lê os dados do disco e joga na variável 'm'
    fread(&m, sizeof(Medico), 1, arqDados);

    // Mostra os dados atuais para o usuário conferir
    printf("\n--- Dados Atuais ---\n");
    printf("Nome: %s | Especialidade: %s | Valor: %.2f\n", m.nome, m.especialidade, m.valor_hora_trabalho);
    printf("---------------------------------------------\n");
    printf("AVISO: O CRM nao pode ser alterado (Chave Primaria).\n");
    
    // 6. COLETA DOS NOVOS DADOS
    printf("Novo Nome: ");
    fgets(m.nome, 50, stdin); // Lê o nome permitindo espaços
    m.nome[strcspn(m.nome, "\n")] = 0; // Truque para remover o \n do final da string

    printf("Nova Especialidade: ");
    fgets(m.especialidade, 20, stdin);
    m.especialidade[strcspn(m.especialidade, "\n")] = 0; // Remove o \n

    printf("Novo Valor Hora: ");
    scanf("%f", &m.valor_hora_trabalho); // Lê o novo valor float
    getchar(); // Limpa o buffer novamente

    // 7. GRAVAÇÃO (SOBRESCRITA)
    // fseek: É OBRIGATÓRIO chamar fseek entre uma leitura e uma escrita
    // Voltamos para o mesmo byte de início para gravar EXATAMENTE em cima do velho
    fseek(arqDados, posicao, SEEK_SET); 
    
    // fwrite: Escreve a struct 'm' atualizada no arquivo
    fwrite(&m, sizeof(Medico), 1, arqDados);
    
    // Fecha o arquivo para salvar as alterações no disco
    fclose(arqDados);
    
    printf("Dados do medico atualizados com sucesso!\n");
}

// --- FUNÇÃO 5: EXCLUIR MÉDICO (Delete) ---
// Objetivo: Apagar o médico do sistema.
// Estratégia: Exclusão Lógica. Apagamos apenas o ÍNDICE da memória.
void ExcluirMedico() {
    // 1. DECLARAÇÃO DE VARIÁVEIS NO TOPO
    char crmBusca[20]; // CRM a ser excluído
    int indice;        // Posição no vetor
    int confirmacao;   // Variável para sim/não
    int i;             // Contador para o loop for

    // 2. BUSCA DO ALVO
    printf("\n--- EXCLUIR MEDICO ---\n");
    printf("Digite o CRM do medico a ser excluido: ");
    scanf("%s", crmBusca);
    getchar(); // Limpa buffer

    // Procura onde ele está no vetor de índices
    indice = buscaBinariaMedico(crmBusca);

    // Validação se existe
    if (indice == -1) {
        printf("Erro: Medico nao encontrado!\n");
        return;
    }

    // 3. SEGURANÇA (Confirmação do usuário)
    printf("Tem certeza que deseja excluir o CRM %s? (1-Sim / 0-Nao): ", crmBusca);
    scanf("%d", &confirmacao);

    // Se digitar qualquer coisa diferente de 1, cancela
    if (confirmacao != 1) {
        printf("Operacao cancelada.\n");
        return;
    }

    // 4. REMOÇÃO DO ÍNDICE (Shift Left)
    // Como o vetor não pode ter buracos, copiamos os elementos da frente para trás.
    // Exemplo: Se excluir o índice 2, o 3 vira o 2, o 4 vira o 3, etc.
    for (i = indice; i < qtdMedicos - 1; i++) {
        tabelaIndices[i] = tabelaIndices[i + 1]; // O índice atual é sobrescrito pelo próximo
    }

    // 5. ATUALIZAÇÃO DO CONTADOR
    // Diminuímos a contagem total. O último elemento fica duplicado lá no fundo,
    // mas o sistema ignora ele porque qtdMedicos diminuiu.
    qtdMedicos--; 

    // Aviso final: A exclusão só vai pro arquivo quando chamar "SalvarIndicesMedicos"
    printf("Medico excluido com sucesso! (Sera efetivado ao sair do programa)\n");
}
    fclose(arqDados);
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