/*******************************************************************************
Autor: Johnny Quest Dantas Pereira
Componente Curricular: Algoritmos I
Concluido em: 07/10/2017
Declaro que este c�digo foi elaborado por mim de forma individual e n�o cont�m nenhum
trecho de c�digo de outro colega ou de outro autor, tais como provindos de livros e
apostilas, e p�ginas ou documentos eletr�nicos da Internet. Qualquer trecho de c�digo
de outra autoria que n�o a minha est� destacado com uma cita��o para o autor e a fonte
do c�digo, e estou ciente que estes trechos n�o ser�o considerados para fins de avalia��o.
********************************************************************************/

//PROGRAMA DE CADASTRO ACS

#include <stdio.h>   //Biblioteca para entrada e sa�da de dados, necess�ria para utilizar os comandos "printf" e "scanf".
#include <locale.h>  //Biblioteca que possibilita definir a localiza��o do programa.
#include <stdlib.h>  //Biblioteca para poder usar o comando system("cls"), que "limpa" a tela, apaga tudo o que foi escrito.
int escolha, dia, mes, ano, diaatual=0, mesatual=0, anoatual=0, microcefalia, cardiaco, diabetes, plano, sexo, dataok, etapamenu, confirmacao; //Declara��o das vari�veis do tipo int.
int foiano, foimicro, foicard, foidiabete, foiplano, foimenino, foimenina; //Declara��o de vari�veis do tipo int que ser�o utilizadas simulando vari�veis booleanas (true e false com 1 e 0, respectivamente)
float relat_ano = 0, peso, altura, relat_micro = 0, relat_card = 0, relat_diabetes = 0, relat_plano = 0, relat_meninos = 0, relat_meninas = 0, relat_criancas = 0, mediapeso= 0, relat_peso = 0; //Declara��o das vari�veis do tipo float.
int main(){
    setlocale(LC_ALL, "Portuguese"); //Definindo a localiza��o do programa para portugu�s, para poder utilizar caracteres especiais como acentos e �.

//Solicita��o da data atual:
    if(dataok!=2){     //Esse if existe para que a solicita��o de data aconte�a apenas no come�o do programa.
        printf("Insira a data de hoje no padr�o dia/m�s/ano (Exemplo: 3/8/2008)\n->");
        scanf("%i/%i/%i", &diaatual,&mesatual,&anoatual); //O usu�rio insere o valor das vari�veis correspondentes � dia, m�s e ano, respectivamente
        if (diaatual > 31 || diaatual < 1 || mesatual > 12 || mesatual <= 0 || anoatual <= 1000){  //Garante que o usu�rio n�o digite uma data que n�o exista
            printf("\aData inv�lida\n");
            return main();
        }
        system("cls");
        dataok=2; //Garante que o programa n�o pergunte mais a data de hoje
        etapamenu=0; //Inicia o while do menu inicial
    }

//Menu principal:
    while(etapamenu==0){
        printf("\n==============================================================================\n");
        printf("\t\t\t  PROGRAMA DE CADASTRO ACS\n");
        printf("\t\t\t A data de hoje � %i/%i/%i \n", diaatual,mesatual,anoatual);
        printf("==============================================================================\n\n");
        printf("Escolha uma op��o. \n[1]Novo Cadastro \n[2]Visualizar Relat�rio \n->");
        scanf("%d", &escolha);
        if (escolha == 1){
            etapamenu++; //Inicia o la�o correspondente � solicita��o da data de nascimento da crian�a.
        }else if (escolha == 2){
            etapamenu=9; //Inicia o la�o correspondente ao relat�rio.
        }else{
            printf("\aERRO: Comando inv�lido!");
        }
    }

//Solicita��o da data de nascimento:
    while(etapamenu==1){
        printf("\nData de nascimento da crian�a. (Formato dd/mm/aaaa) \n->");
        scanf("%d/%d/%d", &dia,&mes,&ano);
        if (ano == anoatual){
            foiano=1; //"foiano" est� como true, isso significa que, no final do cadastro, eu devo somar 1 no relat�rio, nessa caracteristica.
            etapamenu++; //modifica a vari�vel condicional do while para que o programa entre no pr�ximo la�o
        }else if (ano > anoatual){ //Pro�be que o usu�rio cadastre uma crian�a que ainda n�o nasceu
            printf("\aERRO: Data inv�lida. \n");
        }else if (ano < (anoatual-12)){ //Se o usu�rio tentar cadastrar uma pessoa que n�o � crian�a, o programa  volta ao menu iniciar, automaticamente anulando o cadastro que estava sendo feito.
            printf("\aERRO: Essa pessoa n�o � considerada uma crian�a \n");
            system("pause");
            system("cls");
            etapamenu=0; //inicia o la�o correspondente ao menu inicial
            return main();
        }else if (ano == (anoatual-12)){ //Caso a crian�a tenha nascido 12 anos atr�s, a estrutura condicional abaixo ir� verificar se ela j� fez anivers�rio, caso tenha feito, o programa apresenta um erro.
            if (mes < mesatual){
                printf("\aERRO: Essa pessoa n�o � considerada uma crian�a. \n");
                system("pause");
                system("cls");
                etapamenu=0; //inicia o la�o correspondente ao menu inicial
            }else if (mes == mesatual && dia < diaatual){
                printf("\aERRO: Essa pessoa n�o � considerada uma crian�a. \n");
                system("pause");
                system("cls");
                etapamenu=0; //inicia o la�o correspondente ao menu inicial
            }else{
                foiano=0; //"foiano" est� como false, isso significa que, no final do cadastro, eu n�o devo somar nada no relat�rio, nessa caracteristica.
                etapamenu++;
            }
        }else{
            foiano=0; //"foiano" est� como false, isso significa que, no final do cadastro, eu n�o devo somar nada no relat�rio, nessa caracteristica.
            etapamenu++;
        }
    }

//Solicita��o do peso da crian�a: (e altura, que ser� usada para mostrar o IMC da crian�a)
    while(etapamenu==2){
        printf("\nPeso da crian�a em kg. (Ex: 13,5)\n->");
        scanf("%f", &peso);
        mediapeso=mediapeso+(float)peso;
        printf("Altura da crian�a em m. (Ex: 1,30)\n->");
        scanf("%f", &altura);
        printf("OBS.: O IMC da crian�a � %.2f\n", peso/(altura*altura));
        etapamenu++;
    }

//Pergunta "Possui Microcefalia?":
    while(etapamenu==3){
        printf("\nPossui microcefalia? \n[1] Sim\n[2] N�o\n->");
        scanf("%d", &microcefalia);
        if (microcefalia == 1){
            foimicro=1; //"foimicro" est� como true, isso significa que, no final do cadastro, eu devo somar 1 no relat�rio, nessa caracteristica.
            etapamenu++;
        }else if (microcefalia != 2){
            printf("\aERRO: Comando inv�lido!\n");
        }else{
            foimicro=0; //"foimicro" est� como false, isso significa que, no final do cadastro, eu n�o devo somar nada no relat�rio, nessa caracteristica.
            etapamenu++;
        }
    }

//Pergunta "Possui Problema Card�aco?":
    while(etapamenu==4){
        printf("\nPossui problema card�aco? \n[1] Sim\n[2] N�o\n->");
        scanf("%d", &cardiaco);
        if (cardiaco == 1){
            foicard=1; //"foicard" est� como true, isso significa que, no final do cadastro, eu devo somar 1 no relat�rio, nessa caracteristica.
            etapamenu++;
        }else if (cardiaco  != 2){
            printf("\aERRO: Comando inv�lido!\n");
        }else{
            foicard=0; //"foicard" est� como false, isso significa que, no final do cadastro, eu n�o devo somar nada no relat�rio, nessa caracteristica.
            etapamenu++;
        }
    }

//Pergunta "Possui Diabetes?":
    while(etapamenu==5){
        printf("\nPossui diabetes? \n[1] Sim\n[2] N�o\n->");
        scanf("%d", &diabetes);
        if (diabetes == 1){
            foidiabete=1; //"foidiabete" est� como true, isso significa que, no final do cadastro, eu devo somar 1 no relat�rio, nessa caracteristica.
            etapamenu++;
        }else if (diabetes  != 2){
            printf("\aERRO: Comando inv�lido!\n");
        }else{
            foidiabete=0; //"foidiabete" est� como false, isso significa que, no final do cadastro, eu n�o devo somar nada no relat�rio, nessa caracteristica.
            etapamenu++;
        }
    }

//Pergunta "Possui plano de sa�de?":
    while(etapamenu==6){
        printf("\nPossui plano de sa�de? \n[1] Sim\n[2] N�o\n->");
        scanf("%d", &plano);
        if (plano ==2){
            foiplano=1; //"foiplano" est� como true, isso significa que, no final do cadastro, eu devo somar 1 no relat�rio, nessa caracteristica.
            etapamenu++;
        }else if (plano != 1){
            printf("\aERRO: Comando inv�lido! \n");
        }else{
            foiplano=0; //"foiplano" est� como false, isso significa que, no final do cadastro, eu n�o devo somar nada no relat�rio, nessa caracteristica.
            etapamenu++;
        }
    }

//Pergunta "Sexo da crian�a?":
    while(etapamenu==7){
        printf("\nSexo da crian�a: \n[1] Masculino\n[2] Feminino\n->");
        scanf("%d", &sexo);
        if (sexo == 1){
            foimenino=1; //"foimenino" est� como true, isso significa que, no final do cadastro, eu devo somar 1 no relat�rio, nessa caracteristica.
            foimenina=0; //"foimenina" est� como false, isso significa que, no final do cadastro, eu n�o devo somar nada no relat�rio, nessa caracteristica.
            etapamenu++;
        }else if (sexo == 2){
            foimenino=0; //"foimenino" est� como false, isso significa que, no final do cadastro, eu n�o devo somar nada no relat�rio, nessa caracteristica.
            foimenina=1; //"foimenina" est� como true, isso significa que, no final do cadastro, eu devo somar 1 no relat�rio, nessa caracteristica.
            etapamenu++;
        }else{
            printf("\aERRO: Comando inv�lido! \n");
        }
    }

//A confirma��o do Cadastro, onde o usu�rio vai visualizar os dados que inseriu e decidir se tais informa��es ser�o somadas ao relat�rio ou n�o:
    while(etapamenu==8){
        printf("As informa��es que voc� prestou foram as seguintes:\n\n\tData de nascimento: %d/%d/%d; \n\t", dia,mes,ano);
        printf("Peso: %.2f kg\n\t", peso);
        if (foimicro==1) printf("Possui microcefalia;\n\t"); else printf("N�o possui microcefalia;\n\t");
        if (foicard==1) printf("Possui problema card�aco;\n\t"); else printf("N�o possui problema card�aco;\n\t");
        if (foidiabete==1) printf("Possui diabetes;\n\t"); else printf ("N�o possui diabetes;\n\t");
        if (foiplano==0) printf ("Possui plano de sa�de;\n\t"); else printf("N�o possui plano de sa�de;\n\t");
        if (foimenino==1) printf("Sexo masculino.\n\n"); else printf("Sexo feminino.\n\n");
        printf("DESEJA CONFIRMAR ESSE CADASTRO?\n[1] Sim\n[2] N�o\n->");
        scanf("%d", &confirmacao);
        if(confirmacao==1){
            relat_criancas=relat_criancas+1;
            if (foiano==1) relat_ano=relat_ano+1;
            if (foimicro==1) relat_micro=relat_micro+1;
            if (foicard==1) relat_card=relat_card+1;
            if (foidiabete==1) relat_diabetes=relat_diabetes+1;
            if (foiplano==1) relat_plano=relat_plano+1;
            if (foimenino==1) relat_meninos=relat_meninos+1;
            if (foimenina==1) relat_meninas=relat_meninas+1;
            printf("\nCadastro conclu�do com sucesso!\n");
            system("pause");
            system("cls");
            etapamenu=0;
            return main();
        }else if (confirmacao==2){
            printf("\a\nCadastro cancelado!");
            system("pause");
            system("cls");
            etapamenu=0;
            return main();
        } else{
            printf("\aComando inv�lido!");
        }

    }

////RELAT�RIO:
    while(etapamenu==9){
        if(relat_criancas>0){
            float porcent_ano = (relat_ano*100)/relat_criancas, porcent_micro = (relat_micro*100)/relat_criancas, porcent_card = (relat_card*100)/relat_criancas, porcent_diabetes = (relat_diabetes*100)/relat_criancas, porcent_plano= (relat_plano*100)/relat_criancas , porcent_menino= (relat_meninos*100)/relat_criancas, porcent_menina = (relat_meninas*100)/relat_criancas, relat_peso = (mediapeso/relat_criancas);
            printf("\n\n ##### RELAT�RIO ##### \n\n");
            printf("CRIAN�AS CADASTRADAS: %.0f \n", relat_criancas);
            printf("Crian�as nascidas no ano corrente: %.0f", relat_ano);
                printf("              (%.1f %% do total) \n", porcent_ano);
            printf("Quantidade de crian�as com microcefalia: %.0f", relat_micro);
                printf("        (%.1f %% do total) \n", porcent_micro);
            printf("Quantidade de crian�as com problema card�aco: %.0f", relat_card);
                printf("   (%.1f %% do total) \n", porcent_card);
            printf("Quantidade de crian�as com diabetes: %.0f", relat_diabetes);
                printf("            (%.1f %% do total) \n", porcent_diabetes);
            printf("Quantidade de crian�as sem plano de sa�de: %.0f", relat_plano);
                printf("      (%.1f %% do total) \n", porcent_plano);
            printf("Quantidade de meninos: %.0f", relat_meninos);
                printf("                          (%.1f %% do total) \n", porcent_menino);
            printf("Quantidade de meninas: %.0f", relat_meninas);
                printf("                          (%.1f %% do total) \n", porcent_menina);
            printf("M�dia de peso entre as crian�as: %.2fkg \n\n\n\n", relat_peso);
            system("pause");
            system("cls");
            etapamenu=0;
            return main();
        }else{
            printf("\a ERRO: Fa�a algum cadastro antes! \n\n");    //Essa mensagem � exibida caso o usu�rio tente visualizar o relat�rio sem ter feito nenhum cadastro antes.
            system("pause");
            system("cls");
            etapamenu=0;
            return main();
        }
    }
return 0;
}

