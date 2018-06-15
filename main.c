/*
 * Natan michel
  Marcelo colla

  esse codig88o � um jogo, no qual o usuario deve adivinhar o numero aleatorio gerado pelo sistema, dentro de um determinado intervado
  que � escolhido pelo usuario atravez de niveis.

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Incluimos as biblioteca abaixo para melhorar a interação com o jogo, com intuito de deixar
// o jogo menos verboso ao fazer leituras de comandos por exemplo
// #include <windows.h>
// #include <conio.h>

typedef struct user usuario;
struct user {
    int pt;
    char name[100];
    char lvl;
};
char name[100], msg[80], dificuldade;
int num = 0;

/*
 * Definições das funções
 */
int leitura_int (void);
void print_escolhas (void);
void escolha_P (int *ini, int *fim);
int leitura_menu (int *ini,int *fim);
void fullscreen (void);
int busca_binaria (int num,char s);
void telas_ASCII (char *url, char *msg);
int second_tela (void);
void gera_score (int cont);
void abre_score (void);
void init_resolve_game (int a, int b);
int resolve_game (int ini, int fim);
int escolhas[150];

// Intervalor escolhidos por o jogador
int intervalo_min (void);
int intervalo_max (void);
int jogadas = 0;

int main(void) {
    char url[] = "start.txt";
    int playgame = 0, menu = 0;

    fullscreen();
    do {
        telas_ASCII(url, "Digite 13 para comeca o game:");

        // playgame = getch();
        scanf("%d", &playgame);

    } while (playgame != 13);

    // system("CLS");
    // second_tela();

    int escolha = 0, ini = 0, fim = 99, busca = 0;
    srand((unsigned) time(NULL));

    do {
        // system("CLS");
        fflush(stdin);
        char urld[] = "first.txt";
        telas_ASCII(urld, "Ola, sua missão é descobrir o número aleatório sorteado... Boa Sorte!");

        // Leitura do nome do jogador
        printf("\n\n\n\n\n");
        printf("                                                                       Nome do jogador:\n");
        printf("                                                                    ");

        // gets(name);
        scanf(" %s", name);
        // system("CLS");

        // Niveis de dificuldade para iniciar o jogo
        print_escolhas();

        escolha = leitura_menu(&ini, &fim);
        if(escolha == 1) {
            escolha_P(&ini, &fim);
        }

        num = rand() << 15 + rand() % (fim-ini+1) + ini;

        // system("CLS");
        printf("                                                            Sorteando numero aleatorio entre: %d e %d\n", ini, fim);
        printf("                                                                             Valendo!!\n\n");

        printf("Olá %s, podemos iniciar o game:\n", name);
        printf("Precione qualquer tecla para jogar agora\nOu Digite 0 para que a gente resolva por você\n");
        scanf("%d", &menu);

        if (menu == 0) {
            init_resolve_game(ini, fim);
            busca = 27;
        } else {
            busca = busca_binaria(num, dificuldade);
        }

        num = 0;

    } while(busca != 27);

    return 0;
}

void init_resolve_game (int a, int b) {
    int resolve = resolve_game(a, b);

    printf("\n---------------------\n");
    printf("FIM DE JOGO valor [%d] encontrado!\nFORAM APENAS [%d] jogadas para encontrar.\n", resolve, jogadas);
    printf("---------------------\n\n");
}

int resolve_game (int ini, int fim) {
    int maior = ini > fim ? ini : fim,
        menor = ini > fim ? fim : ini,
        metade = ((maior - menor) / 2) + menor;

    jogadas += 1;
    printf("Valor Sorteado [%d], já foram [%d] jogadas!\n", metade, jogadas);

    if (metade == num) {
        return num;
    } else if (metade > num) {
        fim = metade;
    } else {
        ini = metade;
    }

    return resolve_game(ini, fim);
}

int leitura_menu(int *ini, int *fim) {
    /* @Params:
     * Recebemos por parametros os ponteiros que definem o inicio e fim do intervalo do rand que será sorteado
     */

    int menu;
    do {
        // dificuldade = getch();
        scanf(" %c", &dificuldade);
        menu = 1;

        if (dificuldade == 'E' || dificuldade == 'e') {
            (*fim) = 100;
        } else if(dificuldade == 'M'|| dificuldade == 'm') {
            (*fim) = 1000;
        } else if(dificuldade == 'H' || dificuldade == 'h') {
            (*fim) = 9999;
        } else if(dificuldade == 'F' || dificuldade == 'f') {
            (*fim) = 987654321;
        } else if(dificuldade == 'P' || dificuldade == 'p') {
            return 1;
        } else {
            menu = 0;
        }

    } while (menu != 1);

    return 0;
}


int intervalo_min () {
    printf("\nInsira o numero minimo:");

    return leitura_int();
}

int intervalo_max () {
    printf("Insira o numero maximo: ");

    return leitura_int();
}

/*
 * Opcao P:
 * Ao selecionar a opção P(definida por o jogador) este method será responsavel por definir o valor maximo e minimo
 */
void escolha_P(int *ini, int *fim) {

    do {
        *ini = intervalo_min();
        *fim = intervalo_max();

        // caso os numeros sejam iguais ele me fica pedindo ate que as entradas sejam diferentes
        if ((*ini) == (*fim)) {
            print_escolhas();
        }

    } while((*fim) == (*ini));

    /*
     * Caso o jogador inserir valores onde o valor inicial for menor que o valor maximo
     * Fizemos a troca desses valores para proseguir com o jogo
     */
    if (*ini > *fim) {
        int tr = *fim;

        *fim = *ini;
        *ini = tr;
    }

    printf("\n");
}

/*
 * Exibe as opções de escolha que cada jogador pode escolher, conforme as escolha do jogador
 * será o tamanho do intervalo sorteado!
 */
void print_escolhas (void) {
    char ascii_dificuldade[] = "lets.txt";

    // system("CLS");
    telas_ASCII(ascii_dificuldade, "O Seu proximo passo é escolha uma das dificuldade abaixo:");

    printf("\n\n\n\n");
    printf("Para EASY digite 'E'\n");
    printf("Para MEDIUM digite 'M'\n");
    printf("Para HARD digite 'H'\n");
    printf("Para FUCKING HARD digite 'F'\n");
    printf("Para escolher o intervalo digite 'P'\n\n\n\n\n\n");
}


/*
 * Este method garante que o jogador vai inserir um numero intereiro
 */
int leitura_int (void) {
    int aux, l, i;
    char is[100];

    do {
        aux = 0;
        scanf(" %[^\n]s", is);

        for(l = 0; is[l] != '\0'; l++) {
            if(is[l] < 48 || is[l] > 57) {
                aux = 1;
                break;
            }
        }

    } while(aux != 0);

    sscanf(is, "%d", &i);

    return i;
}


/*
 * Este method deixa o prompt em fullscreen
 * Ref .: http://...
 */
void fullscreen (void) {

//    keybd_event(VK_MENU  , 0x36, 0, 0);
//    keybd_event(VK_RETURN, 0x1C, 0, 0);
//    keybd_event(VK_RETURN, 0x1C, KEYEVENTF_KEYUP, 0);
//    keybd_event(VK_MENU  , 0x38, KEYEVENTF_KEYUP, 0);

}

/*
 * Aqui que a magica acontece
 * Este method faz a busca binaria manual, onde o jogador faz a sua aposta,
 * escolhendo o numero o qual ele acha ser o certo.
 */
int busca_binaria (int num, char s) {
    int i = 0, cont = 1;

    do {
        printf("%d Tentativa: ", cont);
        i = leitura_int();

        if(i < num) {
            printf("Eh maior\n\n");
        } else if(i > num) {
            printf("Eh menor\n\n");
        } else if(i == num) {
            // system("CLS");
            char menos[] = "ok.txt";
            telas_ASCII(menos, "UUhuuulll Muito Bommm");

            printf("\nParabens!! ACERTOU MISERAVI.\n");
            printf("\n-----------------\nJogador: ");

            puts(name);
            printf("Numero de tentativas: %d\n-----------------\n\n", cont);

            gera_score(cont);

            printf("Para novo jogo digite qualquer tecla.\n");
            printf("Precione ESC para sair.\n\n");

            // i = getch();
            scanf("%d", &i);

            break;
        }
        cont++;
    } while(i != num || i != 27);

    cont = 1;

    return i;
}

/*
 * Leitura de arquivos de texto com figuras ASCII
 * @params espera-se receber por parametro um ponteiro de char que é o nome do arquivo
 * que será feito a leitura e na sequência imprimido na tela da aplicação até chegar ao final do arquivo.
 * - Tambem esperamos uma mensagem de callback para cada arquivo que esta sendo lido, que será apresentada,
 * caso não seja possivel fazer a leitura do arquivo.
 */
void telas_ASCII(char *url, char *msg) {
    char ch;

    FILE *arq;

    // Leitura do arquivo que foi passado por parametro
    arq = fopen(url, "r");

    if(arq == NULL) {

        // Não foi possivel ler o arquivo
        printf("%s\n", msg);

    } else {
        while ((ch = fgetc(arq)) != EOF) {
            putchar(ch);
        }
    }

    // fechando o arquivo após usar
    fclose(arq);
}

/*
 * Method responsavel por mostrar Score dos melhores jogadores
 */
int second_tela (void) {
    char pqp[] = "second.txt";
    int x = 0;

    do {
        telas_ASCII(pqp, "msgggg");
        abre_score();

        // x = getch();
        printf("Digite 13 pra seguir o baile: \n");
        scanf("%d", &x);

    } while(x != 13);

    return x;
}

/*
 * Salvar a pontuação e nome do jogador para gerar o score
 */
void gera_score(int cont) {
    FILE *arq;
    char arq_score[] = "score.txt";

    arq = fopen(arq_score, "a+");
    fprintf(arq, "%d %s \n", cont, name);
}

/*
 * Leitura do Score salvo
 */
void abre_score (void) {
    FILE *arq;
    char arq_score[] = "score.txt";
    arq = fopen(arq_score, "a+");

    return;
    // fscanf(arq,"%d %[^\n]s", &a.pt, &a.name);
    // printf("%d %s ", a.pt, a.name);
}