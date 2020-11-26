#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

//Declaração dos Procedimentos e Funções a serem utilizados 
void menuPrincipal();  
void cadastro(); 
void telaLogin();  
void consulta();

//Declaração das Estruturas a serem utilizadas 
//Cliente
typedef struct enderecoStruct {
  char rua[40];
  char bairro[30];
  char numero[6];
  char cep[8];
  char cidade[20];
  char estado[20];
}
Endereco;

typedef struct CadastroPessoaStruct {
  char nome[40];
  char reg[12];
  char rg[10];
  char telefone[11];
  char especialidade[20];
  char data[8];
  char hora[5];
  Endereco end;
}
Pessoa;


//Declaração das variáveis 
//Cliente
int input = 0;
int qtdClientes;
int tamClientes;
Pessoa * clientes;
FILE * arquivo;
char clientes_dir[] = "Clientes.bin";
Pessoa * medico;

//Declaração dos Procedimentos e Funções a serem utilizados 
void menuPrincipal();
void cadastro();
void menuClientes();
void removerQuebraLinha();
Pessoa receberCliente();
Endereco receberEndereco();
void inserirCliente();
Pessoa * buscarCliente();
int removerCliente();
void listarClientes();
//Consulta receberConsulta();

//Declaração das Estruturas a serem utilizadas
//Medico
typedef struct enderecoMedStruct {
  char rua[40];
  char bairro[30];
  char numero[6];
  char cep[8];
  char cidade[20];
  char estado[20];
}
EnderecoMed;

typedef struct CadastroMedStruct {
  char nome[40];
  char reg[12];
  char rg[10];
  char telefone[11];
  EnderecoMed endMed;
}
Med;

//Declaração das variáveis 
//Medico
int qtdMedicos;
int tamMedicos;
Med * medicos;
FILE * arquivo;
char medicos_dir[] = "Medicos.bin";

//Declaração dos Procedimentos e Funções a serem utilizados 
void menuPrincipal();
void cadastro();
void menuMedico();
void removerQuebraLinha();
Med  receberMedico();
EnderecoMed receberEnderecoMed();
void inserirMedico();
Med * buscarMedico();
int removerMedico();
void listarMedicos();


//Início do main  
//Login para acessar o menu.(Login:Clinip - senha:1234)
int main(int argc, char** argv)  
{  
    telaLogin();  
    return 0;  
}  
    void telaLogin(){ 
    char login[15] = "clinip";  
    char login1[15];  
    char senha[15] = "1234";  
    char senha1[15];          
    int loginEfetuado = 0; //0 - Falso e  1 - Verdadeiro  
    
    while(!loginEfetuado){  
        printf("Digite o Login: ");  
        scanf("%s", login1);  
        printf("Digite a Senha: ");  
        scanf("%s", senha1);  
    
        if (strcmp(login, login1) == 0 && strcmp(senha, senha1) == 0){  
            printf("\n\nLOGADO!\n\n");  
            loginEfetuado = 1;  
        }  
    
        else  
            printf("\n\nDADOS INVALIDOS!\n\n");      
    }  

    switch (loginEfetuado){ 
        case 1: 
        menuPrincipal(); 
    } 
}  

void erro(char * nome_arquivo) {
  printf("Nao foi possivel abrir o arquivo %s\n", nome_arquivo);
}

void sucesso() {
  system("cls");
  printf("Operacao realizada com sucesso!");
}
//Menu Principal

void menuPrincipal() {
  do {
    printf("\n");
    printf("\t\t\t\t      CLINIP! \n");
    printf("\t\t\t==========================\n");
    printf("\t\t\t|\t                      |\n");
    printf("\t\t\t|\t 1 - Cadastro         |\n");
    printf("\t\t\t|\t 2 - Consulta         |\n");
    printf("\t\t\t|\t 0 - Sair             |\n");
    printf("\t\t\t|\t                      |\n");
    printf("\t\t\t==========================\n");
    printf("\n\n");
    printf("\t\t\tPor favor, selecione uma opcao: ");

    fflush(stdin);
    scanf("%d", & input);
    system("cls");

    switch (input) {
      case 1:
        cadastro();
        break;
      case 2:
        consulta();
      case 3:
      case 4:
        break;
      case 0:
        exit(EXIT_SUCCESS);
      default:
        printf("\n\t\t\tOpcao invalida!\n\n");
        fflush(stdin);
    }
  } while (input != 0);

  system("cls");
}
void consulta() {
  do {
    printf("\n");
    printf("\t\t\t\t\t  CLINIP! \n");
    printf("\t\t\t==========================\n");
    printf("\t\t\t|\t                      |\n");
    printf("\t\t\t|\t 1 - Listar Cliente   |\n");
    printf("\t\t\t|\t 2 - Buscar Cliente   |\n");
    printf("\t\t\t|\t 3 - Listar Medicos   |\n");
    printf("\t\t\t|\t 4 - Buscar Medicos   |\n");
    printf("\t\t\t|\t 0 - Sair             |\n");
    printf("\t\t\t|\t                      |\n");
    printf("\t\t\t==========================\n");
    printf("\n\n");
    printf("\t\t\tPor favor, selecione uma opcao: ");

    fflush(stdin);
    scanf("%d", & input);
    system("cls");

    switch (input) {
      case 1:
        listarClientes();
        break;
      case 2:
        buscarCliente();
        break;
      case 3:
        listarMedicos();
        break;
      case 4:
        buscarMedico();
        break;
      case 5:
        menuPrincipal();
        break;
      case 0:
        exit(EXIT_SUCCESS);
      default:
        printf("\n\t\t\tOpcao invalida!\n\n");
        fflush(stdin);
    }
  } while (input != 0);
  
  system("cls");
}

void cadastro() {
  do {
    printf("\n");
    printf("\t\t\t\t\t  CLINIP! \n");
    printf("\t\t\t==========================\n");
    printf("\t\t\t|\t     Cadastrar...     |\n");
    printf("\t\t\t|\t 1 - Cliente          |\n");
    printf("\t\t\t|\t 2 - Medico           |\n");
    printf("\t\t\t|\t 0 - Sair             |\n");
    printf("\t\t\t|\t                      |\n");
    printf("\t\t\t==========================\n");
    printf("\n\n");
    printf("\t\t\tPor favor, selecione uma opcao: ");

    fflush(stdin);
    scanf("%d", & input);
    system("cls");

    switch (input) {
      case 1:
        menuClientes();
        break;
      case 2:
       menuMedico();
        break;
      case 0:
        exit(EXIT_SUCCESS);
      default:
        printf("\n\t\t\tOpcao invalida!\n\n");
        fflush(stdin);
    }
  } while (input != 0);
  
  system("cls");
}

void menuClientes() {
  do {
    printf("\n");
    printf("\t\t\t\t CLINIP! \n");
    printf("\t\t\t===============================\n");
    printf("\t\t\t|\t                      |\n");
    printf("\t\t\t|    1 - Cadastrar Cliente    |\n");
    printf("\t\t\t|    2 - Excluir Cadastro     |\n");
    printf("\t\t\t|    3 - Menu Principal       |\n");
    printf("\t\t\t|    0 - Sair                 |\n");
    printf("\t\t\t|                             |\n");
    printf("\t\t\t===============================\n");
    printf("\n\n");
    printf("\t\t\tPor favor, selecione uma opcao: ");

    fflush(stdin);
    scanf("%d", & input);
    system("cls");

    switch (input) {
      case 1:
         fflush(stdin);
        inserirCliente(receberCliente());
      case 2:
         removerCliente(qtdClientes, clientes_dir);
        break;
      case 3:
        menuPrincipal();
        break;
      case 0:
        exit(EXIT_SUCCESS);
      default:
        printf("\n\t\t\tOpcao invalida!\n\n");
        fflush(stdin);
    }
  } while (input != 0);

  system("cls");
}


void removerQuebraLinha(char * string) {
  if (string != NULL && strlen(string) > 0) {
    short tamanho = strlen(string);

    if (string[tamanho - 1] == '\n') {
      string[tamanho - 1] = '\0';
    }
  }
}

void receberString(char * string_destinoC, int quantidade_caracteres) {
  fgets(string_destinoC, quantidade_caracteres, stdin);
  removerQuebraLinha(string_destinoC);
}

Pessoa receberCliente() {
  Pessoa p;
  
  fflush(stdin);
  printf("Nome: ");
  receberString(p.nome, 39);
  fflush(stdin);

  printf("CPF: ");
  receberString(p.reg, 13);
  fflush(stdin);

  printf("RG: ");
  receberString(p.rg, 11);
  fflush(stdin);

  printf("Telefone: ");
  receberString(p.telefone, 12);
  fflush(stdin);
  
  printf("Especialidade: ");
  receberString(p.especialidade, 20);
  fflush(stdin);
    
  printf("Data: ");
  receberString(p.data, 8);
  fflush(stdin);
    
  printf("Hora: ");
  receberString(p.hora, 5);
  fflush(stdin);
  

  p.end = receberEndereco();
  fflush(stdin);
  

  return p;
}

Endereco receberEndereco() {
  Endereco e;

  printf("Rua: ");
  receberString(e.rua, 39);
  fflush(stdin);

  printf("Numero: ");
  receberString(e.numero, 5);
  fflush(stdin);

  printf("CEP: ");
  receberString(e.cep, 9);
  fflush(stdin);

  printf("Bairro: ");
  receberString(e.bairro, 29);
  fflush(stdin);
  
  printf("Cidade: ");
  receberString(e.cidade, 20);
  fflush(stdin);

  printf("Estado: ");
  receberString(e.estado, 20);
  
  return e;
}

void inserirCliente(Pessoa p) {
  if (qtdClientes == tamClientes) {
    tamClientes *= 1.5;
    clientes = realloc(clientes, tamClientes * sizeof(Pessoa));
  }

  clientes[qtdClientes] = p;
  qtdClientes++;
}

void listarClientes() {
  int c;

  printf("\nListando %d clientes cadastrados\n", qtdClientes);

  for (c = 0; c < qtdClientes; c++) {
    printf("-----------------------------------\n");
    printf("(%d)\n", c + 1);
    printf("Nome  = %s\n", clientes[c].nome);
    printf("CPF = %s\n", clientes[c].reg);
    printf("RG = %s\n", clientes[c].rg);
    printf("Telefone = %s\n", clientes[c].telefone);
    printf("Endereco = %s", clientes[c].end.rua);
    printf(" - %s,", clientes[c].end.numero);
    printf(" %s,", clientes[c].end.bairro);
    printf(" %s", clientes[c].end.cidade);
    printf(" - %s.\n", clientes[c].end.estado);
    printf("Especialidade = %s\n", clientes[c].especialidade);
    printf("Data = %s\n", clientes[c].data);
    printf("Hora= %s\n", clientes[c].hora);
  }
}


Pessoa * buscarCliente() {
  Pessoa * p = NULL;
  int i;
  char cpf[12];

  printf("Digite o CPF do cliente a ser buscado: ");
  fgets(cpf, 11, stdin);

  for (i = 0; i < qtdClientes; i++) {
    if (strcmp(clientes[i].reg, cpf) == 0) {
      p = & clientes[i];
      break;
    }
  }

  return p;
}

int removerCliente(int qtd, char * dir){
  int i, CPF, sucess = 0;

  printf("Digite o CPF do cliente que deseja remover: ");
  scanf("%d", & CPF);

  for (i = 0; i < qtd; i++) {
    if ((clientes[i].reg - CPF) == 0) {
      while (i < qtd - 1) {
        clientes[i] = clientes[i + 1];
        i++;
      }

      qtd--;
      sucess = 1;
      break;
    } else {
      erro(dir);
    }
  }
}
void menuMedico() {
  do {
    printf("\n");
    printf("\t\t\t\t CLINIP! \n");
    printf("\t\t\t===============================\n");
    printf("\t\t\t|\t                           |\n");
    printf("\t\t\t|    1 - Cadastrar Medico    |\n");
    printf("\t\t\t|    2 - Excluir Cadastro     |\n");
    printf("\t\t\t|    3 - Menu Principal       |\n");
    printf("\t\t\t|    0 - Sair                 |\n");
    printf("\t\t\t|                             |\n");
    printf("\t\t\t===============================\n");
    printf("\n\n");
    printf("\t\t\tPor favor, selecione uma opcao: ");

    fflush(stdin);
    scanf("%d", & input);
    system("cls");

    switch (input) {
      case 1:
        fflush(stdin);
        inserirMedico(receberMedico());
        break;
      case 2:
        removerMedico(qtdMedicos, medicos_dir);
        break;
      case 3:
        menuPrincipal();
        break;
      case 0:
        exit(EXIT_SUCCESS);
      default:
        printf("\n\t\t\tOpcao invalida!\n\n");
        fflush(stdin);
    }
  } while (input != 0);

  system("cls");
}



Med receberMedico() {
  Med m;

  printf("Nome: ");
  receberString(m.nome, 39);
  fflush(stdin);

  printf("CPF: ");
  receberString(m.reg, 13);
  fflush(stdin);

  printf("RG: ");
  receberString(m.rg, 11);
  fflush(stdin);

  printf("Telefone: ");
  receberString(m.telefone, 12);
  fflush(stdin);

  m.endMed = receberEnderecoMed();

  sucesso();

  return m;
}

EnderecoMed receberEnderecoMed() {
  EnderecoMed e;

  printf("Rua: ");
  receberString(e.rua, 39);
  fflush(stdin);

  printf("Numero: ");
  receberString(e.numero, 5);
  fflush(stdin);

  printf("CEP: ");
  receberString(e.cep, 9);
  fflush(stdin);

  printf("Bairro: ");
  receberString(e.bairro, 29);
  fflush(stdin);
  
  printf("Cidade: ");
  receberString(e.cidade, 20);
  fflush(stdin);
  
  printf("Estado: ");
  receberString(e.estado, 20);

  sucesso();

  return e;
}

void inserirMedico(Med m) {
  if (qtdMedicos == tamMedicos) {
    tamMedicos *= 1.5;
    medicos = realloc(medicos, tamMedicos * sizeof(Med));
  }

  medicos[qtdMedicos] = m;
  qtdMedicos++;
}

void listarMedicos() {
  int c;

  printf("\nListando %d Medicos cadastrados\n", qtdMedicos);

  for (c = 0; c < qtdMedicos; c++) {
    printf("-----------------------------------\n");
    printf("(%d)\n", c + 1);
    printf("Nome  = %s\n", medicos[c].nome);
    printf("CPF = %s\n", medicos[c].reg);
    printf("RG = %s\n", medicos[c].rg);
    printf("Telefone = %s\n", medicos[c].telefone);
    printf("Endereco = %s", medicos[c].endMed.rua);
    printf(" - %s,", medicos[c].endMed.numero);
    printf(" %s,", medicos[c].endMed.bairro);
    printf(" %s", medicos[c].endMed.cidade);
    printf(" - %s.", medicos[c].endMed.estado);
  }
}


Med * buscarMedico() {
  Med * m = NULL;
  int i;
  char cpf[12];

  printf("Digite o CPF do cliente a ser buscado: ");
  fgets(cpf, 11, stdin);

  for (i = 0; i < qtdMedicos; i++) {
    if (strcmp(medicos[i].reg, cpf) == 0) {
      m = & medicos[i];
      break;
    }
  }

  return m;
}

int removerMedico(int qtd, char * dir){
  int i, CPF, sucess = 0;

  printf("Digite o CPF do cliente que deseja remover: ");
  scanf("%d", & CPF);

  for (i = 0; i < qtd; i++) {
    if ((medicos[i].reg - CPF) == 0) {
      while (i < qtd - 1) {
        medicos[i] = medicos[i + 1];
        i++;
      }

      qtd--;
      sucess = 1;
      break;
    } else {
      erro(dir);
    }
  }


  return sucess;
}