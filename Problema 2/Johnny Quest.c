/*******************************************************************************
Autor: Johnny Quest Dantas Pereira
Componente Curricular: Algoritmos I
Concluido em: 25/11/2017
Declaro que este código foi elaborado por mim de forma individual e não contém nenhum
trecho de código de outro colega ou de outro autor, tais como provindos de livros e
apostilas, e páginas ou documentos eletrônicos da Internet. Qualquer trecho de código
de outra autoria que não a minha está destacado com uma citação para o autor e a fonte
do código, e estou ciente que estes trechos não serão considerados para fins de avaliação.
******************************************************************************************/

//Bibliotecas//
#include <stdio.h> //Biblioteca de entrada e saída padrão, para utilizar funções como printf, scanf, etc.
#include <string.h> //Biblioteca para manipulação de vetores de caracteres(strings)
#include <stdlib.h> //Biblioteca utilizada para a função system("cls")
#include <locale.h> //Biblioteca utilizada para localizar o programa na língua portuguesa e poder printar mensagens com caracteres especiais

//Definição da Struct que armazena os dados de uma proposta//
struct cadastro{
    char titulo[100]; //string que armazena o título da proposta.
    int hora; //essa variável irá armazenar o horário da apresentação
    int tipo; //essa variável armazena um número de 1 a 4 que representa, respectivamente: Oral, Oficina, Pôster, Laboratório.
    char proponentes[5][80]; //matriz de strings que armazena os nomes dos proponentes
    int quantidade_de_proponentes; //armazena a quantidade de proponentes da proposta
    int temprof; //armazena 0 ou 1, responde a pergunta "Tem algum professor nessa proposta?" 1 para sim e 0 para não.
};

//Protótipos das funções usadas no programa//
int Pergunta_Inicial(void); //Função que pergunta ao usuário a quantidade de cursos que participarão da feira.
void Limpa_Tela(int dia); //Função que "limpa" as mensagens da tela, printa o título do programa e mostra em qual data o usuário está cadastrando naquele momento
void Usuario_Digita_Os_Cursos_Da_Feira(int numcursos, char cursos[50][60]); //Essa função é executada apenas uma vez, nela o usuário digita um por um os cursos que participarão da feira
int Usuario_Escolhe_Curso_entre_as_Opcoes(int numcursos, char cursos[50][60]); //Função "menu principal", o usuário escolhe um entre os cursos disponíveis para realizar um cadastro nele.
int Pega_Hora(int horasdisponiveis[50][12][2], int escolhacurso, int dia); //Essa função é executada dentro da função Cadastro_De_Proposta, é basicamente uma rotina de escolher o horário da apresentação e bloquear que duas propostas do mesmo curso aconteçam no mesmo horário.
int Pega_Tipo(int contadordetipos[2][4], int dia); //Essa função também é executada dentro da Cadastro_de_Proposta, ela simplesmente solicita o tipo de proposta ao usuário e soma num contador de tipos que será utilizado no final do programa, ao mostras quantas propostas de cada tipo foram cadastradas.
void Cadastro_de_Proposta(char cursos[50][60], int indice, int escolhacurso, struct cadastro propostas[50][10][2], int dia, int horasdisponiveis[50][12][2], int contadordetipos[2][4]); //A função que realiza o procedimento de cadastro de uma proposta.
void Solicitar_Nome_do_Arquivo(char nomedoarquivo[60]); //Função que solicita ao usuário que ele digite um nome pro arquivo texto e concatena essa string com ".txt"
void Ordena_Propostas(struct cadastro propostas[50][10][2], int numcursos, int quantpropostas[2][50]);
void Funcao_Arquivo_Texto_1(int numcursos, int quantpropostas[2][50], char cursos[50][60], struct cadastro propostas[50][10][2], char nomedoarquivo[60]); //Função que printa todas as propostas no arquivo .txt
void Funcao_Arquivo_Texto_2(int contadordetipos[2][4], char nomedoarquivo[60]); //Função que printa no arquivo texto quantas apresentações de cada tipo acontecerão em cada um dos dias
void Funcao_Arquivo_Texto_3(int quantpropostas[2][50], char cursos[50][60], char nomedoarquivo[60], int numcursos); //Função que printa no arquivo .txt o(s) cursos com maior representatividade
void Funcao_Arquivo_Texto_4(int quantpropostas[2][50], char cursos[50][60], char nomedoarquivo[60], int numcursos); //Função que printa no arquivo .txt o(s) cursos com menor representatividade
void Funcao_Arquivo_Texto_5(struct cadastro propostas[50][10][2], char cursos[50][60], int quantpropostas[2][50], char nomedoarquivo[60], int numcursos); //Função que printa no arquivo .txt uma lista com todas as propostas que contém apenas estudantes

////////////Função Principal (main)////////////
int main(){
    //Localização do programa//
    setlocale(LC_ALL, "Portuguese"); //Definindo a localização de todo o programa para língua portuguesa, possibilitando que mensagens com caracteres especiais (ç, acentos) sejam printadas sem precisar da tabela ASCII.

    //Declaração de Variáveis//
    int cadastrando=0, escolhendocurso=1, i=0; //Variáveis utilizadas em laços de repetição while e do-while.
    int escolhacurso; //Essa variável armazena o valor que o usuário digitar quando for "escolher" o curso que deseja cadastrar
    int numcursos; //Variável que armazena a quantidade de cursos que serão cadastrados.
    int dia=0; //0 representa o dia 23 e 1 representa o dia 24.

    //Declaração dos vetores e matrizes//
    char cursos[50][60]; //Matriz de strings que armazena os nomes dos cursos.
    char nomedoarquivo[60]; //String que armazena o nome do arquivo texto que o usuário irá digitar
    struct cadastro propostas[50][10][2]; //Matriz de structs, cada "linha" corresponde a um curso, e as "colunas" representam as propostas de cada curso.
    int quantpropostas[2][50]; //Esse vetor faz a "contagem" de quantas propostas foram feitas por curso, cada índice representa um curso, é usada ao printar no arquivos texto, para saber quantas vezes repetir o laço.
    int limitepropostas[50]; //Esse vetor também faz contagem de propostas por curso, porém esse é usado para limitar os cadastros (máximo 10 por curso), então não tem uma linha pra cada dia, diferente do anterior.
    int horasdisponiveis[50][12][2]; //Vetor que irá armazenar 0 e 1 em seus indices, indicando a disponibilidade de cada horário (cada índice representa uma hora no intervalo 8h ~ 20h)
    int contadordetipos[2][4]; //Matriz de contadores, cada linha corresponde a um dia e cada coluna corresponde a um tipo, cada cadastro realizado soma 1

    //Funções que são executadas apenas uma vez//
    numcursos=Pergunta_Inicial(); //Solicitação da quantidade de cursos que participarão da feira
    Usuario_Digita_Os_Cursos_Da_Feira(numcursos, cursos); //Processo de entrada dos cursos que participarão da Feira e ordenação deles em ordem alfabética.

    //Rotina de cadastros//
    do{ //Esse laço se repete duas vezes, uma para cada dia.
        Limpa_Tela(dia); //"Limpa" as informações na tela, printa o título do programa e mostra em qual data o usuário está cadastrando naquele momento
            do{ //Esse laço corresponde ao "menu principal" do programa, "acontece" sempre que o usuário vai escolher um curso para realizar cadastros.
                escolhacurso=Usuario_Escolhe_Curso_entre_as_Opcoes(numcursos, cursos); //Chama uma função que apresenta na tela os cursos disponíveis, pede para o usuário escolher qual ele deseja cadastrar e retorna essa escolha, representada por um número inteiro;
                Limpa_Tela(dia); //"Limpa" as informações na tela, printa o título do programa e mostra em qual data o usuário está cadastrando naquele momento
                cadastrando=1; //Faz com que o laço de repetição abaixo "inicie":
                while(cadastrando==1){ //Aqui o usuário irá cadastrar todas as propostas do curso que ele escolheu.
                    if (limitepropostas[(escolhacurso-1)] >= 10){ //Condicional que impossibilita o usuário de cadastrar mais de 10 propostas num curso.
                        printf("\nERRO: Você já atingiu o limite de propostas (10) para esse curso!\n");
                        system("pause");
                        cadastrando=2; //Quebra o laço de cadastro, para que o programa retorne ao menu de escolha de cursos.
                        Limpa_Tela(dia); //"Limpa" as informações na tela, printa o título do programa e mostra em qual data o usuário está cadastrando naquele momento
                    }else{
                        Cadastro_de_Proposta(cursos, quantpropostas[dia][escolhacurso-1], escolhacurso, propostas, dia, horasdisponiveis, contadordetipos); //Nessa função, o usuário entra todos os valores necessários para preencher uma proposta

                        do{ //Menu de escolhas pós cadastro, com tratamento de erro para números menores que 1 ou maiores que 4.
                            printf("O que deseja agora? \n\t[1] Fazer outro cadastro em %s", cursos[escolhacurso-1]); //Após o cadastro, o usuário recebe essas 3 opções
                            printf("\n\t[2] Escolher outro curso\n\t[3] Finalizar cadastros do dia ");
                            if (dia==0)
                                printf("23/10 e iniciar os do dia 24/10");
                            else
                                printf("24/10 e finalizar o programa");
                            printf("\n\t[4] Interromper o cadastro e encerrar o programa (OBS. todas as informações serão perdidas!)\n->");
                            scanf("%i", &cadastrando); //Caso escolha 1, o laço se repete e o usuário irá cadastrar mais uma proposta nesse curso. Caso 2, esse laço (que depende que o valor de "cadastrando" seja 1) se quebra e o usuário retorna para o "menu principal", e caso escolha 3, ele passa a repetir todo o processo, porém cadastrando as propostas do segundo dia (24)
                            if(cadastrando>4 || cadastrando<1)
                                printf("ERRO: Comando inválido.\n");
                            else
                                i++;
                        }while(i==0);

                        quantpropostas[dia][escolhacurso-1]++; //Soma 1 na quantidade de propostas do curso no dia
                        limitepropostas[escolhacurso-1]++; //Soma 1 na quantidade de propostas do curso em geral
                        if (cadastrando==3){
                            escolhendocurso=0; //"quebra" o laço do menu principal
                            dia++; //Informa que o usuário terminou de cadastrar todos os cursos do dia que ele estava cadastrando.
                        }
                        else if (cadastrando==4)
                            return 0;
                        else
                            Limpa_Tela(dia); //"Limpa" as informações na tela, printa o título do programa e mostra em qual data o usuário está cadastrando naquele momento
                    }
                }
            }while(escolhendocurso==1);
    }while(dia<=1); //Quando dia for maior que 1, significa que o usuário já escolheu a opção 3 duas vezes, que significa que ele já cadastrou as propostas dos 2 dias, finalizando o laço.

    //Agora, após adquirir todos os dados necessários, o programa irá imprimir essas informações no arquivo texto, de forma organizada.//
    Solicitar_Nome_do_Arquivo(nomedoarquivo); //Função que solicita ao usuário que ele digite um nome pro arquivo texto e concatena essa string com ".txt"
    Ordena_Propostas(propostas, numcursos, quantpropostas); //Função que ordena as propostas por horário.
    Funcao_Arquivo_Texto_1(numcursos, quantpropostas, cursos, propostas, nomedoarquivo); //Função que printa todas as propostas no arquivo .txt
    Funcao_Arquivo_Texto_2(contadordetipos, nomedoarquivo); //Função que printa no arquivo texto quantas apresentações de cada tipo acontecerão em cada um dos dias
    Funcao_Arquivo_Texto_3(quantpropostas, cursos, nomedoarquivo, numcursos); //Função que printa no arquivo .txt o(s) cursos com maior representatividade
    Funcao_Arquivo_Texto_4(quantpropostas, cursos, nomedoarquivo, numcursos); //Função que printa no arquivo .txt o(s) cursos com menor representatividade
    Funcao_Arquivo_Texto_5(propostas, cursos, quantpropostas, nomedoarquivo, numcursos); //Função que printa no arquivo .txt uma lista com todas as propostas que contém apenas estudantes

    //E então, o programa encerra.//
    printf("Programa finalizado, arquivo salvo com sucesso!\n");
    return 0;
}

//Função que pergunta ao usuário a quantidade de cursos que participarão da feira.
int Pergunta_Inicial(void){
    int numcursos;
    printf("Quantos cursos participarão da feira? \n-> ");
    scanf("%i", &numcursos);
    return numcursos;
}

//Função que "limpa" as mensagens da tela, printa o título do programa e mostra em qual data o usuário está cadastrando naquele momento
void Limpa_Tela(int dia){
    system("cls");
    printf("##################################################\n");
    printf("\t     FEIRA DE GRADUAÇÃO UEFS\n");
    printf("\t Sistema de Cadastro de Propostas\n");
    printf("(Você está realizando cadastros do dia %i/10/2017)\n", dia+23); //dia sempre será 0 ou 1, portanto na data sempre será printado 23 ou 24.
    printf("##################################################\n\n");
}

//Essa função é executada apenas uma vez, nela o usuário digita um por um os cursos que participarão da feira
void Usuario_Digita_Os_Cursos_Da_Feira(int numcursos, char cursos[50][60]){
    int i, j;
    char aux[60];
    printf("(Por favor, não use acentos ou 'ç' nesse programa.)\n");
    for (i=0; i<numcursos; i++){
        fflush(stdin); //limpa o buffer do teclado para impedir que o gets "pegue" um caractere que não deva (um enter, por exemplo)
        printf("%iº Curso: ", i+1);
        gets(cursos[i]);
    }
    //Agora, essa matriz de strings será reordenada em ordem alfabética utilizando o método de ordenação Bubble Sort:
    for (i=0; i<(numcursos-1); i++){
        for (j=0; j<(numcursos-1); j++){
            if (strcasecmp(cursos[j+1], cursos[j]) < 0){
                strcpy(aux, cursos[j]);
                strcpy(cursos[j], cursos[j+1]);
                strcpy(cursos[j+1], aux);
            }
        }
    }
}

//Função "menu principal", o usuário escolhe um entre os cursos disponíveis para realizar um cadastro nele.
int Usuario_Escolhe_Curso_entre_as_Opcoes(int numcursos, char cursos[50][60]){
    int i, escolhacurso;
    printf("Escolha um curso para realizar um cadastro:\n");
        for (i=0; i<numcursos; i++){ //Esse laço printa na tela todos os cursos disponíveis com um número correspondente ao lado. Ex: "[1] Engenharia"
            printf("\t[%i] ", i+1);
            puts(cursos[i]);
        }
        scanf("%i", &escolhacurso); //O usuário digita o número correspondente ao curso que ele deseja cadastrar uma proposta
        return escolhacurso;
}

//A função que realiza o procedimento de cadastro de uma proposta.
void Cadastro_de_Proposta(char cursos[50][60], int indice, int escolhacurso, struct cadastro propostas[50][10][2], int dia, int horasdisponiveis[50][12][2], int contadordetipos[2][4]){
    int i, j=0, prof_ou_alun;
    printf("Curso: %s\n", cursos[escolhacurso-1]);
    printf("\tNome da proposta: ");
    fflush(stdin); //limpa o buffer do teclado para impedir que o gets "pegue" um caractere que não deva (um enter, por exemplo). OBS. Funciona apenas em Windows.
    gets(propostas[escolhacurso-1][indice][dia].titulo); //Pega o título da proposta e armazena na matriz de struct das propostas, com a coluna e profundidade recebidas pela função, e a linha será o curso que o usuário escolheu-1, porque na matriz, o primeiro indice é 0, mas no menu, no primeiro curso é dado a opção [1]
    propostas[escolhacurso-1][indice][dia].hora=Pega_Hora(horasdisponiveis, escolhacurso, dia); //Chama outra função pra pegar a hora
    propostas[escolhacurso-1][indice][dia].tipo=Pega_Tipo(contadordetipos, dia); //Chama outra função pra pegar o tipo da proposta

    //Pergunta ao usuário quantos proponentes a proposta terá, impedindo-o de inserir mais que 5 ou de cadastrar uma proposta sem proponentes.//
    do{
        printf("\tQuantidade de proponentes: ");
        scanf("%i", &propostas[escolhacurso-1][indice][dia].quantidade_de_proponentes); //é perguntado a quantidade de proponentes para saber quantas vezes o laço abaixo deve se repetir
        if (propostas[escolhacurso-1][indice][dia].quantidade_de_proponentes > 5 || propostas[escolhacurso-1][indice][dia].quantidade_de_proponentes < 1)
            printf("ERRO: A quantidade de proponentes precisa ser um número de 1 a 5.\n");
        else
            j++;
    }while(j==0);

    propostas[escolhacurso][indice][dia].temprof=0; //temprof inicia-se como 0, supõe-se de início que a proposta não tem professores, caso o usuário cadastre algum professor, esse valor muda para 1
    for (i=0; i<propostas[escolhacurso-1][indice][dia].quantidade_de_proponentes; i++){
        fflush(stdin); //limpando o buffer do teclado novamente
        printf("\t\tNome do %iº proponente:", i+1);
        gets(propostas[escolhacurso-1][indice][dia].proponentes[i]); //Pede o nome do proponente e armazena na matriz de struct

        //Pergunta ao usuário se o proponente x é aluno ou professor, com tratamento de erro caso ele digite um número inválido.//
        do{
            printf("\t\t[1]Aluno ou [2]Professor: ");
            scanf("%i", &prof_ou_alun);
            if (prof_ou_alun>2 || prof_ou_alun<1)
                printf("ERRO: Digite um valor válido.\n");
            else
                j++;
        }while(j==1);

        if (prof_ou_alun == 2){
            propostas[escolhacurso-1][indice][dia].temprof=1; //Se houver algum professor, esse valor muda pra 1, futuramente quando for apresentar os cursos que só tem estudantes, eu só irei printar os cursos que essa variável é igual a zero
            strcat(propostas[escolhacurso-1][indice][dia].proponentes[i], " (Professor)"); //Concatena o nome do proponente com o que ele é, por exemplo: "João (Aluno); José (Professor)"
        }else
            strcat(propostas[escolhacurso-1][indice][dia].proponentes[i], " (Aluno)");
        }
    Limpa_Tela(dia);
    printf("Cadastro concluído.\n");
}

//Essa função é executada dentro da função Cadastro_De_Proposta, é basicamente uma rotina de escolher o horário da apresentação e bloquear que duas propostas do mesmo curso aconteçam no mesmo horário.
int Pega_Hora(int horasdisponiveis[50][12][2], int escolhacurso, int dia){
    int i, valorhora, k=0, horafinal;
    //Esse sistema de disponibilidade de horário funciona da seguinte forma: todos os horários iniciam com seu indice correspondente igual a zero, sempre que o usuário escolher uma hora, ele verifica se o índice correspondente a ele é igual a 0 ou 1
    //Se for 1, ele não permite o cadastro, se for 0, ele permite o cadastro e modifica esse indice pra 1
    do{
        printf("Escolha um horario para a apresentação:");
        for (i=0; i<12; i++){
            printf("\n\t[%i] %ih", i+1, i+8);
            if (horasdisponiveis[escolhacurso][i][dia]==1)
                printf (" (já utilizado)");
        }
        printf("\n-> ");
        scanf("%i", &valorhora);
        if (horasdisponiveis[escolhacurso][(valorhora-1)][dia]==1)
            printf("\nERRO: Esse horário já está sendo utilizado em uma apresentação desse curso, por favor escolha outro.\n");
        else if (valorhora<1 || valorhora>12)
            printf("\nERRO: Comando inválido.\n");
        else{
            horasdisponiveis[escolhacurso][(valorhora-1)][dia]=1;
            k=1;
        }
    }while(k==0);
    horafinal = valorhora+7; //Por fim, a hora que será retornada será o valor q o usuario digitou somado com 7, pois [1] representa 8h, [2] representa 9h e assim por diante.
    return horafinal;
}

//Essa função também é executada dentro da Cadastro_de_Proposta, ela simplesmente solicita o tipo de proposta ao usuário e soma num contador de tipos que será utilizado no final do programa, ao mostras quantas propostas de cada tipo foram cadastradas.
int Pega_Tipo(int contadordetipos[2][4], int dia){
    int tipo, i=0;
    while (i==0){
        printf("Escolha um tipo de apresentação:\n");
        printf("\t[1] Oral\t[2] Oficina\n\t[3] Pôster\t[4] Laboratório\n->");
        scanf("%i", &tipo);
        if(tipo>4 || tipo<1) //Solicita um número, executa tratamento de erro caso o usuario digite um numero menor que 1 ou maior que 4, caso não, retorna esse numero.
            printf("\nERRO: Comando inválido.\n");
        else{
            contadordetipos[dia][(tipo-1)]++;
            i++;
        }
    }
    return tipo;
}

//Função que solicita ao usuário que ele digite um nome pro arquivo texto e concatena essa string com ".txt"
void Solicitar_Nome_do_Arquivo(char nomedoarquivo[60]){
    printf("Seu relatório será salvo em um arquivo de texto!\nNome do arquivo: ");
    fflush(stdin);
    gets (nomedoarquivo);
    strcat(nomedoarquivo, ".txt");
}

//Função que ordena as propostas do menor horário para o maior, utilizando o algoritmo de ordenação Bubble Sort
void Ordena_Propostas(struct cadastro propostas[50][10][2], int numcursos, int quantpropostas[2][50]){
    struct cadastro aux;
    int i, j, h, k;
    for (h=0; h<2; h++){
        for (i=0; i<numcursos; i++){
            //A partir desse ponto começa o Bubble Sort, os dois laços anteriores garantem que todos os cursos sejam ordenadas, de ambos os dias//
            for (j=0; j<quantpropostas[h][i]; j++){
                for (k=0; k<(quantpropostas[h][i] -1); k++){
                    if (propostas[i][k+1][h].hora < propostas[i][k][h].hora){
                        aux = propostas[i][k][h];
                        propostas[i][k][h] = propostas[i][k+1][h];
                        propostas[i][k+1][h] = aux;
                    }
                }
            }
        }
    }
}

//Função que printa todas as propostas no arquivo .txt
void Funcao_Arquivo_Texto_1(int numcursos, int quantpropostas[2][50], char cursos[50][60], struct cadastro propostas[50][10][2], char nomedoarquivo[60]){
    int i, j, k;
    int dia;
    FILE *file;
    file = fopen(nomedoarquivo, "w");
    fprintf(file, "\n################## PROPOSTAS CADASTRADAS ##################\n");
    for (dia=0; dia<=1; dia++){ //Nessa rotina, o programa printa "DIA 23/10" e todas as propostas desse dia abaixo, em seguida, printa "24/10" e todas as propostas desse dia abaixo
        if (dia==0)
            fprintf(file, "DIA 23/10:");
        else
            fprintf(file, "\nDIA 24/10:");
        for (i=0; i<numcursos; i++){
            fprintf(file, "\n\tCURSO: %s", cursos[i]);
            for (j=0; j<quantpropostas[dia][i]; j++){
                fprintf(file, "\n\t\tProposta: %s", propostas[i][j][dia].titulo);
                fprintf(file, "\n\t\t\tHorário: %ih", propostas[i][j][dia].hora);
                fprintf(file, "\n\t\t\tTipo: %i", propostas[i][j][dia].tipo);
                fprintf(file, "\n\t\t\tLista de Proponentes:");
                for (k=0; k<propostas[i][j][dia].quantidade_de_proponentes; k++){
                        fprintf(file, "\n\t\t\t\t-%s", propostas[i][j][dia].proponentes[k]);
                }
            }
        }
    }
    fclose(file); //fecha o arquivo com segurança
}

//Função que printa no arquivo texto quantas apresentações de cada tipo acontecerão em cada um dos dias
void Funcao_Arquivo_Texto_2(int contadordetipos[2][4], char nomedoarquivo[60]){
    int i, j;
    FILE *file;
    file = fopen(nomedoarquivo, "a");
    fprintf(file, "\n\n################## INFORMAÇÕES ADICIONAIS ##################\n");
    for (i=0; i<2; i++){
        fprintf(file, "No dia %i/10, estão cadastradas:\n\t", i+23);
        for (j=0; j<4; j++){
            fprintf(file, "%i apresentações do tipo ", contadordetipos[i][j]); //Essa função basicamente printa os valores do contadordetipos.
            if (j==0)
                fprintf(file, "ORAL;\n\t");
            else if (j==1)
                fprintf(file, "OFICINA;\n\t");
            else if (j==2)
                fprintf(file, "PÔSTER;\n\t");
            else if (j==3)
                fprintf(file, "LABORATÓRIO;\n");
        }
    }
    fclose(file);
}

//Função que printa no arquivo .txt o(s) cursos com maior representatividade
void Funcao_Arquivo_Texto_3(int quantpropostas[2][50], char cursos[50][60], char nomedoarquivo[60], int numcursos){
    FILE *file;
    file = fopen(nomedoarquivo, "a");
    int maior, i;
    //Verificando qual é a maior quantidade de propostas//
    maior = quantpropostas[0][0]+quantpropostas[1][0];
    for (i=0; i<numcursos; i++){
        if ((quantpropostas[0][i]+quantpropostas[1][i]) > maior)
            maior = quantpropostas[0][i]+quantpropostas[1][i];
    }
    //Printando todos os cursos que tem uma quantidade de propostas igual a maior//
    fprintf(file, "\nCurso(s) com maior representatividade:\n");
    for (i=0; i<numcursos; i++){
        if ((quantpropostas[0][i]+quantpropostas[1][i]) == maior){
            fprintf(file, "\t%s (%i propostas)", cursos[i], maior);
        }
    }
    fclose(file);
}

//Função que printa no arquivo .txt o(s) cursos com menor representatividade
void Funcao_Arquivo_Texto_4(int quantpropostas[2][50], char cursos[50][60], char nomedoarquivo[60], int numcursos){
    FILE *file;
    file = fopen(nomedoarquivo, "a");
    int menor, i;
    //Verificando qual é a menor quantidade de propostas//
    menor = quantpropostas[0][0]+quantpropostas[1][0];
    for (i=0; i<numcursos; i++){
        if ((quantpropostas[0][i]+quantpropostas[1][i]) < menor)
            menor = quantpropostas[0][i]+quantpropostas[1][i];
    }
    //Printando todos os cursos que tem uma quantidade de propostas igual a menor//
    fprintf(file, "\nCurso(s) com menor representatividade:\n");
    for (i=0; i<numcursos; i++){
        if ((quantpropostas[0][i]+quantpropostas[1][i]) == menor){
            fprintf(file, "\t%s (%i propostas)", cursos[i], menor);
        }
    }
    fclose(file);
}

//Função que printa no arquivo .txt uma lista com todas as propostas que contém apenas estudantes.
void Funcao_Arquivo_Texto_5(struct cadastro propostas[50][10][2], char cursos[50][60], int quantpropostas[2][50], char nomedoarquivo[60], int numcursos){
    FILE *file;
    file = fopen(nomedoarquivo, "a");
    int dia, curso, proposta;
    fprintf(file, "\n\n################## PROPOSTAS OFERTADAS APENAS POR ALUNOS ##################:");
    for(dia=0; dia<2; dia++){
        for (curso=0; curso<numcursos; curso++){
            for (proposta=0; proposta<quantpropostas[dia][curso]; proposta++){
                if (propostas[curso][proposta][dia].temprof==0)
                    fprintf(file, "\n\t-%s, do curso %s", propostas[curso][proposta][dia].titulo, cursos[curso]); //Analisa curso por curso se temprof é 0 ou 1, se for 0 (não tem professor), então ele printa esse curso.
            }
        }
    }
    fclose(file);
}
