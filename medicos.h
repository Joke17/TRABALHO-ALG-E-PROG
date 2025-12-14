#ifndef MEDICOS_H
#define MEDICOS_H

// Protótipos das funções (O "Cardápio" para a Main)

void CarregarIndicesMedicos();
void SalvarIndicesMedicos();
void InserirNovoMedico();
void ListarMedicos();

// Se você precisar usar a busca em outros arquivos (ex: consultas), deixe esta aqui.
// Caso contrário, é opcional.
int buscaBinariaMedico(char *crmBusca);

#endif