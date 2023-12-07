#include <stdio.h>
#include <stdlib.h>
#include "clientes.h"
//#include "produto.h"
//#include "pedido.h"

short menuPrincipal(){
    short op;
    puts("1 - Clientes");
    puts("2 - Produtos");
    puts("3 - Pedidos");
    puts("0 - Sair");
    scanf("%hd", &op);
    puts("");
    return op;
}

int main(){
    short op=1, op_cliente;// op_produto, op_pedido;
    //variáveis Cliente
    Cliente novo, *cliente_buscado;
    char cpf[12];
    //variáveis Produto
    //Variáveis Pedido

    //FILE *arq;
    while(op!=0){
        op = menuPrincipal();
        switch(op){
        case 1://Cliente
            op_cliente = 1;

            op_cliente = menuCliente();

            while(op_cliente != 0){
                switch(op_cliente){
                    case 1:
                        novo = cadastrarPessoa();
                        gravarCliente(&novo);
                        break;
                    case 2:
                        cliente_buscado = malloc(sizeof(Cliente));
                        printf("Digite o CPF do Cliente a ser consultado: ");
                        setbuf(stdin, NULL);
                        fgets(cpf, 12, stdin);
                        puts("");
                        cliente_buscado = buscarCliente(cpf);
                        if(eValido(cpf) == 0){

                        }
                        else{
                            if(analisarCliente(cpf) == 0){
                                puts("O Cliente nao existe.");
                                puts("");
                            }
                            imprimirCliente(cliente_buscado);
                            puts("");
                        }
                        break;
                    case 3:
                        printf("Digite o CPF do Cliente a ser removido: ");
                        setbuf(stdin, NULL);
                        fgets(cpf, 12, stdin);
                        puts("");
                        if(eValido(cpf) == 0){

                        }
                        else{
                            if(analisarCliente(cpf) == 0){
                                puts("O Cliente nao existe.");
                                puts("");
                            } else {
                            removerCliente(cpf);
                            }
                            puts("");
                        }
                        break;
                    case 4:
                        listarClientes();
                        break;
                    case 0:
                        break;
                    default:
                        printf("opcao invalida!!\n\n");
                        break;
                }

                op_cliente = menuCliente();
            }
            break;
        case 2://Produto

            break;
        case 3://Pedido
            break;
        case 0:
            puts("Saindo...");
            puts("");
            break;
        default:
            puts("Opcao Incoerente.");
            puts("");
            break;
        }
    }
}
