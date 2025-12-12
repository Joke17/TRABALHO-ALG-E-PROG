

typedef struct {
    char usuario[20];
    char senha[10];
} login;


typedef struct {
    char CRM[6];
    char nome[50];
    char especialidade[20];
    char data_de_nascimento[12];
    float valor_hora_trabalho; 
    char telefone[14];
} medico;


typedef struct {
    char CPF[12];
    char nome[30];
    char data_de_nascimento[12]; 
    char telefone[14];
} paciente;

// alequis: estrutura da consulta 
typedef struct {
    char crm_medico[6];
    char cpf_paciente[12];
    char data[12];
    char sintomas[100];
    char encaminhamentos[100];
} consulta;


typedef struct {
    char chave[12]; // CPF ou CRM
    int posicao;    // posição do registro no arquivo binário
} indexPaciente, indexMedico;


int buscarMedicoPorCRM(char crm_alvo[]);
int buscarPacientePorCPF(char cpf_alvo[]);


void InserirNovaConsulta(); 
void ListarConsultasPorMedico(); 
void ListarConsultasPorPaciente(); 
void ListarConsultasPorData();

