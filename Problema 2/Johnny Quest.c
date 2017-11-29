/*******************************************************************************
Autor: Johnny Quest Dantas Pereira
Componente Curricular: Algoritmos I
Concluido em: 25/11/2017
Declaro que este c�digo foi elaborado por mim de forma individual e n�o cont�m nenhum
trecho de c�digo de outro colega ou de outro autor, tais como provindos de livros e
apostilas, e p�ginas ou documentos eletr�nicos da Internet. Qualquer trecho de c�digo
de outra autoria que n�o a minha est� destacado com uma cita��o para o autor e a fonte
do c�digo, e estou ciente que estes trechos n�o ser�o considerados para fins de avalia��o.
******************************************************************************************/

//Bibliotecas//
#include <stdio.h> //Biblioteca de entrada e sa�da padr�o, para utilizar fun��es como printf, scanf, etc.
#include <string.h> //Biblioteca para manipula��o de vetores de caracteres(strings)
#include <stdlib.h> //Biblioteca utilizada para a fun��o system("cls")
#include <locale.h> //Biblioteca utilizada para localizar o programa na l�ngua portuguesa e poder printar mensagens com caracteres especiais

//Defini��o da Struct que armazena os dados de uma proposta//
struct cadastro{
    char titulo[100]; //string que armazena o t�tulo da proposta.
    int hora; //essa vari�vel ir� armazenar o hor�rio da apresenta��o
    int tipo; //essa vari�vel armazena um n�mero de 1 a 4 que representa, respectivamente: Oral, Oficina, P�ster, Laborat�rio.
    char proponentes[5][80]; //matriz de strings que armazena os nomes dos proponentes
    int quantidade_de_proponentes; //armazena a quantidade de proponentes da proposta
    int temprof; //armazena 0 ou 1, responde a pergunta "Tem algum professor nessa proposta?" 1 para sim e 0 para n�o.
};

//Prot�tipos das fun��es usadas no programa//
int Pergunta_Inicial(void); //Fun��o que pergunta ao usu�rio a quantidade de cursos que participar�o da feira.
void Limpa_Tela(int dia); //Fun��o que "limpa" as mensagens da tela, printa o t�tulo do programa e mostra em qual data o usu�rio est� cadastrando naquele momento
void Usuario_Digita_Os_Cursos_Da_Feira(int numcursos, char cursos[50][60]); //Essa fun��o � executada apenas uma vez, nela o usu�rio digita um por um os cursos que participar�o da feira
int Usuario_Escolhe_Curso_entre_as_Opcoes(int numcursos, char cursos[50][60]); //Fun��o "menu principal", o usu�rio escolhe um entre os cursos dispon�veis para realizar um cadastro nele.
int Pega_Hora(int horasdisponiveis[50][12][2], int escolhacurso, int dia); //Essa fun��o � executada dentro da fun��o Cadastro_De_Proposta, � basicamente uma rotina de escolher o hor�rio da apresenta��o e bloquear que duas propostas do mesmo curso aconte�am no mesmo hor�rio.
int Pega_Tipo(int contadordetipos[2][4], int dia); //Essa fun��o tamb�m � executada dentro da Cadastro_de_Proposta, ela simplesmente solicita o tipo de proposta ao usu�rio e soma num contador de tipos que ser� utilizado no final do programa, ao mostras quantas propostas de cada tipo foram cadastradas.
void Cadastro_de_Proposta(char cursos[50][60], int indice, int escolhacurso, struct cadastro propostas[50][10][2], int dia, int horasdisponiveis[50][12][2], int contadordetipos[2][4]); //A fun��o que realiza o procedimento de cadastro de uma proposta.
void Solicitar_Nome_do_Arquivo(char nomedoarquivo[60]); //Fun��o que solicita ao usu�rio que ele digite um nome pro arquivo texto e concatena essa string com ".txt"
void Ordena_Propostas(struct cadastro propostas[50][10][2], int numcursos, int quantpropostas[2][50]);
void Funcao_Arquivo_Texto_1(int numcursos, int quantpropostas[2][50], char cursos[50][60], struct cadastro propostas[50][10][2], char nomedoarquivo[60]); //Fun��o que printa todas as propostas no arquivo .txt
void Funcao_Arquivo_Texto_2(int contadordetipos[2][4], char nomedoarquivo[60]); //Fun��o que printa no arquivo texto quantas apresenta��es de cada tipo acontecer�o em cada um dos dias
void Funcao_Arquivo_Texto_3(int quantpropostas[2][50], char cursos[50][60], char nomedoarquivo[60], int numcursos); //Fun��o que printa no arquivo .txt o(s) cursos com maior representatividade
void Funcao_Arquivo_Texto_4(int quantpropostas[2][50], char cursos[50][60], char nomedoarquivo[60], int numcursos); //Fun��o que printa no arquivo .txt o(s) cursos com menor representatividade
void Funcao_Arquivo_Texto_5(struct cadastro propostas[50][10][2], char cursos[50][60], int quantpropostas[2][50], char nomedoarquivo[60], int numcursos); //Fun��o que printa no arquivo .txt uma lista com todas as propostas que cont�m apenas estudantes

////////////Fun��o Principal (main)////////////
int main(){
    //Localiza��o do programa//
    setlocale(LC_ALL, "Portuguese"); //Definindo a localiza��o de todo o programa para l�ngua portuguesa, possibilitando que mensagens com caracteres especiais (�, acentos) sejam printadas sem precisar da tabela ASCII.

    //Declara��o de Vari�veis//
    int cadastrando=0, escolhendocurso=1, i=0; //Vari�veis utilizadas em la�os de repeti��o while e do-while.
    int escolhacurso; //Essa vari�vel armazena o valor que o usu�rio digitar quando for "escolher" o curso que deseja cadastrar
    int numcursos; //Vari�vel que armazena a quantidade de cursos que ser�o cadastrados.
    int dia=0; //0 representa o dia 23 e 1 representa o dia 24.

    //Declara��o dos vetores e matrizes//
    char cursos[50][60]; //Matriz de strings que armazena os nomes dos cursos.
    char nomedoarquivo[60]; //String que armazena o nome do arquivo texto que o usu�rio ir� digitar
    struct cadastro propostas[50][10][2]; //Matriz de structs, cada "linha" corresponde a um curso, e as "colunas" representam as propostas de cada curso.
    int quantpropostas[2][50]; //Esse vetor faz a "contagem" de quantas propostas foram feitas por curso, cada �ndice representa um curso, � usada ao printar no arquivos texto, para saber quantas vezes repetir o la�o.
    int limitepropostas[50]; //Esse vetor tamb�m faz contagem de propostas por curso, por�m esse � usado para limitar os cadastros (m�ximo 10 por curso), ent�o n�o tem uma linha pra cada dia, diferente do anterior.
    int horasdisponiveis[50][12][2]; //Vetor que ir� armazenar 0 e 1 em seus indices, indicando a disponibilidade de cada hor�rio (cada �ndice representa uma hora no intervalo 8h ~ 20h)
    int contadordetipos[2][4]; //Matriz de contadores, cada linha corresponde a um dia e cada coluna corresponde a um tipo, cada cadastro realizado soma 1

    //Fun��es que s�o executadas apenas uma vez//
    numcursos=Pergunta_Inicial(); //Solicita��o da quantidade de cursos que participar�o da feira
    Usuario_Digita_Os_Cursos_Da_Feira(numcursos, cursos); //Processo de entrada dos cursos que participar�o da Feira e ordena��o deles em ordem alfab�tica.

    //Rotina de cadastros//
    do{ //Esse la�o se repete duas vezes, uma para cada dia.
        Limpa_Tela(dia); //"Limpa" as informa��es na tela, printa o t�tulo do programa e mostra em qual data o usu�rio est� cadastrando naquele momento
            do{ //Esse la�o corresponde ao "menu principal" do programa, "acontece" sempre que o usu�rio vai escolher um curso para realizar cadastros.
                escolhacurso=Usuario_Escolhe_Curso_entre_as_Opcoes(numcursos, cursos); //Chama uma fun��o que apresenta na tela os cursos dispon�veis, pede para o usu�rio escolher qual ele deseja cadastrar e retorna essa escolha, representada por um n�mero inteiro;
                Limpa_Tela(dia); //"Limpa" as informa��es na tela, printa o t�tulo do programa e mostra em qual data o usu�rio est� cadastrando naquele momento
                cadastrando=1; //Faz com que o la�o de repeti��o abaixo "inicie":
                while(cadastrando==1){ //Aqui o usu�rio ir� cadastrar todas as propostas do curso que ele escolheu.
                    if (limitepropostas[(escolhacurso-1)] >= 10){ //Condicional que impossibilita o usu�rio de cadastrar mais de 10 propostas num curso.
                        printf("\nERRO: Voc� j� atingiu o limite de propostas (10) para esse curso!\n");
                        system("pause");
                        cadastrando=2; //Quebra o la�o de cadastro, para que o programa retorne ao menu de escolha de cursos.
                        Limpa_Tela(dia); //"Limpa" as informa��es na tela, printa o t�tulo do programa e mostra em qual data o usu�rio est� cadastrando naquele momento
                    }else{
                        Cadastro_de_Proposta(cursos, quantpropostas[dia][escolhacurso-1], escolhacurso, propostas, dia, horasdisponiveis, contadordetipos); //Nessa fun��o, o usu�rio entra todos os valores necess�rios para preencher uma proposta

                        do{ //Menu de escolhas p�s cadastro, com tratamento de erro para n�meros menores que 1 ou maiores que 4.
                            printf("O que deseja agora? \n\t[1] Fazer outro cadastro em %s", cursos[escolhacurso-1]); //Ap�s o cadastro, o usu�rio recebe essas 3 op��es
                            printf("\n\t[2] Escolher outro curso\n\t[3] Finalizar cadastros do dia ");
                            if (dia==0)
                                printf("23/10 e iniciar os do dia 24/10");
                            else
                                printf("24/10 e finalizar o programa");
                            printf("\n\t[4] Interromper o cadastro e encerrar o programa (OBS. todas as informa��es ser�o perdidas!)\n->");
                            scanf("%i", &cadastrando); //Caso escolha 1, o la�o se repete e o usu�rio ir� cadastrar mais uma proposta nesse curso. Caso 2, esse la�o (que depende que o valor de "cadastrando" seja 1) se quebra e o usu�rio retorna para o "menu principal", e caso escolha 3, ele passa a repetir todo o processo, por�m cadastrando as propostas do segundo dia (24)
                            if(cadastrando>4 || cadastrando<1)
                                printf("ERRO: Comando inv�lido.\n");
                            else
                                i++;
                        }while(i==0);

                        quantpropostas[dia][escolhacurso-1]++; //Soma 1 na quantidade de propostas do curso no dia
                        limitepropostas[escolhacurso-1]++; //Soma 1 na quantidade de propostas do curso em geral
                        if (cadastrando==3){
                            escolhendocurso=0; //"quebra" o la�o do menu principal
                            dia++; //Informa que o usu�rio terminou de cadastrar todos os cursos do dia que ele estava cadastrando.
                        }
                        else if (cadastrando==4)
                            return 0;
                        else
                            Limpa_Tela(dia); //"Limpa" as informa��es na tela, printa o t�tulo do programa e mostra em qual data o usu�rio est� cadastrando naquele momento
                    }
                }
            }while(escolhendocurso==1);
    }while(dia<=1); //Quando dia for maior que 1, significa que o usu�rio j� escolheu a op��o 3 duas vezes, que significa que ele j� cadastrou as propostas dos 2 dias, finalizando o la�o.

    //Agora, ap�s adquirir todos os dados necess�rios, o programa ir� imprimir essas informa��es no arquivo texto, de forma organizada.//
    Solicitar_Nome_do_Arquivo(nomedoarquivo); //Fun��o que solicita ao usu�rio que ele digite um nome pro arquivo texto e concatena essa string com ".txt"
    Ordena_Propostas(propostas, numcursos, quantpropostas); //Fun��o que ordena as propostas por hor�rio.
    Funcao_Arquivo_Texto_1(numcursos, quantpropostas, cursos, propostas, nomedoarquivo); //Fun��o que printa todas as propostas no arquivo .txt
    Funcao_Arquivo_Texto_2(contadordetipos, nomedoarquivo); //Fun��o que printa no arquivo texto quantas apresenta��es de cada tipo acontecer�o em cada um dos dias
    Funcao_Arquivo_Texto_3(quantpropostas, cursos, nomedoarquivo, numcursos); //Fun��o que printa no arquivo .txt o(s) cursos com maior representatividade
    Funcao_Arquivo_Texto_4(quantpropostas, cursos, nomedoarquivo, numcursos); //Fun��o que printa no arquivo .txt o(s) cursos com menor representatividade
    Funcao_Arquivo_Texto_5(propostas, cursos, quantpropostas, nomedoarquivo, numcursos); //Fun��o que printa no arquivo .txt uma lista com todas as propostas que cont�m apenas estudantes

    //E ent�o, o programa encerra.//
    printf("Programa finalizado, arquivo salvo com sucesso!\n");
    return 0;
}

//Fun��o que pergunta ao usu�rio a quantidade de cursos que participar�o da feira.
int Pergunta_Inicial(void){
    int numcursos;
    printf("Quantos cursos participar�o da feira? \n-> ");
    scanf("%i", &numcursos);
    return numcursos;
}

//Fun��o que "limpa" as mensagens da tela, printa o t�tulo do programa e mostra em qual data o usu�rio est� cadastrando naquele momento
void Limpa_Tela(int dia){
    system("cls");
    printf("##################################################\n");
    printf("\t     FEIRA DE GRADUA��O UEFS\n");
    printf("\t Sistema de Cadastro de Propostas\n");
    printf("(Voc� est� realizando cadastros do dia %i/10/2017)\n", dia+23); //dia sempre ser� 0 ou 1, portanto na data sempre ser� printado 23 ou 24.
    printf("##################################################\n\n");
}

//Essa fun��o � executada apenas uma vez, nela o usu�rio digita um por um os cursos que participar�o da feira
void Usuario_Digita_Os_Cursos_Da_Feira(int numcursos, char cursos[50][60]){
    int i, j;
    char aux[60];
    printf("(Por favor, n�o use acentos ou '�' nesse programa.)\n");
    for (i=0; i<numcursos; i++){
        fflush(stdin); //limpa o buffer do teclado para impedir que o gets "pegue" um caractere que n�o deva (um enter, por exemplo)
        printf("%i� Curso: ", i+1);
        gets(cursos[i]);
    }
    //Agora, essa matriz de strings ser� reordenada em ordem alfab�tica utilizando o m�todo de ordena��o Bubble Sort:
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

//Fun��o "menu principal", o usu�rio escolhe um entre os cursos dispon�veis para realizar um cadastro nele.
int Usuario_Escolhe_Curso_entre_as_Opcoes(int numcursos, char cursos[50][60]){
    int i, escolhacurso;
    printf("Escolha um curso para realizar um cadastro:\n");
        for (i=0; i<numcursos; i++){ //Esse la�o printa na tela todos os cursos dispon�veis com um n�mero correspondente ao lado. Ex: "[1] Engenharia"
            printf("\t[%i] ", i+1);
            puts(cursos[i]);
        }
        scanf("%i", &escolhacurso); //O usu�rio digita o n�mero correspondente ao curso que ele deseja cadastrar uma proposta
        return escolhacurso;
}

//A fun��o que realiza o procedimento de cadastro de uma proposta.
void Cadastro_de_Proposta(char cursos[50][60], int indice, int escolhacurso, struct cadastro propostas[50][10][2], int dia, int horasdisponiveis[50][12][2], int contadordetipos[2][4]){
    int i, j=0, prof_ou_alun;
    printf("Curso: %s\n", cursos[escolhacurso-1]);
    printf("\tNome da proposta: ");
    fflush(stdin); //limpa o buffer do teclado para impedir que o gets "pegue" um caractere que n�o deva (um enter, por exemplo). OBS. Funciona apenas em Windows.
    gets(propostas[escolhacurso-1][indice][dia].titulo); //Pega o t�tulo da proposta e armazena na matriz de struct das propostas, com a coluna e profundidade recebidas pela fun��o, e a linha ser� o curso que o usu�rio escolheu-1, porque na matriz, o primeiro indice � 0, mas no menu, no primeiro curso � dado a op��o [1]
    propostas[escolhacurso-1][indice][dia].hora=Pega_Hora(horasdisponiveis, escolhacurso, dia); //Chama outra fun��o pra pegar a hora
    propostas[escolhacurso-1][indice][dia].tipo=Pega_Tipo(contadordetipos, dia); //Chama outra fun��o pra pegar o tipo da proposta

    //Pergunta ao usu�rio quantos proponentes a proposta ter�, impedindo-o de inserir mais que 5 ou de cadastrar uma proposta sem proponentes.//
    do{
        printf("\tQuantidade de proponentes: ");
        scanf("%i", &propostas[escolhacurso-1][indice][dia].quantidade_de_proponentes); //� perguntado a quantidade de proponentes para saber quantas vezes o la�o abaixo deve se repetir
        if (propostas[escolhacurso-1][indice][dia].quantidade_de_proponentes > 5 || propostas[escolhacurso-1][indice][dia].quantidade_de_proponentes < 1)
            printf("ERRO: A quantidade de proponentes precisa ser um n�mero de 1 a 5.\n");
        else
            j++;
    }while(j==0);

    propostas[escolhacurso][indice][dia].temprof=0; //temprof inicia-se como 0, sup�e-se de in�cio que a proposta n�o tem professores, caso o usu�rio cadastre algum professor, esse valor muda para 1
    for (i=0; i<propostas[escolhacurso-1][indice][dia].quantidade_de_proponentes; i++){
        fflush(stdin); //limpando o buffer do teclado novamente
        printf("\t\tNome do %i� proponente:", i+1);
        gets(propostas[escolhacurso-1][indice][dia].proponentes[i]); //Pede o nome do proponente e armazena na matriz de struct

        //Pergunta ao usu�rio se o proponente x � aluno ou professor, com tratamento de erro caso ele digite um n�mero inv�lido.//
        do{
            printf("\t\t[1]Aluno ou [2]Professor: ");
            scanf("%i", &prof_ou_alun);
            if (prof_ou_alun>2 || prof_ou_alun<1)
                printf("ERRO: Digite um valor v�lido.\n");
            else
                j++;
        }while(j==1);

        if (prof_ou_alun == 2){
            propostas[escolhacurso-1][indice][dia].temprof=1; //Se houver algum professor, esse valor muda pra 1, futuramente quando for apresentar os cursos que s� tem estudantes, eu s� irei printar os cursos que essa vari�vel � igual a zero
            strcat(propostas[escolhacurso-1][indice][dia].proponentes[i], " (Professor)"); //Concatena o nome do proponente com o que ele �, por exemplo: "Jo�o (Aluno); Jos� (Professor)"
        }else
            strcat(propostas[escolhacurso-1][indice][dia].proponentes[i], " (Aluno)");
        }
    Limpa_Tela(dia);
    printf("Cadastro conclu�do.\n");
}

//Essa fun��o � executada dentro da fun��o Cadastro_De_Proposta, � basicamente uma rotina de escolher o hor�rio da apresenta��o e bloquear que duas propostas do mesmo curso aconte�am no mesmo hor�rio.
int Pega_Hora(int horasdisponiveis[50][12][2], int escolhacurso, int dia){
    int i, valorhora, k=0, horafinal;
    //Esse sistema de disponibilidade de hor�rio funciona da seguinte forma: todos os hor�rios iniciam com seu indice correspondente igual a zero, sempre que o usu�rio escolher uma hora, ele verifica se o �ndice correspondente a ele � igual a 0 ou 1
    //Se for 1, ele n�o permite o cadastro, se for 0, ele permite o cadastro e modifica esse indice pra 1
    do{
        printf("Escolha um horario para a apresenta��o:");
        for (i=0; i<12; i++){
            printf("\n\t[%i] %ih", i+1, i+8);
            if (horasdisponiveis[escolhacurso][i][dia]==1)
                printf (" (j� utilizado)");
        }
        printf("\n-> ");
        scanf("%i", &valorhora);
        if (horasdisponiveis[escolhacurso][(valorhora-1)][dia]==1)
            printf("\nERRO: Esse hor�rio j� est� sendo utilizado em uma apresenta��o desse curso, por favor escolha outro.\n");
        else if (valorhora<1 || valorhora>12)
            printf("\nERRO: Comando inv�lido.\n");
        else{
            horasdisponiveis[escolhacurso][(valorhora-1)][dia]=1;
            k=1;
        }
    }while(k==0);
    horafinal = valorhora+7; //Por fim, a hora que ser� retornada ser� o valor q o usuario digitou somado com 7, pois [1] representa 8h, [2] representa 9h e assim por diante.
    return horafinal;
}

//Essa fun��o tamb�m � executada dentro da Cadastro_de_Proposta, ela simplesmente solicita o tipo de proposta ao usu�rio e soma num contador de tipos que ser� utilizado no final do programa, ao mostras quantas propostas de cada tipo foram cadastradas.
int Pega_Tipo(int contadordetipos[2][4], int dia){
    int tipo, i=0;
    while (i==0){
        printf("Escolha um tipo de apresenta��o:\n");
        printf("\t[1] Oral\t[2] Oficina\n\t[3] P�ster\t[4] Laborat�rio\n->");
        scanf("%i", &tipo);
        if(tipo>4 || tipo<1) //Solicita um n�mero, executa tratamento de erro caso o usuario digite um numero menor que 1 ou maior que 4, caso n�o, retorna esse numero.
            printf("\nERRO: Comando inv�lido.\n");
        else{
            contadordetipos[dia][(tipo-1)]++;
            i++;
        }
    }
    return tipo;
}

//Fun��o que solicita ao usu�rio que ele digite um nome pro arquivo texto e concatena essa string com ".txt"
void Solicitar_Nome_do_Arquivo(char nomedoarquivo[60]){
    printf("Seu relat�rio ser� salvo em um arquivo de texto!\nNome do arquivo: ");
    fflush(stdin);
    gets (nomedoarquivo);
    strcat(nomedoarquivo, ".txt");
}

//Fun��o que ordena as propostas do menor hor�rio para o maior, utilizando o algoritmo de ordena��o Bubble Sort
void Ordena_Propostas(struct cadastro propostas[50][10][2], int numcursos, int quantpropostas[2][50]){
    struct cadastro aux;
    int i, j, h, k;
    for (h=0; h<2; h++){
        for (i=0; i<numcursos; i++){
            //A partir desse ponto come�a o Bubble Sort, os dois la�os anteriores garantem que todos os cursos sejam ordenadas, de ambos os dias//
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

//Fun��o que printa todas as propostas no arquivo .txt
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
                fprintf(file, "\n\t\t\tHor�rio: %ih", propostas[i][j][dia].hora);
                fprintf(file, "\n\t\t\tTipo: %i", propostas[i][j][dia].tipo);
                fprintf(file, "\n\t\t\tLista de Proponentes:");
                for (k=0; k<propostas[i][j][dia].quantidade_de_proponentes; k++){
                        fprintf(file, "\n\t\t\t\t-%s", propostas[i][j][dia].proponentes[k]);
                }
            }
        }
    }
    fclose(file); //fecha o arquivo com seguran�a
}

//Fun��o que printa no arquivo texto quantas apresenta��es de cada tipo acontecer�o em cada um dos dias
void Funcao_Arquivo_Texto_2(int contadordetipos[2][4], char nomedoarquivo[60]){
    int i, j;
    FILE *file;
    file = fopen(nomedoarquivo, "a");
    fprintf(file, "\n\n################## INFORMA��ES ADICIONAIS ##################\n");
    for (i=0; i<2; i++){
        fprintf(file, "No dia %i/10, est�o cadastradas:\n\t", i+23);
        for (j=0; j<4; j++){
            fprintf(file, "%i apresenta��es do tipo ", contadordetipos[i][j]); //Essa fun��o basicamente printa os valores do contadordetipos.
            if (j==0)
                fprintf(file, "ORAL;\n\t");
            else if (j==1)
                fprintf(file, "OFICINA;\n\t");
            else if (j==2)
                fprintf(file, "P�STER;\n\t");
            else if (j==3)
                fprintf(file, "LABORAT�RIO;\n");
        }
    }
    fclose(file);
}

//Fun��o que printa no arquivo .txt o(s) cursos com maior representatividade
void Funcao_Arquivo_Texto_3(int quantpropostas[2][50], char cursos[50][60], char nomedoarquivo[60], int numcursos){
    FILE *file;
    file = fopen(nomedoarquivo, "a");
    int maior, i;
    //Verificando qual � a maior quantidade de propostas//
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

//Fun��o que printa no arquivo .txt o(s) cursos com menor representatividade
void Funcao_Arquivo_Texto_4(int quantpropostas[2][50], char cursos[50][60], char nomedoarquivo[60], int numcursos){
    FILE *file;
    file = fopen(nomedoarquivo, "a");
    int menor, i;
    //Verificando qual � a menor quantidade de propostas//
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

//Fun��o que printa no arquivo .txt uma lista com todas as propostas que cont�m apenas estudantes.
void Funcao_Arquivo_Texto_5(struct cadastro propostas[50][10][2], char cursos[50][60], int quantpropostas[2][50], char nomedoarquivo[60], int numcursos){
    FILE *file;
    file = fopen(nomedoarquivo, "a");
    int dia, curso, proposta;
    fprintf(file, "\n\n################## PROPOSTAS OFERTADAS APENAS POR ALUNOS ##################:");
    for(dia=0; dia<2; dia++){
        for (curso=0; curso<numcursos; curso++){
            for (proposta=0; proposta<quantpropostas[dia][curso]; proposta++){
                if (propostas[curso][proposta][dia].temprof==0)
                    fprintf(file, "\n\t-%s, do curso %s", propostas[curso][proposta][dia].titulo, cursos[curso]); //Analisa curso por curso se temprof � 0 ou 1, se for 0 (n�o tem professor), ent�o ele printa esse curso.
            }
        }
    }
    fclose(file);
}
