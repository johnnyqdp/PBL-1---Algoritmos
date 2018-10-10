/*****************************************************************************************
Autor: Johnny Quest Dantas Pereira
Componente Curricular: Algoritmos I
Concluido em: 21/12/2017
Declaro que este c�digo foi elaborado por mim de forma individual e n�o cont�m nenhum
trecho de c�digo de outro colega ou de outro autor, tais como provindos de livros e
apostilas, e p�ginas ou documentos eletr�nicos da Internet. Qualquer trecho de c�digo
de outra autoria que n�o a minha est� destacado com uma cita��o para o autor e a fonte
do c�digo, e estou ciente que estes trechos n�o ser�o considerados para fins de avalia��o.
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

typedef struct principal{ //Estrutura de um n� da lista encadeada principal. Armazena uma palavra, a quantidade de arquivos em que ela aparece e aponta pra uma lista encadeada de arquivos.
    char palavra[256];
    int quantarquivos;
    struct arquivo *arquivo; //Ponteiro para uma lista encadeada de arquivos
    struct principal *proximo; //Ponteiro para o pr�ximo n� da c�lula
}principal;

//Prot�tipos das fun��es:
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

//A fun��o main verifica os argumentos inseridos pelo usu�rio e redireciona o programa para uma fun��o correspondente.
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

//Essa fun��o imprime uma mensagem de erro baseada no n�mero recebido.
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

//Essa fun��o retorna 0 caso o usuario n�o insira argumentos v�lidos, 1 caso o usuario queira inserir um arquivo, 2 caso queira buscar uma palavra e 3 caso queira limpar a lista invertida.
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

//Nessa fun��o ocorre todo o processo de inserir as palavras de um arquivo no �ndice invertido.
void FuncaoInserirArquivo(char nomearquivo[]){
    principal *p; //Este seria o n� inicial da lista encadeada, p de ponteiro.
    p=(principal*)malloc(sizeof(principal));
    p=NULL;
    /*O programa ler� o �ndice invertido que est� armazenado (se tiver) e vai inserir todos os valores contidos
    nele em uma lista encadeada, em seguida, ler� o arquivo que o usu�rio informou, incrementando a lista
    encadeada existente com as palavras dele. Por �ltimo, o programa substituir� o �ndice invertido anterior
    pelo "novo".*/
    p=Carregar_Lista(p); //Lendo o �ndice invertido
    p=Gerar_Lista(p, nomearquivo); //Lendo o arquivo informado pelo usu�rio
    if (p==NULL){
        MensagemDeErro(2);
        return;
    }
    SalvarLista(p); //Substituindo o indice invertido anterior.
}

//Essa fun��o l� os valores do �ndice invertido e os insere na lista encadeada do programa.
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

//Recebe uma palavra e a quantidade de arquivos ela aparece e p�e esses valores em um n� da lista encadeada principal.
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

//Recebe um arquivo e a quantidade de vezes que a palavra aparece nele e insere esses valores em um n� de arquivo dentro do n� principal da palavra em quest�o.
principal* InsereNaLista_1_2(principal *p, int quantidade, char nomearquivo[]){
    arquivo *aux;
    aux=(arquivo*)malloc(sizeof(arquivo));
    strcpy(aux->nomearquivo, nomearquivo);
    aux->quantidade=quantidade;
    aux->proximo=p->arquivo;
    p->arquivo=aux;
    return p;
}

//Incrementa a lista encadeada com as palavras do arquivo novo que o usu�rio informou.
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

//Essa fun��o remove v�rgula, ponto ou ponto e v�rgula caso um desses seja o ultimo caractere da palavra.
void RemovePontuacao(char palavra[]){
    int ultimoindice;
    ultimoindice = (strlen(palavra)-1);
    if (palavra[ultimoindice]==',' || palavra[ultimoindice]=='.' || palavra[ultimoindice]==';'){
        palavra[ultimoindice]='\0';
    }
}

//Essa fun��o recebe uma palavra, verifica se ela j� est� presente na lista principal, retorna 0 pra n�o e 1 pra sim
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

//Caso no arquivo que o usuario inseriu tenha uma palavra que j� esteja na lista encadeada principal, essa fun��o ir� analisar se j� existe um n� de arquivo do mesmo arquivo que est� sendo analisado, se sim, ela apenas soma a quantidade, se n�o, ela cria esse n�.
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

//Essa fun��o cria um n� na lista principal.
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

//Essa fun��o cont�m processo de "salvar" a lista encadeada em um arquivo txt, de forma que o programa possa l�-lo novamente e capturar os valores.
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

//Essa fun��o exclui o arquivo listainvertida.txt
void DeletaListaInvertida(void){
    int flag = remove("listainvertida.txt");
    if(flag == 0){
        printf("A lista invertida foi deletada com sucesso.");
    }else{
        MensagemDeErro(3);
   }
}

//Essa fun��o busca uma palavra no arquivo listainvertida.txt, e retorna todos os arquivos em que ela aparece, e quantas vezes aparece em cada um.
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
