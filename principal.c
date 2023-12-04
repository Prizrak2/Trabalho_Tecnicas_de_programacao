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
    puts("");
    return op;
}

int main(){
    short op=1, op_cliente, op_produto, op_pedido;
    //variáveis Cliente

    //variáveis Produto
    Produto *novo, *produto_buscado;
    char aux_codigo[CODIGO_TAM];
    short comfirmacaoDeExclusao;
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
                    puts("");
                    break;
                case 2://Excluir Produto
                    printf("Digite o código do produto: ");
                    setbuf(stdin, NULL);
                    fgets(aux_codigo, CODIGO_TAM, stdin);
                    Replace(aux_codigo, '\n', '\0');
                    if(analisarProduto(aux_codigo) == 1){//Analisa Produto
                        if(consultarCodigoPedido(aux_codigo)){
                            puts("O Produto não pode ser excluído, pois consta em pedidos de clientes.");
                            puts("");
                        }
                        else{
                            printf("Deseja mesmo excluir esse produto? (1 - Sim\n0 - Não)\n->");
                            scanf("%hd", &comfirmacaoDeExclusao);
                            if(comfirmacaoDeExclusao == 1){
                                removerProduto(aux_codigo);
                            }
                            puts("");
                        }
                    }
                    else{
                        puts("ERROR!\nEsse Produto não existe!");
                        puts("");
                    }
                    break;
                case 3://Consultar Produto
                    produto_buscado = malloc(sizeof(Produto));
                    printf("Digite o código do produto: ");
                    setbuf(stdin, NULL);
                    fgets(aux_codigo, CODIGO_TAM, stdin);
                    Replace(aux_codigo, '\n', '\0');
                    produto_buscado = buscarProduto(aux_codigo);
                    if(analisarProduto(aux_codigo) == 0){//Analisa Produto
                        puts("O Produto não existe.");
                        puts("");
                    }
                    else{
                        imprimirProduto(produto_buscado);
                        puts("");
                    }
                    break;
                case 4://Listar Produtos
                    listarProdutos();
                    break;
                case 0://Voltar ao Menu Principal
                    puts("Voltando ao Menu Principal...");
                    puts("");
                    break;
                default:
                    puts("Opção Incoerente.");
                    puts("");
                    break;
                }
            }
            break;
        case 3://Pedido
            break;
        case 0:
            puts("Saindo...");
            puts("");
            break;
        default:
            puts("Opção Incoerente.");
            puts("");
            break;
        }
    }
}
