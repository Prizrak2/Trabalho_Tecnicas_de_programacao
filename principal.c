#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"
#include "produto.h"
#include "pedido.h"

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

}
