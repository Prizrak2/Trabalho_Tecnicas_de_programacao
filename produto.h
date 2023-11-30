typedef struct {
    int codigo;
    char descricao[301];
    float preco;
} Produto;

short menuProduto(){
    short op;
    puts("1 - Incluir Produto");
    puts("2 - Excluir Produto");
    puts("3 - Consultar Produto");
    puts("0 - Voltar ao Menu Princpal");
    scanf("%hd", &op);
    return op;
}

short gravarProduto(Produto *novo){
    printf("Digite o código do produto: ");
    scanf("%d", &novo->codigo);
    printf("Escreva a descrição do produto [Máximo de 300 caracteres]\n");
    setbuf(stdin, NULL);
    fgets(novo->descricao, 301, stdin);
    printf("Digite o Preço do produto(Utilize . ao invés de ,): ");
    scanf("%f", &novo->preco);
}

//Consultar Produto
