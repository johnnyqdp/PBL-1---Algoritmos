/*****************************************************************************************
Autor: Johnny Quest Dantas Pereira
Componente Curricular: Algoritmos I
Concluido em: 21/12/2017
Declaro que este código foi elaborado por mim de forma individual e não contém nenhum
trecho de código de outro colega ou de outro autor, tais como provindos de livros e
apostilas, e páginas ou documentos eletrônicos da Internet. Qualquer trecho de código
de outra autoria que não a minha está destacado com uma citação para o autor e a fonte
do código, e estou ciente que estes trechos não serão considerados para fins de avaliação.
******************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <locale.h>

typedef struct arquivo{ //Lista encadeada de arquivos, armazena nomes de arquivos e quantidade de vezes que uma palavra se repete nele.
    int quantidade;
    char nomearquivo[256];
    struct arquivo *proximo;
}arquivo;

typedef struct principal{ //Estrutura de um nó da lista encadeada principal. Armazena uma palavra, a quantidade de arquivos em que ela aparece e aponta pra uma lista encadeada de arquivos.
    char palavra[256];
    int quantarquivos;
    struct arquivo *arquivo; //Ponteiro para uma lista encadeada de arquivos
    struct principal *proximo; //Ponteiro para o próximo nó da célula
}principal;

//Protótipos das funções:
void MensagemDeErro(int erro);
int VerificaArgumentos(int argc, char* argv[]);
void FuncaoInserirArquivo(char nomearquivo[]);
principal* Carregar_Lista(principal *p);
principal* Gerar_Lista(principal *p, char *nomearquivo);
void RemovePontuacao(char palavra[]);
int Verifica_Se_Ja_Tem(principal *p, char palavra[]);
principal* AtualizaNaLista(principal *p, char palavra[], char nomearquivo[]);
principal* InsereNaLista_1_1(principal *p, char palavra[], int qtarquivos);
principal* InsereNaLista_1_2(principal *p, int quantidade, char nomearquivo[]);
principal* InsereNaLista_2(principal *p, char palavra[], char nomearquivo[]);
void SalvarLista(principal *p);
void DeletaListaInvertida(void);
void FuncaoDeBusca(char busca[]);

//A função main verifica os argumentos inseridos pelo usuário e redireciona o programa para uma função correspondente.
int main(int argc, char* argv[]){
    //setlocale(LC_ALL, "");
    int opcao=VerificaArgumentos(argc, argv);
    if(opcao==0){
        MensagemDeErro(1);
    }else if(opcao==1){
        FuncaoInserirArquivo(argv[2]);
    }else if (opcao==2){
        FuncaoDeBusca(argv[2]);
    }else if (opcao==3){
        DeletaListaInvertida();
    }
    return 0;
}

//Essa função imprime uma mensagem de erro baseada no número recebido.
void MensagemDeErro(int erro){
    if (erro==1){
        printf("Voce cometeu algum erro na insercao de argumentos. Suas opcoes sao:");
        printf("\n\t-arquivo + endereco de um arquivo .txt (para inserir um novo arquivo)");
        printf("\n\t-busca + palavra (para buscar uma palavra nos arquivos inseridos)");
        printf("\n\t-zerar (para zerar a lista de palavras salvas)");
    }else if(erro==2){
        printf("Houve algum problema. Por favor, verifique se inseriu o endereco do \narquivo corretamente, ou se ha algo escrito nele.");
    }else if(erro==3){
        printf("ERRO: Nao foi possivel deletar o arquivo listainvertida.txt");
    }else if(erro==4){
        printf("ERRO: Voce ainda nao inseriu nenhum arquivo no indice.");
    }else if(erro==5){
        printf("\n\tEssa palavra nao foi encontrada.\n\t");
    }else
        printf("Erro ao gerar a lista invertida.");
}

//Essa função retorna 0 caso o usuario não insira argumentos válidos, 1 caso o usuario queira inserir um arquivo, 2 caso queira buscar uma palavra e 3 caso queira limpar a lista invertida.
int VerificaArgumentos(int argc, char* argv[]){
    if (argc==3 && strcasecmp(argv[1], "arquivo")==0)
        return 1;
    else if (argc==3 && strcasecmp(argv[1], "busca")==0)
        return 2;
    else if (argc==2 && strcasecmp(argv[1], "zerar")==0)
        return 3;
    else
        return 0;
}

//Nessa função ocorre todo o processo de inserir as palavras de um arquivo no índice invertido.
void FuncaoInserirArquivo(char nomearquivo[]){
    principal *p; //Este seria o nó inicial da lista encadeada, p de ponteiro.
    p=(principal*)malloc(sizeof(principal));
    p=NULL;
    /*O programa lerá o índice invertido que está armazenado (se tiver) e vai inserir todos os valores contidos
    nele em uma lista encadeada, em seguida, lerá o arquivo que o usuário informou, incrementando a lista
    encadeada existente com as palavras dele. Por último, o programa substituirá o índice invertido anterior
    pelo "novo".*/
    p=Carregar_Lista(p); //Lendo o índice invertido
    p=Gerar_Lista(p, nomearquivo); //Lendo o arquivo informado pelo usuário
    if (p==NULL){
        MensagemDeErro(2);
        return;
    }
    SalvarLista(p); //Substituindo o indice invertido anterior.
}

//Essa função lê os valores do índice invertido e os insere na lista encadeada do programa.
principal* Carregar_Lista(principal *p){
    char palavra[50], nomearquivo[50];
    int quantidade, qtarquivos, i;
    FILE *file;
    file=fopen("listainvertida.txt", "r");
    if (file==NULL){
        return NULL;
    }
    else{
        while(1){
            fscanf(file, "%s %i", palavra, &qtarquivos);
            if (feof(file))
                break;
            p=InsereNaLista_1_1(p, palavra, qtarquivos);
            for(i=0; i<qtarquivos;i++){
                fscanf(file, "%i %s", &quantidade, nomearquivo);
                p=InsereNaLista_1_2(p, quantidade, nomearquivo);
            }
        }
        fclose(file);
        return p;
    }
}

//Recebe uma palavra e a quantidade de arquivos ela aparece e põe esses valores em um nó da lista encadeada principal.
principal* InsereNaLista_1_1(principal *p, char palavra[], int qtarquivos){
    principal *aux;
    aux=(principal*)malloc(sizeof(principal));
    strcpy(aux->palavra, palavra);
    aux->quantarquivos=qtarquivos;
    aux->proximo=p;
    aux->arquivo=NULL;
    p=aux;
    return p;
}

//Recebe um arquivo e a quantidade de vezes que a palavra aparece nele e insere esses valores em um nó de arquivo dentro do nó principal da palavra em questão.
principal* InsereNaLista_1_2(principal *p, int quantidade, char nomearquivo[]){
    arquivo *aux;
    aux=(arquivo*)malloc(sizeof(arquivo));
    strcpy(aux->nomearquivo, nomearquivo);
    aux->quantidade=quantidade;
    aux->proximo=p->arquivo;
    p->arquivo=aux;
    return p;
}

//Incrementa a lista encadeada com as palavras do arquivo novo que o usuário informou.
principal* Gerar_Lista(principal *p, char *nomearquivo){
    FILE *file;
    file=fopen(nomearquivo, "r");
    if (file==NULL){
        return NULL;
    }
    char palavra[256];
    int jatem;
    while (!feof(file)){
        fscanf(file, "%s", palavra);
        RemovePontuacao(palavra);
        jatem=Verifica_Se_Ja_Tem(p, palavra);
        if(jatem==0){
            p=InsereNaLista_2(p, palavra, nomearquivo);
        }else if(jatem==1){
            p=AtualizaNaLista(p, palavra, nomearquivo);
        }
    }
    fclose(file);
    return p;
}

//Essa função remove vírgula, ponto ou ponto e vírgula caso um desses seja o ultimo caractere da palavra.
void RemovePontuacao(char palavra[]){
    int ultimoindice;
    ultimoindice = (strlen(palavra)-1);
    if (palavra[ultimoindice]==',' || palavra[ultimoindice]=='.' || palavra[ultimoindice]==';'){
        palavra[ultimoindice]='\0';
    }
}

//Essa função recebe uma palavra, verifica se ela já está presente na lista principal, retorna 0 pra não e 1 pra sim
int Verifica_Se_Ja_Tem(principal *p, char palavra[]){
    int jatem=0;
    principal *aux;
    aux=p;
    while(aux!=NULL){
        if(strcasecmp(aux->palavra, palavra)==0){
            jatem=1;
            break;
        }
        aux=aux->proximo;
    }
    return jatem;
}

//Caso no arquivo que o usuario inseriu tenha uma palavra que já esteja na lista encadeada principal, essa função irá analisar se já existe um nó de arquivo do mesmo arquivo que está sendo analisado, se sim, ela apenas soma a quantidade, se não, ela cria esse nó.
principal* AtualizaNaLista(principal *p, char palavra[], char nomearquivo[]){
    principal *aux;
    aux=p;
    int flag=0, i;
    while(aux!=NULL){
        if (strcasecmp(aux->palavra, palavra)==0){
            arquivo *aux2;
            aux2=aux->arquivo;
            for(i=0; i<(aux->quantarquivos); i++){
                if(strcasecmp(aux2->nomearquivo, nomearquivo)==0){
                    aux2->quantidade++;
                    flag=1;
                    break;
                }
            }
        }
        aux=aux->proximo;
    }
    if(flag==0){
        aux=p;
        while(aux!=NULL){
            if (strcasecmp(aux->palavra, palavra)==0){
                aux->quantarquivos++;
                arquivo *novo;
                novo=(arquivo*)malloc(sizeof(arquivo));
                strcpy(novo->nomearquivo, nomearquivo);
                novo->quantidade=1;
                novo->proximo=aux->arquivo;
                aux->arquivo=novo;
            }
            aux=aux->proximo;
        }
    }
    return p;
}

//Essa função cria um nó na lista principal.
principal* InsereNaLista_2(principal *p, char palavra[], char nomearquivo[]){
    principal *nova;
    nova=(principal*)malloc(sizeof(principal));
    strcpy(nova->palavra, palavra);
    nova->quantarquivos=1;
    nova->arquivo=NULL;

    arquivo *novo;
    novo=(arquivo*)malloc(sizeof(arquivo));
    strcpy(novo->nomearquivo, nomearquivo);
    novo->quantidade=1;
    novo->proximo=nova->arquivo;
    nova->arquivo=novo;

    nova->proximo=p;
    p=nova;
    return p;
}

//Essa função contém processo de "salvar" a lista encadeada em um arquivo txt, de forma que o programa possa lê-lo novamente e capturar os valores.
void SalvarLista(principal *p){
    FILE *file;
    file=fopen("listainvertida.txt", "w");
    if (file==NULL){
        MensagemDeErro(6);
    }else{
        int i;
        principal *aux;
        aux=p;
        while(aux!=NULL){
            fprintf(file, "%s %i ", aux->palavra, aux->quantarquivos);
            arquivo *aux2;
            aux2=aux->arquivo;
            for(i=0; i<aux->quantarquivos; i++){
                fprintf(file, "%i %s ", aux2->quantidade, aux2->nomearquivo);
                aux2=aux2->proximo;
            }
            fprintf(file, "\n");
            aux=aux->proximo;
        }
        fclose(file);
        printf("\tArquivo registrado com sucesso!");
        printf("\n\tOBS: NAO CADASTRE ESSE ARQUIVO NOVAMENTE!\n");
    }
}

//Essa função exclui o arquivo listainvertida.txt
void DeletaListaInvertida(void){
    int flag = remove("listainvertida.txt");
    if(flag == 0){
        printf("A lista invertida foi deletada com sucesso.");
    }else{
        MensagemDeErro(3);
   }
}

//Essa função busca uma palavra no arquivo listainvertida.txt, e retorna todos os arquivos em que ela aparece, e quantas vezes aparece em cada um.
void FuncaoDeBusca(char busca[]){
    FILE *file;
    file=fopen("listainvertida.txt", "r");
    int i, quantarquivos, quantvezes;
    char palavra[256], arquivo[256];
    if (file==NULL){
        MensagemDeErro(4);
    }else{
        while(1){
            fscanf(file, "%s %i", palavra, &quantarquivos);
            if(strcasecmp(palavra, busca)==0){
                printf("\tEssa palavra se encontra:");
                for (i=0; i<quantarquivos; i++){
                    fscanf(file, "%i %s", &quantvezes, arquivo);
                    printf("\n\t-%i vezes em %s", quantvezes, arquivo);
                }
                printf("\n");
                break;
            }
            for (i=0; i<quantarquivos; i++){
                fscanf(file, "%i %s", &quantarquivos, palavra);
            }
            if(feof(file)){
                MensagemDeErro(5);
                break;
            }
        }
    }
}
