#include <string.h>

typedef struct {
    char codigo[30];
    char descricao[301];
    float preco;
} Produto;

void Replace(char* String, char antigo, char novo){
    int i;
    for(i=0; String[i]!='\0'; i++){
        if(String[i] == antigo){
            String[i] = novo;
        }
    }
}

short menuProduto(){
    short op;
    puts("1 - Incluir Produto");
    puts("2 - Excluir Produto");
    puts("3 - Consultar Produto");
    puts("4 - Listar Produtos");
    puts("0 - Voltar ao Menu Princpal");
    scanf("%hd", &op);
    return op;
}

Produto* buscarProduto(char* codigo){
    FILE *arq;
    long int n;
    int i;
    Produto *aux=NULL;
    arq = fopen("./produtos.bin", "rb");
    if(arq == NULL){
        puts("Erro ao abrir o arquivo.");
        exit(1);
    }
    fseek(arq, 0, SEEK_END);
    n = ftell(arq);
    n = n/sizeof(Produto);
    Produto *V;
    V = malloc(n*sizeof(Produto));
    rewind(arq);
    fread(V, sizeof(Produto), n, arq);
    fclose(arq);
    for(i=0; i<n; i++){
        if(strcmp(V[i].codigo, codigo) == 0){
            aux = malloc(sizeof(Produto));
            *aux = V[i];
        }
    }
    free(V);
    return aux;
}

short gravarProduto(Produto *novo){
    //char aux[30];
    printf("Digite o código do produto: ");
    setbuf(stdin, NULL);
    fgets(novo->codigo, 30, stdin);
    Replace(novo->codigo, '\n', '\0');
    //novo->codigo = aux;
    printf("Escreva a descrição do produto [Máximo de 300 caracteres]\n");
    setbuf(stdin, NULL);
    fgets(novo->descricao, 301, stdin);
    printf("Digite o Preço do produto(Utilize . ao invés de ,): ");
    scanf("%f", &novo->preco);
}

void imprimirProduto(Produto *produto){
    if(produto == NULL){
        puts("Error");
        exit(1);
    }
    printf("%s\n", produto->codigo);
    printf("%s", produto->descricao);
    printf("%f\n", produto->preco);
}

void listarProdutos(){
    FILE *arq;
    long int n;
    int i;
    arq = fopen("./produtos.bin", "rb");
    if(arq == NULL){
        puts("Erro ao abrir o arquivo.");
        exit(1);
    }
    fseek(arq, 0, SEEK_END);
    n = ftell(arq);
    fclose(arq);
    n = n/sizeof(Produto);
    Produto *V;
    V = malloc(n*sizeof(Produto));
    arq = fopen("./produtos.bin","rb");
    fread(V, sizeof(Produto), n, arq);
    for(i=0; i<n; i++){
        printf("%s\n", V[i].codigo);
        printf("%s", V[i].descricao);
        printf("%f\n", V[i].preco);
        puts("");
    }
    fclose(arq);
    free(V);
}

void removerProduto(char* codigo){

}
