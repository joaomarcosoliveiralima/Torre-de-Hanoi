/*
##############################################################
### UFGD - UNIVERCIDADE FEDERAL DA GRANDE DOURADOS         ###
### ACADEMICO - JOÃO MARCOS OLIVEIRA LIMA                  ###
### RGA - 2014071258692                                    ###
### PROFESSOR - ADAILTON JOSÉ ALVES DA CRUZ                ###
### DISCIPLINA - LABORATORIO DE PROGRAMAÇÃO II             ###
### CURSO - ENGENHARIA DE COMPUTAÇÃO                       ###
##############################################################
*/
//DECLARAÇÃO DA BLIBIOTECAS USADAS NO JOGO
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <math.h>

//DEFININDO CONSTANTES
#define linha 7
#define coluna 73
#define tam 16

//ARQUIVOS GLOBAIS ULTILISADOS
FILE *Movimentos;//SALVA OS MOVIMENTOS DO USUARIO
FILE *relatorio; // SALVA OS MOVIMENTOS PARA USAR NO UNDO
FILE *relatGeral; //RELATORIO AUXILIAR PARA O USO DO UNDO
FILE *ranking;// ARMAZENA OS RANKING DOS USUARIOS
FILE *cont_jogadores;// APRESENTAS A LISTA DE JOGADORES DO JOGO
FILE *treino;//SALVA OS MOVIMENTOS DO MODO TREINO

char arquivo[30] = { };//ARMAZENA OS NOME DE USUARIOS PARA CRIAR UM ARQUIVO
char nomeArq[20] = "Relatorio.txt",op; //ARMAZENA O NOME PARA ABRIR O ARQUIVO DO UNDO

typedef struct // STRUC PARA ARMAZENAR OS DADOS DO USUARIO
    {
        char Nome[tam];//ARMAZENA O NOME DO USUARIO
        float pontos;// ARMAZENA O SCORE DO USUARIO
    }tscore;

int seg=0;//VARIAVEL PARA CONTAR OS SEGUNDOS
float time_animation=0.0;//TEMPO DA ANIMAÇÃO
int origem, destino,cont=0;//SALVA ORIGEN DESTINO E O CONTADOR DE MOVIMENTOS
int dia=0,mes=0,ano=0,horas=0,minutos=0,segundos=0;//RECEBE A DATA E HORARIO DO SISTEMA
char str[100]={ };  //ULTILIZADA PARA CONCATENAR OS DADOS
int undo;//VARIAVEL PARA REPRESENTAR SE E UNDO OU NAO
tscore Dados;//VARIAVEL DO TIPO DA STRUCT

char menu();//MENU INICIAL
char menu2();//MENU DA PARTIDA
char menu3();//MENU DE JOGADAS
void perfil();//CRIAR PERFIL PARA O USUARIO
void parabens();//IMPRIME MENSAGEM DE PARABENS
void menu_tela();//MENU DE TELA NO JOGO
void limpa_str();//LIMPAR A STRING DE NOMES
void Limpe_list();//EXCLUIR LISTA DE NOMES
char menu_escolha();//MENU DE ESCOLHA DO JOGADOR
void List_jogador();//LISTA OS JOGADORES DO JOGO
void ordena_score();//ORDENA O RANKING DE JOGADORES
void time_animacao();//RECEBE O TEMPO DE ANIMAÇÃO
void torre_de_hanoi();//IMPRIME TEXTE DE TORRE DE HANOI
//SE NAO TIVER A BLIBIOTECA DA CONIO DESCOMENTAR A FUNCAO GOTOXY
//void gotoxy(int x, int y);
void menu_tela_teste();//MENU DE TELA NO TREINO
int analisamovimento(int);//ANALISA MOVIMENTO PARA A MATRIZ PRINCIPAL
void Time_and_Date_system();//RECEBER DATA E HORA DO SISTEMA
void altera_caracter(int m);//CONVERTE OS NUMEROS DO DIA E HORA DO SISTEMA EM CARACTERE PARA SE CONCATENADO COM O NOME
void cronometro(int x,int y);//CRONOMETRO DA PARTIDA
void imprime_torre(int mat[7][3]);//INPRIME A PRIMEIRA TORRE DE HANOI
void Undorelatorio(char nomeArq[]);//CRIAR O UNDO PARA SER USADO APENAS NO MODO TREINO
void gera_matriz(int mat[7][3], int *disco);//GERA UMA MATRIZ COM A QUANTIDADE DE DICOS SELECIONADA PELO JOGADOR
void mat_interface(char discos[linha][coluna]);//MOSTRA A INTERFASE DA TORRE
void animacao_torre(int , int , int , int , int );//CRIA A ANIMAÇÃO DE TRANSIÇÃO DO DISCO DE UMA TORRE PARA OUTRA
void imprime_pilar(int mat[7][3],char discos[linha][coluna]);//IMPRIME OS PILAR DA TORRE
void MoveDisco(int Orig,int Dest,int mat[7][3] ,char discos[linha][coluna]);//CRIA A RECURÇÃO DO JOGO NA RESOLUÇÃO
void ImprimeUndo(char nomeArq[],int mat[7][3],char discos[linha][coluna]);//FAZ O MOVIMENTO DE REVERTER A JOGADA DO USUARIO NO UNDO
void movemat(int destino2,int origem2,char discos[linha][coluna],int i,int j,int p);//MOVE O DISCO PARA DETERMINDA REGIAO
void movimenta_torre(int mat[7][3] ,int destino2,int origem2,char discos[linha][coluna]);//FUNÇÃO QUE VERIFICA SE AS JOGADAS DO USUARIO E VALIDA
void MoveTorre(int n, int Orig,int Dest, int Aux,int mat[7][3] ,char discos[linha][coluna]);//AUXILIAR NA RECURÇÃO


int main()
{
    int mat[7][3]={0};//MATRIZ DE CONTROLE PARA OS DISCOS
    int Orig = 1, Dest = 3,Aux = 2,cont_jog = 0;//VARIAVEIS DE AUXILIO
    int i,j = 1,k,disco = 0,centro = 9,n,origem2,destino2,Num_min,cont_jogador = 0;//DISCO : QUANTADE DE DISCOS,NUM_MIN : DE MOVIMENTOS
    float num_di_float = 0.0,rec_score = 0.0,aux; // VARIAVEIS PARA O CALCULO DO SCORE

    char discos[linha][coluna] = {0},opcao,opcao2,relat;//DISCOS E A MATRIZ QUE GARDA CADA DISCO EM CARACTER
    char text[100] = {},escolha,ori_conv,des_conv,escolha_menu,nomeArq[] = "treino.txt";//VARIAVEIS DE AUXILIO PARA IMPRIMIR E PARA SALVAR NOME DO ARQUIVO



    FILE *jogadores;//GARDA TODOS OS JOGADORE DO JOGO
    FILE *historia;//GARDA OS DADOS SOBRE O JOGO

    system("color 70");//MUDA A COR DA TELA
    opcao = menu();//RECEBE A SOLICITAÇÃO DO USUARIO

    switch(opcao)
    {
        case'I'://INICIAR
           system("color 70");
           opcao2 = menu2();//MENU DE ESCOLAS
           switch (opcao2)
           {
           case'J'://JOGAR
                jogadores = fopen("jogadores.txt","ab");//ABRIR ARQUIVO PARA SALVAR O NOME DO JOGADOR

                if(jogadores == NULL)
                {
                    printf("nao foi possivel acessar o arquivo");
                    exit(1);
                }
                do{
                    escolha = menu_escolha();
                    system("cls");//LIMPA TELA
                    switch(escolha)//LE A ESCOLHA DO USUARIO
                    {
                        case (49):
                            perfil();//CRIA UM PERFIL PARA O JOGADOR
                        break;
                        case (50):
                            List_jogador();//LISTA OS JOGADORES
                        break;
                        case (51):
                            Limpe_list();// DELETA TODOS OS JOGADORES DA LISTA
                        break;
                        default:
                            printf("\n Opcao Invalida Tente Novamente !\n\n\n");

                    }
                }while(escolha != 49 && escolha != 50 && escolha != 51);
                system("cls");
                fwrite(arquivo,sizeof(arquivo),1,jogadores);//ESCREVE O NOME DO JOGADOR NO ARQUIVO JUNTO COM A DATA EHORA

                fclose(jogadores);
                time_animacao();//ESCOLHA O TEMPO DE ANIMAÇÃO
                gera_matriz(mat,&disco);//GERA UMA MATRIS COM A ECOLHA DE DISCO DO USUARIO
                imprime_pilar(mat,discos);//IMPRIME OS PILAR
                Num_min = 0;
                Num_min = pow(2,disco)-1;//NUMERO MINIMOS DE MOVIMENTOS

                for (i=7-disco,k=0;i<linha;i++,k++)
                {
                    for (j=centro-k-3;j<=centro+k+3;j++)
                    {
                        discos[i][j]=205;//ATRIBUINDO OS DISCOS A MATRIZ
                    }
                }
                mat_interface(discos);//INTERFACE DOS DISCOS
                menu_tela();//MENU DE TELA

                do{
                    do{
                        while(!kbhit())
                        {
                            gotoxy(1,22);
                            printf("Informe a Sua Origem :\t");//RECEBE A ORIGEM DO USUARIO
                            cronometro(24,22);//CHAMA A FUNÇÃO CRONOMETRO
                        }
                        ori_conv = getche();
                        origem = ori_conv - 48;//CONVERTE A ORIGEM DO USUARIO PARA NUMERO
                        fflush(stdin);

                        if(origem == 29 || origem == 61)
                        {
                            escolha_menu = menu3();//CHAMA A FUNÇÃO MENU

                            switch(escolha_menu)
                            {
                                case'E':
                                    ordena_score();//MOSTRA A LISTA DE RANKING

                                break;
                                case'C'://CONTINUA A PARTIDA DO  JOGO
                                    system("cls");
                                    imprime_pilar(mat,discos);
                                    Num_min = 0;
                                    Num_min = pow(2,disco)-1;

                                    for (i=7-disco,k=0;i<linha;i++,k++)
                                    {
                                        for (j=centro-k-3;j<=centro+k+3;j++)
                                        {
                                             system("color 70");
                                             discos[i][j]=205;
                                        }
                                    }
                                    mat_interface(discos);
                                    menu_tela();

                                    while(!kbhit())
                                    {

                                        gotoxy(1,22);
                                        printf("Informe a Sua Origem :\t");
                                        cronometro(24,22);
                                    }

                                    break;

                                break;
                                case'R'://RECOMESA O JOGO
                                    system("cls");
                                    main();
                                break;
                                case'A':
                                    system("cls");
                                    main();//ABANDONA A PARTIDA
                                break;
                            }
                        }
                        while(!kbhit())
                        {
                            gotoxy(1,24);
                            printf("Informe o Seu Destino Para o Disco :\t");//RECEBE O DESTINO
                            cronometro(37,24);//CHAMA CRONOMETRO
                        }

                        des_conv = getche();
                        destino = des_conv - 48;//COVERTE PARA NUMERO
                        fflush(stdin);
                        if( destino == 29 || destino == 61)
                        {
                            escolha_menu = menu3();//MENU DO USUARIO EM DESTINO

                            switch(escolha_menu)
                            {
                                case'E':
                                    ordena_score();//LISTA DE RANKING

                                break;
                                case'C':
                                    system("cls");
                                    imprime_pilar(mat,discos);
                                    Num_min = 0;
                                    Num_min = pow(2,disco)-1;//CALC. NUMERO MIN DE JOGADAS

                                    for (i=7-disco,k=0;i<linha;i++,k++)
                                    {
                                        for (j=centro-k-3;j<=centro+k+3;j++)
                                        {
                                             system("color 70");
                                             discos[i][j]=205;
                                        }
                                    }
                                    mat_interface(discos);
                                    menu_tela();//MENU DE TELA

                                    while(!kbhit())
                                    {

                                        gotoxy(1,22);
                                        printf("Informe a Sua Origem :\t");//RECOMESA COM  A ORIGEM PARA O USUARIO
                                        cronometro(24,22);//CHAMA NOVAMENTE CRONOMETRO
                                    }

                                    break;

                                break;
                                case'R':
                                    system("cls");
                                    main();
                                break;
                                case'A':
                                    system("cls");
                                    main();
                                break;
                            }
                        }
                        system("cls");
                        mat_interface(discos);
                        imprime_pilar(mat,discos);
                        menu_tela();


                  }while(origem<1 || origem >3 || destino <1 || destino>3 || origem == destino);
                        //SO SAI DESSE LAÇO SE FOR UMA JOGADA VALIDA

                    Movimentos = fopen(arquivo,"a");//CRIAR RELATORIO DE JOGADAS DO USUARIO
                    fprintf(Movimentos,"Tempo : %d\n",seg);//ESCREVE O TEMPO DAS JOGADAS
                    fprintf(Movimentos,"%d -> %d \n",origem ,destino);
                    fclose(Movimentos);

                    origem2 = analisamovimento(origem);//CONVERTE AS CORDENADAS PARA MATRIZ DE CARACTERE
                    destino2 = analisamovimento(destino);

                    movimenta_torre(mat,destino2,origem2,discos);//VERFICA AS CORDENADAS DO USUARIO
                    cronometro(2,25);


            }while(mat[7-disco][2]!=1);

            if(cont == Num_min)//SE A QUANTIDADE DE JOGADAS FOR A MESMA DA QUANTIDADE MINIMA DE MOVIMENTOS
            {
                Movimentos = fopen(arquivo,"a");
                fprintf(Movimentos,"Parabens Voce Conseguiu o Numero Minimo De Movimentos\n");//ESCREVE
                fprintf(Movimentos,"Seu Tempo Foi : %d",seg);
            }

            fclose(Movimentos);
            system("color 71");
            parabens();//ESCREVE PARABENS
            Sleep(100);
            system("color 72");
            Sleep(100);
            system("color 83");
            Sleep(100);
            system("color c4");
            Sleep(100);
            system("color 45");
            Sleep(100);
            system("color f6");
            gotoxy(2,24);
            printf("PARABENS VOCE GANHOU !!!\n\n");

            //CALCULAR O SCORE PARA O USUARIO

            num_di_float = pow(disco,disco);
            num_di_float = num_di_float*num_di_float;

            rec_score = ((num_di_float/((seg+1)*cont))*100);

            rec_score = pow(rec_score,0.33);

            printf("\n\nO Seu Score Na Partida foi : %.2f \n\n",rec_score);//IMPRIME O  ESCORE

            Movimentos = fopen(arquivo,"a");

            fprintf(Movimentos,"\nO Seu Score Na Partida Foi : %.2f\n",rec_score);//ESCREVE NO ARQUIVO
            fclose(Movimentos);

            ranking = fopen("score.txt","ab");

            fwrite(Dados.Nome,sizeof(Dados.Nome),1,ranking);//ESCREVE O NOME DO USUARIO
            fwrite(&rec_score,sizeof(rec_score),1,ranking);//ESCREVE SEU SCORE


            fclose(ranking);
            cronometro(2,25);
            cont = 0;
            seg = 0;
            gotoxy(2,26);
            system("pause");
            system("cls");

            Movimentos = fopen(arquivo,"r");
            if(Movimentos == NULL)
            {
                printf("Nao Foi Possivel Abrir o Arquivo!");//
                system("pause");
                exit(1);
            }

            while(fgets(text,100,Movimentos)!=NULL)//IMPRIME OS MOVIMENTOS FEITOS PELO JOGADOR
            {
                printf("\n %s",text);
            }
            printf("\n\n");
            fclose(Movimentos);
            system("pause");
            system("cls");
            main();
            break;
            case'T'://MODO TREINO

            treino = fopen("relatorio.txt","w");
            fclose(treino);
            for(i=0;i<100;i++)
            {
                text[i] = ' ';
            }
            disco = 0;
            cont = 0;
            time_animacao();//TEMPO DA ANIMAÇÃO
            gera_matriz(mat,&disco);//MATRIS COM AS ESCOLHA DO USUARIO
            imprime_pilar(mat,discos);
            Num_min = pow(2,disco)-1;

            for (i=7-disco,k=0;i<linha;i++,k++)
            {
                for (j=centro-k-3;j<=centro+k+3;j++)
                {   system("color 70");
                    discos[i][j]=205;
                }
            }
            mat_interface(discos);//INTERFACE DO DISCO
            menu_tela_teste();//MENU DE TELA NO MODO TREINO

            do{
                do{
                    do{
                        do{
                            gotoxy(1,22);
                            printf("informe a sua origem :\t");//RECEBE ORIGEM DO USUARIO
                            gotoxy(24,22);
                            ori_conv = getche();
                            origem = ori_conv - 48;//CONERTE EM NUMERO
                            fflush(stdin);

                            if(origem == 20 || origem == 52)//DESISTIR DA PARTIDA
                            {
                                system("cls");
                                main();
                            }
                            if((origem == 37 || origem == 69) && cont!=0)//FUNÇÃO UNDO
                            {

                                undo = 1;
                                ImprimeUndo(nomeArq,mat,discos);
                                cont--;//DECREMETA UM MOVIMENTO DO USUARIO
                                Undorelatorio(nomeArq);
                                system("cls");
                                //MONTA A TELA NOVAMENTE DEPOIS DE TER SIDO LIMPA
                                menu_tela_teste();
                                imprime_pilar(mat,discos);
                                mat_interface (discos);
                                //undo = 0;
                            }
                            else
                                undo=0;
                        }while(undo==1);


                            gotoxy(1,24);
                            printf("Informe o Seu Destino Para o Disco :\t");//RECEBER O DESTINO DO USUARIO
                            des_conv = getche();
                            destino = des_conv - 48;//CONVERTE EM NUMERO
                            fflush(stdin);
                            if( destino == 20 || destino == 52)//ABANDONAR PARTIDA
                            {
                                system("cls");
                                main();
                            }
                            if((destino == 37 || destino == 69) && cont!=0)//FUNÇÃO UNDO
                            {

                                undo = 1;
                                ImprimeUndo(nomeArq,mat,discos);
                                cont--;//DECREMENTA O CONTADOR DE JOGADAS DO USUARIO
                                Undorelatorio(nomeArq);
                                system("cls");
                                //REFAZ A TELA DEPOIS DE LIMPA
                                menu_tela_teste();
                                imprime_pilar(mat,discos);
                                mat_interface (discos);
                            }
                            else
                                undo = 0;
                   }while(undo == 1);
                    //system("cls");

                    mat_interface (discos);
                    menu_tela_teste();

                }while(origem<1 || origem >3 || destino <1 || destino>3 || origem == destino);
                    // SO SAI DO LAÇO DEPOIS DA JOGADA TERCIDO VALIDA
                origem2 = analisamovimento(origem);//CONVERTE ORIGEM PARA A MATRIS DE CARACTER PODER USAR
                destino2 = analisamovimento(destino);//CONVERTE DESTINO PARA A MATRIS DE CARACTER PODER USAR
                system("cls");

                //imprime_pilar(mat,discos);

                movimenta_torre(mat,destino2,origem2,discos);//VERIFICA A COORDENADA DO JOGADOR
                menu_tela_teste();//MENU DE TELA NO MODO TREINO

        }while(mat[7-disco][2]!=1);
        treino = fopen("treino.txt","a");
        if(cont == Num_min)//
        {
            fprintf(treino,"Parabens o Numero De Movimentos foi Minino");
        }

        fclose(treino);
        system("color 71");
        parabens();//ESCREVE PARABENS
        Sleep(100);
        system("color 72");
        Sleep(100);
        system("color 83");
        Sleep(100);
        system("color c4");
        Sleep(100);
        system("color 45");
        Sleep(100);
        system("color f6");
        gotoxy(2,24);
        printf("\n\n\nPARABENS VOCE GANHOU !!!\n\n");
        gotoxy(2,26);
        system("pause");
        system("cls");

        treino = fopen("relatorio.txt","r");
        if(treino == NULL)
        {
            printf("Nao foi possivel abrir o arquivo!");
            system("pause");
            exit(1);
        }
        while(fgets(text,100,treino)!=NULL)//imprime relatorio para o usuario
        {
            printf("\n %s",text);
        }
        printf("\n\n");
        fclose(treino);
        system("pause");
        system("cls");
        main();

        break;

        case'R'://RECURÇÃO DA RELOSUÇÃO

            gera_matriz(mat,&disco);//GERA MATRIZ COM A QUANTIDADE DE DISCO DO USUARIO
            imprime_pilar(mat,discos);

            for (i=7-disco,k=0;i<linha;i++,k++)
            {
                for (j=centro-k-3;j<=centro+k+3;j++)
                {
                    discos[i][j]=205;//INICIALISAR A MATRIS DE CARACTERE
                }
            }

            MoveTorre(disco,Orig,Dest,Aux,mat,discos);//CHAMA A FUNÇÃO RECURSIVA
            printf("\n\n");
            system("pause");
            system("cls");
            main();
        break;

        case'E'://RANKING DE JOGADORES PARA O USUARIO
             ordena_score();//ORDENA A LISTA DE JOGADORES
             system("pause");
             main();//REURÇÃO DA MAIN
        break;
        case'S'://sair do jogo
            exit(1);
        break;
           }
        break;

        case'R'://IMPRIME O RANKING
            ordena_score();//ORDENA O ARQUIVO
            system("pause");
            system("cls");
            main();
        break;

        case'A'://SOBRE O JOGO
            {

             historia = fopen("historia_hanoi.txt","r");
             if(historia == NULL)
                {
                    printf("Nao foi possivel abrir o arquivo!");
                    system("pause");
                    exit(1);
                }

                while(fgets(text,100,historia)!=NULL)//IMPRIME AJUDA DO JOGO
                    {
                        printf("\n %s",text);
                    }
                    printf("\n\n");
                    fclose(historia);
                    system("pause");
                    system("cls");
                    main();
            }
        break;

        case'S'://SAIR
            exit(1);
        break;

    }
    return 0;
}
void imprime_torre(int mat[7][3])//IMPRIME A TORRE DA MATRIZ CONTROLE
{
    int i,j;

    for (i=0;i<7;i++)
     {
         for (j=0;j<3;j++)
        {
            printf("%2d",mat[i][j]);//IMPRIME
        }
         printf("\n");
     }
}
void gera_matriz(int mat[7][3],int *disco)//GERA UMA MATRIZ COM A QUANTIDADE DE DISCO ESCOLHIDA PELO JOGADOR
{
int i,j=1;

    do{
        printf("\n\n\n\n\t\t\tInforme a quantidade de disco (1->7) :\t");//NUMERO DE DISCO DO JOGO
        scanf("%d",disco);
        fflush(stdin);
        system("cls");
    }while(*disco<1 || *disco>7);

    for (i=7-*disco;i<7;i++)
    {
        mat[i][0] = j;
        j=j+1;
    }

}
void mat_interface(char discos[linha][coluna] )//INTERFASE DA MATRIZ
{
    int i,j;

    torre_de_hanoi();//IMPRIME NOME TORRE DE HANOI
    printf("\n\n");

    for(i=0;i<linha;i++)
    {
        for(j=0;j<coluna;j++)
        {
            printf("%c",discos[i][j]);//IMPRIME A MATRIZ DE CARACTER  QUE CONTROLA OS DISCOS
        }
        printf("\n");
    }
    gotoxy(0,18);
    for(i=0;i<80;i++)
        printf("%c",205);//LISTA EM BAIXO DO DISCOS

    gotoxy(9,16);
    printf("<I>");//PRIMEIRA TORRE
    gotoxy(35,16);
    printf("<II>");//SEGUNDA TORRE
    gotoxy(62,16);
    printf("<III>");//TERCEIRA TORRE

}
int analisamovimento(int n)//ANALISA MOVIMENTO PARA A MATRIS DE CARACTER SE ADQUAR
{
     if(n==1)// SE FOR 1 CONVETE PARA 9 DE CARACTER
    {
        return 9;
    }
    else if(n==2)// SE FOR 2 CONVETE PARA 36 DE CARACTER
    {
        return 36;
    }
    else if(n==3)// SE FOR 3 CONVETE PARA 63 DE CARACTER
    {
        return 63;
    }
}
void movemat(int destino2,int origem2,char discos[linha][coluna],int i,int j, int p)//TRACA OS DISCOS POR ESPAÇOS EM BRANCO  NA HORA DE MOVER
{
    int k;

    for(k=destino2-2-i;k<=destino2+2+i;k++)
    {
        discos[j][k]=205;//CARACTER DO DISCO
    }
    for(k=origem2-2-i;k<=origem2+2+i;k++)
    {
        discos[p][k]=' ';//ESPACO EM BRANCO
    }

}
char menu()//MENU DE ESCOLHA DO USUARIO
{
    char opcao;
        do{
            gotoxy(32,12);
            printf(" %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",201,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,187);

            gotoxy(32,13);
            printf(" %c INICIAR :    (I) %c\n ",186,186);
            gotoxy(32,14);
            printf(" %c                  %c\n",186,186);
            gotoxy(32,15);
            printf(" %c RANKING :    (R) %c\n",186,186);
            gotoxy(32,16);
            printf(" %c                  %c\n",186,186);
            gotoxy(32,17);
            printf(" %c SOBRE :      (A) %c\n",186,186);
            gotoxy(32,18);
            printf(" %c                  %c\n",186,186);
            gotoxy(32,19);
            printf(" %c SAIR :       (S) %c\n",186,186);
            gotoxy(32,20);
            printf(" %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,188);

            printf("\n\n\n\t\t\t\t O que deseja fazer ? ");
            opcao = getche();
            opcao = toupper(opcao);
            system("cls");
    }while(opcao!='I'&& opcao!='R'&&opcao!='A'&&opcao!='S');

    return opcao;//RETORNA A ESCOLHA DO USUARIO

}
char menu2()//MENU DE ESOLHA DO USUARIO PARA ESCOLHA DE JOGAR
{
    char opcao2;
    do{
    gotoxy(32,12);
    printf(" %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",201,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,187);
    gotoxy(32,13);
    printf(" %c JOGAR :     (J)  %c\n ",186,186);
    gotoxy(32,14);
    printf(" %c                  %c\n",186,186);
    gotoxy(32,15);
    printf(" %c TREINO :    (T)  %c\n ",186,186);
    gotoxy(32,16);
    printf(" %c                  %c\n",186,186);
    gotoxy(32,17);
    printf(" %c RESOLUCAO : (R)  %c",186,186);
    gotoxy(32,18);
    printf(" %c                  %c\n",186,186);
    gotoxy(32,19);
    printf(" %c RANKING :   (E)  %c",186,186);
    gotoxy(32,20);
    printf(" %c                  %c\n",186,186);
    gotoxy(32,21);
    printf(" %c SAIR :      (S)  %c\n",186,186,186);
    gotoxy(32,22);
 printf(" %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,188);
    printf("\n\n\n\t\t\t\tO que deseja fazer ? ");
    opcao2 = getche();
    opcao2=toupper(opcao2);
    system("cls");
    }while(opcao2!='J'&&opcao2!='R'&&opcao2!='S'&&opcao2!='T'&&opcao2!='E');

    return opcao2;//RETORNA A ESCOLHA DO USUARIO
}
void imprime_pilar(int mat[7][3],char discos[linha][coluna])//IMPRIME O PILAR NA HORA DO MOVIMENTO DO DISCO
{
    int i,j,cont=0,cont1=0,cont2=0;

    for (i=0;i<7;i++)
    {
        if(mat[i][0]==0)
        {
            cont++;
        }
    }

    for (i=0;i<cont;i++)
    {
        discos[i][9]=186;//CARACTER DE TORRE
    }

    for (i=0;i<7;i++)
    {
        if(mat[i][1]==0)
        {
            cont1++;
        }
    }

    for (i=0;i<cont1;i++)
    {
        discos[i][36]=186;
    }
    for (i=0;i<7;i++)
    {
        if(mat[i][2]==0)
        {
            cont2++;
        }
    }
    for (i=0;i<cont2;i++)
    {
        discos[i][63]=186;
    }

}
void torre_de_hanoi()//TEXTO TORRE DE HANOI
{
gotoxy(2,1);
printf("\t _____                         _        _   _                   _ \n");
gotoxy(2,2);
printf("\t|_   _|                       | |      | | | |                 (_)\n");
gotoxy(2,3);
printf("\t  | | ___  _ __ _ __ ___    __| | ___  | |_| | __ _ _ __   ___  _ \n");
gotoxy(2,4);
printf("\t  | |/ _ \\| '__| '__/ _ \\  / _` |/ _ \\ |  _  |/ _` | '_ \\ / _ \\| |\n");
gotoxy(2,5);
printf("\t  | | (_) | |  | | |  __/ | (_| |  __/ | | | | (_| | | | | (_) | |\n");
gotoxy(2,6);
printf("\t  \\_/\\___/|_|  |_|  \\___|  \\__,_|\\___| \\_| |_/\\__,_|_| |_|\\___/|_|\n");

}
void movimenta_torre (int mat[7][3],int destino2,int origem2,char discos[linha][coluna])//FUNÇÃO QUE VERIFICA A JOGADA E VALIDA OU NAO
{
    int i,j,aux=0;

    for (i=0;i<7;i++)
    {
        if(mat[6][origem-1]!=0 && mat[i][origem-1]!=0 && aux!=1)
        {
            if(mat[6][destino-1]==0 && aux!=1)
            {
                mat[6][destino-1] = mat[i][origem-1];//TROCANDO OS DISCO DE LUGAR
                torre_de_hanoi();//ESCREVE TORRE DE HANOI
                menu_tela();//MENU DE TELA
                mat_interface (discos);//INTERFACE DE TORRE
                animacao_torre(origem2,destino2,6,mat[i][origem-1],i);//ANIMAÇÃO NA HORA DE MOVER OS DISCO
                if(undo!=1)//EMCREMENTA CONTADOR DE MOVIMENTOS
                    cont++;
                movemat(destino2,origem2,discos,mat[i][origem-1],6,i);
                mat[i][origem-1]=0;
                aux = 1;
                    treino = fopen("treino.txt","a");//ESCREVE AS CORDENADOS DO JOGO NO ARQUIVO DE RELATORIO DO USUARIO
                    fprintf(treino,"%d -> %d\n",origem,destino);
                    fclose(treino);
                if(undo!=1)
                {

                    treino = fopen("relatorio.txt","a");//ESCREVER NO MODO TREINO AS JOGADAS DO USUARIO
                    fprintf(treino,"%d -> %d\n",origem,destino);
                    fclose(treino);
                }

            }
            else
            {
                for (j=0;j<7;j++)
                {
                    if(mat[j][destino-1]!=0 && mat[i][origem-1]<mat[j][destino-1]&& aux!=1)
                    {

                        mat[j-1][destino-1] = mat[i][origem-1];//ATRIBUINDO O DISCO PARA O DESTINO
                        if(undo!=1)
                            cont++;
                        torre_de_hanoi();//NOME TORRE DE HANOI
                        menu_tela();//MENU DE TELA
                        mat_interface (discos);//INTERFASE DE DISCO
                        animacao_torre(origem2,destino2,j-1,mat[i][origem-1],i);//TRANSIÇÃO DE DISCO
                        movemat(destino2,origem2,discos,mat[i][origem-1],j-1,i);
                        mat[i][origem-1] = 0;
                        aux =1;
                        treino = fopen("treino.txt","a");
                        fprintf(treino,"%d -> %d\n",origem,destino);
                        fclose(treino);

                        if(undo!=1)//NAO GRAVAR A CONDERNADAS DO UNDO QUANDO FOR DESFASER
                        {

                            treino = fopen("relatorio.txt","a");
                            fprintf(treino,"%d -> %d\n",origem,destino);
                            fclose(treino);
                        }
                    }
                    else if(mat[j][destino-1]!=0 && mat[i][origem-1]>mat[j][destino-1]&& aux!=1)
                        aux=1;
                }
            }
        }
    }
    imprime_pilar(mat,discos);//IMPRIME PILAR NA TELA
    mat_interface(discos);//INTERFASE DE MATRIZ

    aux =  0;
}
void MoveTorre(int n, int Orig,int Dest, int Aux,int mat[7][3],char discos[linha][coluna])//FAZ A RECURÇÃO PARA A RESOLUÇÃO DO JOGO
{
    if(n==1)
    {
        MoveDisco(Orig,Dest,mat,discos);
    }else
    {
        MoveTorre(n-1,Orig,Aux,Dest,mat,discos);
        MoveDisco(Orig, Dest,mat,discos);
        MoveTorre(n-1, Aux, Dest, Orig,mat,discos);

    }
}
void MoveDisco(int Orig,int Dest,int mat[7][3],char discos[linha][coluna])//TROCA AS POSIÇÕE DO DISCO PARA SE RESOLVER
{
    int origem2;
    int destino2;

    origem = Orig;
    destino = Dest;

    origem2 = analisamovimento(Orig);
    destino2 = analisamovimento(Dest);

    movimenta_torre(mat,destino2,origem2,discos);
}
void perfil()//CRIA UM PERFIL NOVO PARA CADA USUARIO
{

    int ved;
    do{
        printf("\nInforme o Nome Do Jogador : ");
        gets(Dados.Nome);
        system("cls");
    }while(strcmp(Dados.Nome,"\n")==-1);//VERIFICA SE O USUARIO NAO ENTROU COM UM EMTER
    strcpy(arquivo,Dados.Nome);

    Time_and_Date_system();//TEMPO DO SISTEMA
    //CONCATENA O NOME DO USUARIO COM DATA E HORA DO SISTEMA
    limpa_str();
    altera_caracter(dia);
    strcat(arquivo," ");
    strcat(arquivo,str);
    limpa_str();//LIMPA OS LIXO DA STR
    altera_caracter(mes);
    strcat(arquivo,"-");
    strcat(arquivo,str);
    limpa_str();
    altera_caracter(ano);
    strcat(arquivo,"-");
    strcat(arquivo,str);
    limpa_str();
    altera_caracter(horas);
    strcat(arquivo,"-");
    strcat(arquivo,str);
    limpa_str();
    altera_caracter(minutos);
    strcat(arquivo,"-");
    strcat(arquivo,str);
    limpa_str();
    altera_caracter(segundos);
    strcat(arquivo,"-");
    strcat(arquivo,str);
    strcat(arquivo,".txt");
    Movimentos = fopen(arquivo , "a");


}
void altera_caracter(int m)//CONVERTE OS CARACTER DA HORA E DATA PARA STRING PARA SER CONCATENADO
{

    int n,i=0;
    n=m;
    while((n/10)>10)
    {
        i++;
        n = n/10;
    }
    if((n/10)!=0)
        i++;

    while((m/10)>0)
    {
        str[i] = 48+(m%10);
        m = m/10;
        i--;
    }
    str[i] = 48 + (m%10);

    //printf("%s\n",str);

}
void Time_and_Date_system()//DATA E HORA DO SISTEMA
{

struct tm *local;//STRING QUE CAPITURA DATA E HORA DO SISTEMA

time_t t;
t= time(NULL);


local=localtime(&t);

dia=local->tm_mday;
mes=local->tm_mon+1;
ano = ((local->tm_year+1900)%2000);
segundos = local->tm_sec;
minutos = local->tm_min;
horas = local->tm_hour;

}
char menu_escolha()//MENU ESCOLA PARA JOGAR
{
    char escolha;

            gotoxy(25,12);
            printf(" %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",201,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,187);


            gotoxy(25,13);
            printf(" %cCriar Uma Novo jogador :    (1)      %c\n ",186,186,186);
            gotoxy(25,14);
            printf(" %c                                     %c\n",186,186);
            gotoxy(25,15);
            printf(" %cListar Jogadores :          (2)      %c\n",186,186,186);
            gotoxy(25,16);
            printf(" %c                                     %c\n",186,186);
            gotoxy(25,17);
            printf(" %cLimpar Lista de jogadores : (3)      %c\n",186,186,186);
            gotoxy(25,18);
            printf(" %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,188);

            printf("\n\n\n\t\t\t Selecione a Opcao Desejada : ");
            escolha = getch();

            return escolha;//RETORNA A ESCOLHA DO USUARIO
}
void parabens()//IMPRIME PARABENS
{
gotoxy(2,1);
printf("                ______               _                                      \n");
Sleep(200);
gotoxy(2,2);
printf("                | ___ \\             | |                                    \n");
Sleep(200);
gotoxy(2,3);
printf("                | |_/ /_ _ _ __ __ _| |__   ___ _ __  ___                   \n");
Sleep(200);
gotoxy(2,4);
printf("                |  __/ _` | '__/ _` | '_ \\ / _ \\ '_ \\/ __|                   \n");
Sleep(200);
gotoxy(2,5);
printf("                | | | (_| | | | (_| | |_) |  __/ | | \\__ \\                    \n");
Sleep(200);
gotoxy(2,6);
printf("                \\_|  \\__,_|_|  \\__,_|_.__/ \\___|_| |_|___/                  \n");
Sleep(200);

}
void List_jogador()//LISTA A LISTA DE JOGADORES
{
    FILE *jogadores;
    tscore nome;
    jogadores = fopen("jogadores.txt","r+b");

    char jogador[30],auxnome[30]={ };
    int Nome_arq;
    int cont =1,i=0,j;

    if (jogadores == NULL)
    {
        printf("Nao Foi Possivel Abrir o Arquivo");
        exit(1);
    }


    while(!feof(jogadores))
    {
        fseek(jogadores,sizeof(arquivo)*i,SEEK_SET);
        fread(auxnome,sizeof(auxnome),1,jogadores);
        i++;
    }
    i--;
    for(j=0;j<i;j++)
    {
        fseek(jogadores,sizeof(arquivo)*j,SEEK_SET);
        fread(auxnome,sizeof(auxnome),1,jogadores);
        printf("\n%d -> %s\n",cont,auxnome);
        cont++;
    }
// ABRIR DETERMINADO ARQUIVO PARA VISIALIZAR A JOGADAS DO USUARIO
    printf("\n\n");
    fclose(jogadores);
    printf("Informe o Arquivo Que Deseja Ver o Historico \nOs Arquivos Estao Oganizados Por : Nome dia-mes-ano-hora-min-sec\n\n");
    do{
        scanf("%d",&Nome_arq);
        jogadores = fopen("jogadores.txt","r+b");

        fseek(jogadores,sizeof(arquivo)*(Nome_arq-1),SEEK_SET);
        fread(auxnome,sizeof(auxnome),1,jogadores);

        fclose(jogadores);

        system("pause");

        jogadores = fopen(auxnome,"rb");


        if(jogadores == NULL)
        {
            printf("\n O Nome nao foi Encontrado Tente Novamente OU '0' Para sair!\n");
        }
        if(Nome_arq == 0)
        {
            system("cls");
            main();
        }
    }while(jogadores == NULL);

    system("cls");
    while(fgets(jogador,1000,jogadores)!= NULL)
    {
        printf("\n%s",jogador);
    }
    printf("\n\n");
    system("pause");
    system("cls");
    main();
}
void Limpe_list()//EXCCLUI OS JOGADORES ARMAZENADOS NO ARQUIVO
{
   int i;
   FILE *jogadores;
   jogadores = fopen("jogadores.txt","w");

   fclose(jogadores);

    gotoxy(12,3);
    system("cls");

    printf(" \n\n\t\t\tExcluido Aguarde......");// funcao EXCLUIR ...

    gotoxy(1,10);
    for(i=1;i<14;i++)
    {
        Sleep(200); //retarda em 100 milisegundos
        printf("_______");
    }

    system("cls");//limpamdo a tela

   printf("\n\n\n\t\t\tO Arquivo Excluido Com Sucesso !\n\n\n\n");//INFO ARQUIVO FOI EXCUIDO
   Sleep(100);
   system("pause");
   system("cls");
   main();
}
char menu3()//MENU DE ESCOLHA NA HORA QUE O USUARIO TA JOGANDO
{
    char opcao;
        do{
           gotoxy(29,12);
    Sleep(100);
    printf(" %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",201,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,187);

            gotoxy(29,13);
            Sleep(100);
            printf(" %c RANKING             (E)   %c\n ",186,186);
            gotoxy(29,14);
            Sleep(100);
            printf(" %c                           %c\n",186,186);
            gotoxy(29,15);
            printf(" %c VOLTAR AO JOGO :    (C)   %c\n",186,186);
            gotoxy(29,16);
            Sleep(100);
            printf(" %c                           %c\n",186,186);
            gotoxy(29,17);
            printf(" %c REINICIAR GAME :    (R)   %c\n",186,186);
            gotoxy(29,18);
            printf(" %c                           %c\n",186,186);
            gotoxy(29,19);
            Sleep(100);
            printf(" %c ABANDONAR PARTIDA : (A)   %c\n",186,186);
            gotoxy(29,20);
            Sleep(100);
            printf(" %c                           %c\n",186,186);
            gotoxy(29,21);
            Sleep(100);
            printf(" %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,188);
            Sleep(100);

            printf("\n\n\n\t\t\t\t O que deseja fazer ? ");
            opcao = getche();
            opcao = toupper(opcao);
            system("cls");
    }while(opcao!='E'&& opcao!='C'&&opcao!='R'&&opcao!='A');

    return opcao;//RETORNA ESCOLHA DO USUARIO
}
void limpa_str()//LIMPA STRING PARA NÃO ARMAZENAR LIXO DE NOMES ANTIGOS
{
    int i;

    for (i=0;i<100;i++)
    {
        str[i] = 0;
    }
}
void cronometro(int c,int l)//CRONOMETRO EM SEGUNDOS
{
     gotoxy(76,24);
     printf("%d",seg);
     gotoxy(c,l);
     Sleep(1000);
     seg++;
}
void menu_tela()//MENU DE TELA BASICO NA HORA DO JOGO
{
            gotoxy(55,19);
            printf(" %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",201,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,187);
            gotoxy(55,20);
            printf(" %c MENU/PAUSA :     (M)  %c\n",186,186);
            gotoxy(55,21);
            printf(" %c                       %c\n",186,186);
            gotoxy(55,22);
            printf(" %c MOVIMENTOS :          %c\n",186,186);
            gotoxy(55,23);
            printf(" %c                       %c\n",186,186);
            gotoxy(55,24);
            printf(" %c TEMPO:                %c\n",186,186);
            gotoxy(55,25);
            printf(" %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,188);

            gotoxy(76,22);
            printf("%d",cont);
}
void menu_tela_teste()//MENU DE TELA SIMPLES NO MODO TREINO
{
            gotoxy(55,19);
            printf(" %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",201,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,187);
            gotoxy(55,20);
            printf(" %c DESISITIR  :     (D)  %c\n",186,186);
            gotoxy(55,21);
            printf(" %c                       %c\n",186,186);
            gotoxy(55,22);
            printf(" %c DESFAZER   :     (U)  %c\n",186,186);
            gotoxy(55,23);
            printf(" %c                       %c\n",186,186);
            gotoxy(55,24);
            printf(" %c MOVIMENTOS :          %c\n",186,186);
            gotoxy(55,25);
            printf(" %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,188);
            printf("\n\n");

            gotoxy(76,24);
            printf("%d",cont);
}
void ImprimeUndo(char nomeArq[],int mat[7][3],char discos[linha][coluna])//FUNÇÃO QUE REALIZAO O UNDO
{
    FILE *relatorio;
    int cont2=0;
    int a,b,c;

    relatorio = fopen("relatorio.txt","r");

    if(relatorio==NULL)
    {
        printf("Nao foi possivel abrir seu arquivo...\n");
        exit(1);
    }

    while(!feof(relatorio))//LE O ARQUIVO ATE O FIM E CAPITURA AS JOGADAS EFETUADAS POR ELE
    {
        fscanf(relatorio,"%d -> %d\n",&a,&b);
        cont2++;

        if(cont2==cont)
        {
            origem = b;
            destino = a;

            a = analisamovimento(a);//ALTERA ORIGEM
            b = analisamovimento(b);//ALTERA DESTINO
            movimenta_torre(mat,a,b,discos);//PASSA OS PARAMENTROS PARA SER EFETUADO A TROCA DE POSIÇÕE NO UNDO
        }
    }
    fclose(relatorio);

}
void Undorelatorio(char nomeArq[])//AUXILIAR PARA  O UNDO
{

    FILE *relatorio;
    FILE *nrelatorio;

    int cont2=0,a,b;

    relatorio = fopen(nomeArq,"r");
    nrelatorio = fopen("nrelatorio.txt","w");//RELATORIO AUXILIAR PARA TROCAR AS CORDENADAS E REALIZAR A TROCA

    if(relatorio==NULL || nrelatorio==NULL)
    {
        printf("Nao foi possivel abrir seu arquivo...\n");
        exit(1);
    }
    fclose(nrelatorio);
    rewind(relatorio);//POSICIONAR O CURSOR NO INICIO DO ARQUIVO

    nrelatorio = fopen("nrelatorio.txt","a");

    while(!feof(relatorio))
    {
        if(cont2==cont)
            break;

        fscanf(relatorio,"%d -> %d\n",&a,&b);//LE AS COORDENADAS SALVAS PELO USUARIO
                                                // E
        fprintf(nrelatorio,"%d -> %d\n", a,b);// ESCREVER NO RELATORIO AUXILIAR

        cont2++;

    }
    fclose(nrelatorio);
    fclose(relatorio);

    relatorio = fopen(nomeArq,"w");
    fclose(relatorio);

    nrelatorio = fopen("nrelatorio.txt","r");
    relatorio = fopen(nomeArq,"a");
    rewind(nrelatorio);

    while(!feof(nrelatorio))//AGORA REALIZAR O PASSO INVERSO
    {
        fscanf(nrelatorio,"%d -> %d\n",&a,&b);//LE DE RELATORIO AUXILIAR E
        fprintf(relatorio,"%d -> %d\n", a,b);// ESCREVER E RELATORIO DO UNDO
    }

    fclose(relatorio);

}
void ordena_score()//ORDENA A LISTA DE NOMES E ESCORE SALVOS PELO JOGADOR
{
    int i=0,j,term1 = 0 ,term2 = 0,contador = 0,k=0;
    float conf;//VARIAVEL AXILIAR PARA CONTAR QUANTOS SCORE POSSUI DENTRO DO ARQUIVO
    tscore nome1,nome2,prit_per;//VARIAVEIS PARA A TROCA  DO TIPO TSCORE

    ranking = fopen("score.txt","r+b");

    while(!feof(ranking))//CONTAR QUANTOS PERFIL TEM GRAVADOS DENTRO DO ARQUIVO
    {
        fseek(ranking,(sizeof(tscore)*i)+sizeof(nome2.Nome),SEEK_SET);//POSICIONA O CURSOR NO SCORER E VER SE E DIFERNTE DE 0.0
        fread(&conf,sizeof(conf),1,ranking);// LE O SCORE

        if(conf != 0.0)
        {
            contador ++;
        }
        i++;

    }

    for(i=0;i<contador -1;i++)
    {
        for(j=0;j<contador-2;j++)
        {
            fseek(ranking,(sizeof(tscore)*j)+sizeof(nome2.Nome),SEEK_SET);
            fread(&term1,sizeof(term1),1,ranking);
            fseek(ranking,(sizeof(tscore)*(j+1))+sizeof(nome2.Nome),SEEK_SET);
            fread(&term2,sizeof(term2),1,ranking);

            if(term1 < term2)//COMPARA OS DOIS PRIMEIROS SCORE DO ARQUIVO
            {
                //SE FOR MAIOR O SEGUNDO REALIZA A TROCA DENTRO MESMO DO ARQUIVO
               fseek(ranking,sizeof(tscore)*j,SEEK_SET);
               fread(nome1.Nome,sizeof(nome1.Nome),1,ranking);
               fseek(ranking,(sizeof(tscore)*j)+sizeof(nome1.Nome),SEEK_SET);
               fread(&nome1.pontos,sizeof(nome1.pontos),1,ranking);

               fseek(ranking,sizeof(tscore)*(j+1),SEEK_SET);
               fread(nome2.Nome,sizeof(nome2.Nome),1,ranking);
               fseek(ranking,(sizeof(tscore)*(j+1))+sizeof(nome2.Nome),SEEK_SET);
               fread(&nome2.pontos,sizeof(nome2.pontos),1,ranking);

                //ESCREVENTO OS ARQUIVOS TROCANDO DE FORMA ORDENADA
               fseek(ranking,sizeof(tscore)*j,SEEK_SET);
               fwrite(nome2.Nome,sizeof(nome2.Nome),1,ranking);
               fseek(ranking,(sizeof(tscore)*j)+sizeof(nome2.Nome),SEEK_SET);
               fwrite(&nome2.pontos,sizeof(nome1.pontos),1,ranking);
               fseek(ranking,sizeof(tscore)*(j+1),SEEK_SET);
               fwrite(nome1.Nome,sizeof(nome1.Nome),1,ranking);
               fseek(ranking,(sizeof(tscore)*(j+1))+sizeof(nome2.Nome),SEEK_SET);
               fwrite(&nome1.pontos,sizeof(nome1.pontos),1,ranking);

            }
        }
    }

            for(k=0;k<contador-1;k++)//IMPRIMINDO AS LISTA DE NOMES ORDENADAS
            {

            fseek(ranking,sizeof(tscore)*k,SEEK_SET);
            fread(prit_per.Nome,sizeof(prit_per.Nome),1,ranking);
            printf("\nNome : %s\n",prit_per.Nome);//IMPRIME NOME

            fseek(ranking,(sizeof(tscore)*k)+sizeof(prit_per.Nome),SEEK_SET);
            fread(&prit_per.pontos,sizeof(prit_per.pontos),1,ranking);
            printf("Pontos : %.2f\n\n",prit_per.pontos);//IMPRIME SCORE

            }
            system("pause");//PAUSAR A TELA

}
void animacao_torre(int orig, int dest, int tam_torre, int mat, int indice)//REALIZA A TRANSIÇÃO DOS DISCOS
{

    int i,j,k;

    orig++;
    dest++;
    tam_torre++;
    indice++;

    if(orig<dest)// SE ORIGEM FOR MAIOR QUE DESTINO
    {
        for(k=orig-mat-2;k<=orig+mat+2;k++)
        {
            gotoxy(k,indice+8);
            if(k==orig)
            {
                printf("%c",186);//IMPRIME CARATERE EM BRANCO ENQUANDO O DISCO ESTA MOVENDO
                printf(" ");//APAGA O DISCO NA SAIDA
            }
            else
                printf(" ");
        }
        for(i=indice;i>0;i--)
        {
            for(k=orig-mat-2;k<=orig+mat+2;k++)//FAZANDO O DISCO SE MOVER DEPENDO DAS COODENADAS
            {
                gotoxy(k,i+8);
                printf("%c",205);

            }
            Sleep(time_animation);//TEMPO DE ANIMAÇÃO DA PARTIDA
            for(k=orig-mat-2;k<=orig+mat+2;k++)
            {
                gotoxy(k,i+8);
                if(k==orig)
                {
                    printf("%c",186);
                    printf(" ");
                }

                else
                    printf(" ");
            }
        }
        for(j=orig;j<=dest;j+=4)
        {
            for (k=j-mat-2;k<=j+mat+2;k++)
            {
                gotoxy(k,i+8);
                printf("%c",205);//CARACTER DO DISCO
            }
            Sleep(time_animation);
            for (k=j-mat-2;k<=j+mat+2;k++)
            {
                gotoxy(k,i+8);
                printf(" ");//APAGAR O DISCO
            }
        }
        for(i++;i<tam_torre+1;i++)
        {
            for (k=dest-mat-2;k<=dest+mat+2;k++)
            {
                gotoxy(k,i+8);
                printf("%c",205);
            }
            Sleep(time_animation);//TEMPO DE ANIMAÇÃO
            for (k=dest-mat-2;k<=dest+mat+2;k++)
            {
                gotoxy(k,i+8);
                if(k==dest)
                {
                    printf("%c",186);
                    printf(" ");//ESPAÇO EM BRANCO
                }
                else
                    printf(" ");
            }
        }
    }else if(orig>dest)// SE ORIGEM FOR MAIOR QUE DESTINO
    {
        for(k=orig-mat-2;k<=orig+mat+2;k++)
        {
            gotoxy(k,indice+8);
            if(k==orig)
            {
                printf("%c",186);
                printf(" ");
            }
            else
                printf(" ");
        }
        for(i=indice;i>0;i--)
        {
            for(k=orig-mat-2;k<=orig+mat+2;k++)
            {
            gotoxy(k,i+8);
                printf("%c",205);//CARACTER DE DISCO
            }
            Sleep(time_animation);
            for(k=orig-mat-2;k<=orig+mat+2;k++)
            {
                gotoxy(k,i+8);
                if(k==orig)
                {
                   printf("%c",186);
                   printf(" ");
                }
                else
                    printf(" ");
            }
        }
        for(j=orig;j>=dest;j-=4)
        {
            for (k=j-mat-2;k<=j+mat+2;k++)
            {
                gotoxy(k,i+8);
                printf("%c",205);
            }
            Sleep(time_animation);
            for (k=j-mat-2;k<=j+mat+2;k++)
            {
                gotoxy(k,i+8);
                printf(" ");
            }
        }
        for(i++;i<tam_torre+1;i++)
        {
            for (k=dest-mat-2;k<=dest+mat+2;k++)
            {
                gotoxy(k,i+8);
                printf("%c",205);
            }
            Sleep(time_animation);//TEMPO DE ANIMAÇÃO
            for (k=dest-mat-2;k<=dest+mat+2;k++)
            {
                gotoxy(k,i+8);
                if(k==dest)
                {
                    printf("%c",186);
                    printf(" ");
                }
                else
                    printf(" ");//SUBSTITUIR ESPAÇÕS EM BRANCO
            }
        }
    }
}
//DESCOMNTE SE VOCE NAO TEM A CONIO.H
/*void gotoxy(int x, int y)
{
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}*/
void time_animacao()//IMPRIME O TEMPO DA ANIMAÇÃO PARA A ESCOLHA DO JOGADOR
{
            gotoxy(29,13);
            Sleep(100);
            printf(" %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",201,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,187);
            gotoxy(29,14);
            printf(" %c Informe a Velocidade da Animacao:  %c\n ",186,186);
            gotoxy(29,15);
            printf(" %c                                    %c\n",186,186);
            gotoxy(29,16);
            printf(" %c Em Milissegundos :                 %c\n",186,186);
            gotoxy(29,17);
            printf(" %c                                    %c\n",186,186);
            gotoxy(29,18);
            printf(" %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,188);
            gotoxy(51,16);
            scanf("%f",&time_animation);

}
