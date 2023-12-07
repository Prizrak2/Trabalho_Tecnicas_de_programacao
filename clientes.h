#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED

#include <string.h>
#include <stdbool.h>

typedef struct{
    char cpf[12];
    char nome[30];
    char celular[15];
    char telefone[15];
    char email[100];
} Cliente;

short menuCliente(){
    int op;
    //opções do menu
    printf("1 - Cadastrar Cliente\n2 - Consultar Cliente\n3 - Remover Cliente\n4 - Listar Clientes\n0 - Menu Principal\n\n");
    scanf("%d", &op);
    puts("");
    return op;
}

int analisarCliente(char*cpf){
    FILE *arq = fopen("cliente.csv", "r");
     if (arq) {
        char linha[256];
        char *ptr;

        //verifica se o cliente ja existe buscando seu CPF, caso exista retornará 1 e a função que receber 1 irá pedir para redigitar o CPF
        while (fgets(linha, sizeof(linha), arq) != NULL) {
            ptr = strstr(linha, cpf);
            if(ptr){
                return 1;
            }
        }
        fflush(arq);
        fclose(arq);
    } else {
        printf("ERRO: nao foi possivel abrir o arquivo.\n\n");
    }
    return 0;
}

short eValido(char*cpf){
    int i;
    char aux, cpfinicial[12];
    int auxv, soma = 0, primeirodigito;

    for(i = 0; i <= strlen(cpf); i++){
        cpfinicial[i] = cpf[i];
    }

    //calculo do primeiro digito
    for(i = 0; i < 9; i++){
        aux = cpf[i];
        auxv = atoi(&aux);

        auxv *= i + 1;

        soma += auxv;
    }

    primeirodigito = soma % 11;

    if (primeirodigito >= 10){
        primeirodigito = 0;
    }

    soma = 0, auxv = 0;

    int segundodigito;

    char aux2[10];

    sprintf(aux2, "%d", primeirodigito);

    cpf[9] = aux2[0];
        //calculo do segundo digito
    for(i = 0; i < 10; i++){
        aux = cpf[i];
        auxv = atoi(&aux);

        auxv *= i;

        soma += auxv;
    }

    segundodigito = soma % 11;

    char aux3[10];

    sprintf(aux3, "%d", segundodigito);

    cpf[10] = aux3[0];

    puts("");
    //verifica se o cpf calculado bate com o cpf informado
    if(cpfinicial[9] != cpf[9] || cpfinicial[10] != cpf[10]){
        printf("\nCPF invalido! Tente Novamente.\n\n");
        return 0;
    }

    return 1;
}

Cliente* buscarCliente(char*cpf){
    FILE *arq;
    Cliente *aux = NULL;
        char linha[256];
        int i = 0;
        bool jaleu = false;
        arq = fopen("cliente.csv", "r");
        if(arq == NULL){
            puts("Erro ao abrir o arquivo.");
            exit(1);
        }
            while (fgets(linha, sizeof(linha), arq) != NULL) {
                if(strstr(linha, cpf) != NULL){
                    jaleu = true;
                }
                if(jaleu){
                    printf("%s", linha);
                    i++;
                }
                if(i >= 5){
                    break;
                }
            }
    fclose(arq);
    return aux;
}


void imprimirCliente(Cliente *cliente){
    if(cliente == NULL){
    } else {
        printf("CPF: %s\n", cliente->cpf);
        printf("Nome: %s\n", cliente->nome);
        printf("Celular: %s\n", cliente->celular);
        printf("Telefone: %s\n\n", cliente->telefone);
        printf("Email: %s\n", cliente->email);
    }
}

Cliente cadastrarPessoa() {
    Cliente C;
    bool continua = true;

    scanf("%*c"); //limpa o buffer da linha para nao ocorrer bugs
    printf("CPF: ");
    scanf("%s", &C.cpf);

    //verificação de CPF
    while(continua){
        while(eValido(C.cpf) == 0){
            printf("CPF: ");
            scanf("%s", &C.cpf);
        }

        while(analisarCliente(C.cpf) == 1){
            printf("Cliente ja existente! Tente novamente:\n");
            printf("CPF: ");
            scanf("%s", &C.cpf);
        }
        continua = false;
    }

    //printf's e scanf's para o struct
    printf("Nome: ");
    getchar();
    fgets(C.nome, 50, stdin);
    C.nome[strcspn(C.nome, "\n")] = 0; //mesmo que o de cima
    puts("");

    printf("Celular: ");
    fgets(C.celular, 15, stdin);
    C.celular[strcspn(C.celular, "\n")] = 0; //mesmo que o de cima
    puts("");

    printf("Telefone: ");
    fgets(C.telefone, 15, stdin);
    C.telefone[strcspn(C.telefone, "\n")] = 0; //mesmo que o de cima
    puts("");

    printf("Email: ");
    fgets(C.email, 50, stdin);
    C.email[strcspn(C.email, "\n")] = 0; //mesmo que o de cima
    puts("");

    puts("");

    return C;
}

short gravarCliente(Cliente* novo){
    FILE *arq = fopen("cliente.csv", "a+");
    if (arq) {
        int i;
        //imprime os dados no arquivo
            fprintf(arq, "CPF: %s\n", novo->cpf);
            fprintf(arq, "Nome: %s\n", novo->nome);
            fprintf(arq, "Celular: %s\n", novo->celular);
            fprintf(arq, "Telefone: %s\n", novo->telefone);
            fprintf(arq, "Email: %s\n\n", novo->email);
            fprintf(arq, "\n");
        fflush(arq);
        fclose(arq);

        puts("Cliente Cadastrado!\n");
    } else {
        printf("ERRO: nao foi possivel abrir o arquivo.\n\n");
    }
}

void listarClientes(){
    FILE *arq = fopen("cliente.csv", "r");
    if (arq) {
        char linha[256];
        while (fgets(linha, sizeof(linha), arq) != NULL) {
            printf("%s", linha);
        }
        fflush(arq);
        fclose(arq);
    } else {
        printf("ERRO: nao foi possivel abrir o arquivo.\n\n");
    }
}

#endif // CLIENTES_H_INCLUDED
