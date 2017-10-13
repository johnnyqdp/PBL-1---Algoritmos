/*******************************************************************************
Autor: Johnny Quest Dantas Pereira
Componente Curricular: Algoritmos I
Concluido em: 07/10/2017
Declaro que este código foi elaborado por mim de forma individual e não contém nenhum
trecho de código de outro colega ou de outro autor, tais como provindos de livros e
apostilas, e páginas ou documentos eletrônicos da Internet. Qualquer trecho de código
de outra autoria que não a minha está destacado com uma citação para o autor e a fonte
do código, e estou ciente que estes trechos não serão considerados para fins de avaliação.
********************************************************************************/

//PROGRAMA DE CADASTRO ACS

#include <stdio.h>   //Biblioteca para entrada e saída de dados, necessária para utilizar os comandos "printf" e "scanf".
#include <locale.h>  //Biblioteca que possibilita definir a localização do programa.
#include <stdlib.h>  //Biblioteca para poder usar o comando system("cls"), que "limpa" a tela, apaga tudo o que foi escrito.
int escolha, dia, mes, ano, diaatual=0, mesatual=0, anoatual=0, microcefalia, cardiaco, diabetes, plano, sexo, dataok, etapamenu, confirmacao; //Declaração das variáveis do tipo int.
int foiano, foimicro, foicard, foidiabete, foiplano, foimenino, foimenina; //Declaração de variáveis do tipo int que serão utilizadas simulando variáveis booleanas (true e false com 1 e 0, respectivamente)
float relat_ano = 0, peso, altura, relat_micro = 0, relat_card = 0, relat_diabetes = 0, relat_plano = 0, relat_meninos = 0, relat_meninas = 0, relat_criancas = 0, mediapeso= 0, relat_peso = 0; //Declaração das variáveis do tipo float.
int main(){
    setlocale(LC_ALL, "Portuguese"); //Definindo a localização do programa para português, para poder utilizar caracteres especiais como acentos e ç.

//Solicitação da data atual:
    if(dataok!=2){     //Esse if existe para que a solicitação de data aconteça apenas no começo do programa.
        printf("Insira a data de hoje no padrão dia/mês/ano (Exemplo: 3/8/2008)\n->");
        scanf("%i/%i/%i", &diaatual,&mesatual,&anoatual); //O usuário insere o valor das variáveis correspondentes à dia, mês e ano, respectivamente
        if (diaatual > 31 || diaatual < 1 || mesatual > 12 || mesatual <= 0 || anoatual <= 1000){  //Garante que o usuário não digite uma data que não exista
            printf("\aData inválida\n");
            return main();
        }
        system("cls");
        dataok=2; //Garante que o programa não pergunte mais a data de hoje
        etapamenu=0; //Inicia o while do menu inicial
    }

//Menu principal:
    while(etapamenu==0){
        printf("\n==============================================================================\n");
        printf("\t\t\t  PROGRAMA DE CADASTRO ACS\n");
        printf("\t\t\t A data de hoje é %i/%i/%i \n", diaatual,mesatual,anoatual);
        printf("==============================================================================\n\n");
        printf("Escolha uma opção. \n[1]Novo Cadastro \n[2]Visualizar Relatório \n->");
        scanf("%d", &escolha);
        if (escolha == 1){
            etapamenu++; //Inicia o laço correspondente à solicitação da data de nascimento da criança.
        }else if (escolha == 2){
            etapamenu=9; //Inicia o laço correspondente ao relatório.
        }else{
            printf("\aERRO: Comando inválido!");
        }
    }

//Solicitação da data de nascimento:
    while(etapamenu==1){
        printf("\nData de nascimento da criança. (Formato dd/mm/aaaa) \n->");
        scanf("%d/%d/%d", &dia,&mes,&ano);
        if (ano == anoatual){
            foiano=1; //"foiano" está como true, isso significa que, no final do cadastro, eu devo somar 1 no relatório, nessa caracteristica.
            etapamenu++; //modifica a variável condicional do while para que o programa entre no próximo laço
        }else if (ano > anoatual){ //Proíbe que o usuário cadastre uma criança que ainda não nasceu
            printf("\aERRO: Data inválida. \n");
        }else if (ano < (anoatual-12)){ //Se o usuário tentar cadastrar uma pessoa que não é criança, o programa  volta ao menu iniciar, automaticamente anulando o cadastro que estava sendo feito.
            printf("\aERRO: Essa pessoa não é considerada uma criança \n");
            system("pause"); //"Pausa o programa, solicitando que o usuário pressione alguma tecla para continuar"
            system("cls"); //"Limpa" a tela.
            etapamenu=0; //inicia o laço correspondente ao menu inicial
            return main();
        }else if (ano == (anoatual-12)){ //Caso a criança tenha nascido 12 anos atrás, a estrutura condicional abaixo irá verificar se ela já fez aniversário, caso tenha feito, o programa apresenta um erro.
            if (mes < mesatual){
                printf("\aERRO: Essa pessoa não é considerada uma criança. \n");
                system("pause");
                system("cls");
                etapamenu=0; //inicia o laço correspondente ao menu inicial
            }else if (mes == mesatual && dia < diaatual){
                printf("\aERRO: Essa pessoa não é considerada uma criança. \n");
                system("pause");
                system("cls");
                etapamenu=0; //inicia o laço correspondente ao menu inicial
            }else{
                foiano=0; //"foiano" está como false, isso significa que, no final do cadastro, eu não devo somar nada no relatório, nessa caracteristica.
                etapamenu++; //pula para a próxima etapa
            }
        }else{
            foiano=0; //"foiano" está como false, isso significa que, no final do cadastro, eu não devo somar nada no relatório, nessa caracteristica.
            etapamenu++; //pula para a próxima etapa
        }
    }

//Solicitação do peso da criança: (e altura, que será usada para mostrar o IMC da criança)
    while(etapamenu==2){
        printf("\nPeso da criança em kg. (Ex: 13,5)\n->");
        scanf("%f", &peso); //o usuário entra um dado do tipo float correspondente ao peso da criança
        mediapeso=mediapeso+(float)peso; //o peso inserido é somado a uma variável, ao exibir o relatório, essa variável será a soma de todos os pesos, que vai ser dividida pela quantidade de crianças cadastradas para exibir a média
        printf("Altura da criança em m. (Ex: 1,30)\n->");
        scanf("%f", &altura); //entrada da aultura da criança, apenas para calcular o IMC.
        printf("OBS.: O IMC da criança é %.2f\n", peso/(altura*altura));
        etapamenu++; //pula para a próxima etapa
    }

//Pergunta "Possui Microcefalia?":
    while(etapamenu==3){
        printf("\nPossui microcefalia? \n[1] Sim\n[2] Não\n->");
        scanf("%d", &microcefalia);
        if (microcefalia == 1){
            foimicro=1; //"foimicro" está como true, isso significa que, no final do cadastro, eu devo somar 1 no relatório, nessa caracteristica.
            etapamenu++; //pula para a próxima etapa
        }else if (microcefalia != 2){
            printf("\aERRO: Comando inválido!\n");
        }else{
            foimicro=0; //"foimicro" está como false, isso significa que, no final do cadastro, eu não devo somar nada no relatório, nessa caracteristica.
            etapamenu++; //pula para a próxima etapa
        }
    }

//Pergunta "Possui Problema Cardíaco?":
    while(etapamenu==4){
        printf("\nPossui problema cardíaco? \n[1] Sim\n[2] Não\n->");
        scanf("%d", &cardiaco);
        if (cardiaco == 1){
            foicard=1; //"foicard" está como true, isso significa que, no final do cadastro, eu devo somar 1 no relatório, nessa caracteristica.
            etapamenu++; //pula para a próxima etapa
        }else if (cardiaco  != 2){
            printf("\aERRO: Comando inválido!\n");
        }else{
            foicard=0; //"foicard" está como false, isso significa que, no final do cadastro, eu não devo somar nada no relatório, nessa caracteristica.
            etapamenu++; //pula para a próxima etapa
        }
    }

//Pergunta "Possui Diabetes?":
    while(etapamenu==5){
        printf("\nPossui diabetes? \n[1] Sim\n[2] Não\n->");
        scanf("%d", &diabetes);
        if (diabetes == 1){
            foidiabete=1; //"foidiabete" está como true, isso significa que, no final do cadastro, eu devo somar 1 no relatório, nessa caracteristica.
            etapamenu++; //pula para a próxima etapa
        }else if (diabetes  != 2){
            printf("\aERRO: Comando inválido!\n");
        }else{
            foidiabete=0; //"foidiabete" está como false, isso significa que, no final do cadastro, eu não devo somar nada no relatório, nessa caracteristica.
            etapamenu++; //pula para a próxima etapa
        }
    }

//Pergunta "Possui plano de saúde?":
    while(etapamenu==6){
        printf("\nPossui plano de saúde? \n[1] Sim\n[2] Não\n->");
        scanf("%d", &plano);
        if (plano ==2){
            foiplano=1; //"foiplano" está como true, isso significa que, no final do cadastro, eu devo somar 1 no relatório, nessa caracteristica.
            etapamenu++; //pula para a próxima etapa
        }else if (plano != 1){
            printf("\aERRO: Comando inválido! \n");
        }else{
            foiplano=0; //"foiplano" está como false, isso significa que, no final do cadastro, eu não devo somar nada no relatório, nessa caracteristica.
            etapamenu++; //pula para a próxima etapa
        }
    }

//Pergunta "Sexo da criança?":
    while(etapamenu==7){
        printf("\nSexo da criança: \n[1] Masculino\n[2] Feminino\n->");
        scanf("%d", &sexo);
        if (sexo == 1){
            foimenino=1; //"foimenino" está como true, isso significa que, no final do cadastro, eu devo somar 1 no relatório, nessa caracteristica.
            foimenina=0; //"foimenina" está como false, isso significa que, no final do cadastro, eu não devo somar nada no relatório, nessa caracteristica.
            etapamenu++; //pula para a próxima etapa
        }else if (sexo == 2){
            foimenino=0; //"foimenino" está como false, isso significa que, no final do cadastro, eu não devo somar nada no relatório, nessa caracteristica.
            foimenina=1; //"foimenina" está como true, isso significa que, no final do cadastro, eu devo somar 1 no relatório, nessa caracteristica.
            etapamenu++; //pula para a próxima etapa
        }else{
            printf("\aERRO: Comando inválido! \n");
        }
    }

//A confirmação do Cadastro, onde o usuário vai visualizar os dados que inseriu e decidir se tais informações serão somadas ao relatório ou não:
    while(etapamenu==8){
        printf("As informações que você prestou foram as seguintes:\n\n\tData de nascimento: %d/%d/%d; \n\t", dia,mes,ano);
        printf("Peso: %.2f kg\n\t", peso);
        if (foimicro==1) printf("Possui microcefalia;\n\t"); else printf("Não possui microcefalia;\n\t"); //lembrando que foimicro assume 1 para sim e 0 para não
        if (foicard==1) printf("Possui problema cardíaco;\n\t"); else printf("Não possui problema cardíaco;\n\t"); //lembrando que foicard assume 1 para sim e 0 para não
        if (foidiabete==1) printf("Possui diabetes;\n\t"); else printf ("Não possui diabetes;\n\t"); //lembrando que foidiabete assume 1 para sim e 0 para não
        if (foiplano==0) printf ("Possui plano de saúde;\n\t"); else printf("Não possui plano de saúde;\n\t"); //lembrando que foiplano assume 1 para não e 0 para sim
        if (foimenino==1) printf("Sexo masculino.\n\n"); else printf("Sexo feminino.\n\n"); //lembrando que quando for menino, foimenino assume 1 e foimenina assume 0, quando for menina, foimenino assume 0 e foimenina assume 1
        printf("DESEJA CONFIRMAR ESSE CADASTRO?\n[1] Sim\n[2] Não\n->");
        scanf("%d", &confirmacao);
        if(confirmacao==1){ //Nesse laço é efetuado o processo de soma nas variáveis do relatório baseando-se nas respostas que o usuário digitou
            relat_criancas=relat_criancas+1;
            if (foiano==1) relat_ano=relat_ano+1;
            if (foimicro==1) relat_micro=relat_micro+1;
            if (foicard==1) relat_card=relat_card+1;
            if (foidiabete==1) relat_diabetes=relat_diabetes+1;
            if (foiplano==1) relat_plano=relat_plano+1;
            if (foimenino==1) relat_meninos=relat_meninos+1;
            if (foimenina==1) relat_meninas=relat_meninas+1;
            printf("\nCadastro concluído com sucesso!\n");
            system("pause"); //"Pausa o programa, solicitando que o usuário pressione alguma tecla para continuar"
            system("cls"); //"Limpa" a tela
            etapamenu=0;
            return main();
        }else if (confirmacao==2){ //Caso o usuário cancele o cadastro, nenhuma variável é somada, portanto, nada muda no relatório
            printf("\a\nCadastro cancelado!");
            system("pause"); //"Pausa o programa, solicitando que o usuário pressione alguma tecla para continuar"
            system("cls"); //"Limpa" a tela
            etapamenu=0;
            return main();
        } else{
            printf("\aComando inválido!");
        }

    }

////RELATÓRIO:
    while(etapamenu==9){ //laço de exibição do relatório, aqui, todas as variáveis de relatório são exibidas, além de porcentagens em relação ao total
        if(relat_criancas>0){
            float porcent_ano = (relat_ano*100)/relat_criancas, porcent_micro = (relat_micro*100)/relat_criancas, porcent_card = (relat_card*100)/relat_criancas, porcent_diabetes = (relat_diabetes*100)/relat_criancas, porcent_plano= (relat_plano*100)/relat_criancas , porcent_menino= (relat_meninos*100)/relat_criancas, porcent_menina = (relat_meninas*100)/relat_criancas; //declaração das variáveis de porcentagem juntamente dos seus respectivos cálculos.
            float relat_peso = (mediapeso/relat_criancas); //declaração da variável da media do peso das crianças, onde mediapeso (a soma de todos os pesos inseridos) é dividida pelo total de crianças
            printf("\n\n ##### RELATÓRIO ##### \n\n");
            printf("CRIANÇAS CADASTRADAS: %.0f \n", relat_criancas);
            printf("Crianças nascidas no ano corrente: %.0f", relat_ano);
                printf("              (%.1f %% do total) \n", porcent_ano);
            printf("Quantidade de crianças com microcefalia: %.0f", relat_micro);
                printf("        (%.1f %% do total) \n", porcent_micro);
            printf("Quantidade de crianças com problema cardíaco: %.0f", relat_card);
                printf("   (%.1f %% do total) \n", porcent_card);
            printf("Quantidade de crianças com diabetes: %.0f", relat_diabetes);
                printf("            (%.1f %% do total) \n", porcent_diabetes);
            printf("Quantidade de crianças sem plano de saúde: %.0f", relat_plano);
                printf("      (%.1f %% do total) \n", porcent_plano);
            printf("Quantidade de meninos: %.0f", relat_meninos);
                printf("                          (%.1f %% do total) \n", porcent_menino);
            printf("Quantidade de meninas: %.0f", relat_meninas);
                printf("                          (%.1f %% do total) \n", porcent_menina);
            printf("Média de peso entre as crianças: %.2fkg \n\n\n\n", relat_peso);
            system("pause"); //"Pausa o programa, solicitando que o usuário pressione alguma tecla para continuar"
            system("cls"); //"Limpa" a tela
            etapamenu=0; //inicia o laço correspondente ao menu principal
            return main();
        }else{
            printf("\a ERRO: Faça algum cadastro antes! \n\n");    //Essa mensagem é exibida caso o usuário tente visualizar o relatório sem ter feito nenhum cadastro antes.
            system("pause"); //"Pausa o programa, solicitando que o usuário pressione alguma tecla para continuar"
            system("cls"); //"Limpa" a tela
            etapamenu=0;
            return main();
        }
    }
return 0;
}

