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
    //Calcula a quantidade de elementos do arquivo
    fseek(arq, 0, SEEK_END);
    n = ftell(arq);
    n = n/sizeof(Produto);
    Produto *V;
    V = malloc(n*sizeof(Produto)); //Aloca dinamicamente um vetor V com n elementos
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
    Produto *aux = malloc(sizeof(Produto));
    printf("Digite o código do produto: ");
    setbuf(stdin, NULL);
    fgets(novo->codigo, 30, stdin);
    Replace(novo->codigo, '\n', '\0');
    aux = buscarProduto(novo->codigo);
    if(aux != NULL){
        puts("O Produto já existe.");
        while(aux != NULL){
            printf("Digite o código do produto novamente: ");
            setbuf(stdin, NULL);
            fgets(novo->codigo, 30, stdin);
            Replace(novo->codigo, '\n', '\0');
            aux = buscarProduto(novo->codigo);
        }
    }
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
    //Calcula a quantidade de elementos do arquivo
    fseek(arq, 0, SEEK_END);
    n = ftell(arq);
    fclose(arq);
    n = n/sizeof(Produto);
    Produto *V;
    V = malloc(n*sizeof(Produto)); //Aloca dinamicamente um vetor V com n elementos
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
    FILE *arq;
    long int n;
    int i, j;
    Produto *V_Antigo, *V_Novo;
    arq = fopen("./produtos.bin", "rb");
    if(arq == NULL){
        puts("Erro ao abrir o arquivo.");
        exit(1);
    }
    //Calcula a quantidade de elementos do arquivo
    fseek(arq, 0, SEEK_END);
    n = ftell(arq);
    n = n/sizeof(Produto);
    V_Antigo = malloc(n*sizeof(Produto)); //Aloca dinamicamente um vetor V_Antigo com n elementos, o qual é responsável por armazenar os dados antigos do vetor
    V_Novo = malloc((n-1)*sizeof(Produto));//Aloca dinamicamente um vetor V_Novo com n-1 elementos, o qual ficará responsável por armazenar os novos dados que serão gravados no arquivo
    rewind(arq);
    fread(V_Antigo, sizeof(Produto), n, arq);
    fclose(arq);
    //Código que identifica qual item de V_Antigo deve ser removido e apaga os dados desse item
    for(i=0; i<n; i++){
        if(strcmp(V_Antigo[i].codigo, codigo)==0){
            strcpy(V_Antigo[i].codigo, "");
            strcpy(V_Antigo[i].descricao, "");
            V_Antigo[i].preco  = 0.0;
        }
    }
    //Coloca dos dados de V_Antigo que não foram apagados em V_Novo
    j = 0;
    for(i=0; strcmp(V_Antigo[i].codigo, "")!=0; i++){
        V_Novo[j] = V_Antigo[i];
        j++;
    }
    for(i=i+1; i<n; i++){
        V_Novo[j] = V_Antigo[i];
        j++;
    }
    arq = fopen("./produtos.bin", "wb");
    rewind(arq);
    //Sobreescreve o Arquivo com os dados de V_Novo
    fwrite(V_Novo, sizeof(Produto), (n-1), arq);
    fflush(arq);
    fclose(arq);
    free(V_Antigo);
    free(V_Novo);
}

