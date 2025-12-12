//testejoke2

typedef struct Login{
    char usuario[20];
    char senha[10];
} Login;


typedef struct Medico{
    char CRM[6];
    char nome[50];
    char especialidade[20];
    char data_de_nascimento[12];
    float valor_hora_trabalho; 
    char telefone[14];
} Medico;


typedef struct Paciente{
    char CPF[12];
    char nome[30];
    char data_de_nascimento[12]; 
    char telefone[14];
} Paciente;

// alequis: estrutura da consulta 
typedef struct Consulta{
    char crm_medico[6];
    char cpf_paciente[12];
    char data[12];
    char sintomas[100];
    char encaminhamentos[100];
} Consulta;


typedef struct {
    char chave[12]; // CPF ou CRM
    int posicao;    // posição do registro no arquivo binário
} IndexPaciente, IndexMedico;


int BuscarMedicoPorCRM(char crm_alvo[]);
int BuscarPacientePorCPF(char cpf_alvo[]);


//Funçoes Joke
void InserirNovoPaciente();
void AlterarDadosPaciente();
void BuscarPacientePorNome();
void ListaPacientes();


void InserirNovaConsulta(); 
void ListarConsultasPorMedico(); 
void ListarConsultasPorPaciente(); 
void ListarConsultasPorData();

