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
    short op=1, op_produto;
    //variáveis Cliente
    //variáveis Produto
    Produto *novo, *produto_buscado;
    char aux_codigo[30];
    //Variáveis Pedido
    FILE *arq;
    while(op!=0){
        op = menuPrincipal();
        switch(op){
        case 1://Cliente
            break;
        case 2://Produto
            op_produto=1;
            while(op_produto != 0){
                op_produto = menuProduto();
                switch(op_produto){
                case 1://Incluir Produto
                    novo = malloc(sizeof(Produto));
                    gravarProduto(novo);
                    arq = fopen("./produtos.bin", "ab");
                    fwrite(novo, sizeof(Produto), 1, arq);
                    fflush(arq);
                    fclose(arq);
                    break;
                case 2://Excluir Produto
                    printf("Digite o código do produto: ");
                    setbuf(stdin, NULL);
                    fgets(aux_codigo, 30, stdin);
                    Replace(aux_codigo, '\n', '\0');
                    removerProduto(aux_codigo);
                    break;
                case 3://Consultar Produto
                    produto_buscado = malloc(sizeof(Produto));
                    printf("Digite o código do produto: ");
                    setbuf(stdin, NULL);
                    fgets(aux_codigo, 30, stdin);
                    Replace(aux_codigo, '\n', '\0');
                    produto_buscado = buscarProduto(aux_codigo);
                    if(produto_buscado == NULL){
                        puts("O Produto não existe.");
                    }
                    else{
                        imprimirProduto(produto_buscado);
                    }
                    break;
                case 4://Listar Produtos
                    listarProdutos();
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
