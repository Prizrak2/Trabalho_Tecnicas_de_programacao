#include <stdio.h>
#include <stdlib.h>
//#include "cliente.h"
#include "produto.h"
//#include "pedido.h"

short menuPrincipal(){
    short op;
    puts("1 - Clientes");
    puts("2 - Produtos");
    puts("3 - Pedidos");
    puts("0 - Sair");
    scanf("%hd", &op);
    return op;
}

int main(){
    short op=1;
    while(op!=0){
        op = menuPrincipal();
        switch(op){
        case 1://Cliente
            break;
        case 2://Produto
            short op2=1;
            while(op2 != 0){
                op2 = menuProduto();
                switch(op2){
                case 1://Incluir Produto
                    break;
                case 2://Excluir Produto
                    break;
                case 3://Consultar Produto
                    break;
                case 4://Listar Produtos
                    break;
                case 0://Voltar ao Menu Principal
                    puts("Voltando ao Menu Principal...");
                    break;
                default:
                    puts("Opção Incoerente.");
                    break;
                }
            }
            break;
        case 3://Pedido
            break;
        case 0:
            puts("Saindo...");
            break;
        default:
            puts("Opção Incoerente.");
            break;
        }
    }
}
