#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER 256

/*
* Aluno: Thiago Augusto da Silva Cortez
* Matricula: 2017005276
* Curso: Sistemas de Informação
*/

int main() {

    char mat[] = "6,2,4,5,3,9,1,8,7,5,1,9,7,2,8,6,3,4,8,3,7,6,1,4,2,9,5,1,4,3,8,6,5,7,2,9,9,5,8,2,4,7,3,6,1,7,6,2,3,9,1,4,5,8,3,7,1,9,5,6,8,4,2,4,9,6,1,8,2,5,7,3,2,8,5,4,7,3,9,1,6";

    pid_t pidColuna = -10;
    pid_t pidLinha = -10;
    pid_t pidQuadrado = -10;

    int coluna[2], linha[2], quadrado[2]; 
    
    pipe(coluna);
    pipe(linha);
    pipe(quadrado);   
    
    printf("Eu sou o pai, meu PID e %d\n", getpid());
    
    pidColuna = fork();
    
    if (pidColuna > 0)
        pidLinha = fork();

    if (pidColuna > 0 && pidLinha > 0)
        pidQuadrado = fork();
    
    if (pidColuna == 0) {
        char targ[10];
        sprintf(targ, "%d", coluna[1]);
        char *args1[] = {"./coluna", targ, mat, NULL};
        execv("./coluna", args1);
    }

    
    if (pidLinha == 0) {
        char targ2[10];
        sprintf(targ2, "%d", linha[1]);
        char *args2[] = {"./linha", targ2, mat, NULL};
        execv("./linha", args2);
    }

    if (pidQuadrado == 0){
        char targ3[10];
        sprintf(targ3, "%d", quadrado[1]);
        char *args3[] = {"./linha", targ3, mat, NULL};
        execv("./quadrado", args3);   
    }

    char buffer_coluna[BUFFER];
    close(coluna[1]);
    read( coluna[0], buffer_coluna, sizeof(buffer_coluna) );

    char buffer_linha[BUFFER];
    close(linha[1]);
    read( linha[0], buffer_linha, sizeof(buffer_linha) );

    char buffer_quadrado[BUFFER];
    close(quadrado[1]);
    read( quadrado[0], buffer_quadrado, sizeof(buffer_quadrado) );

    if (atoi(buffer_quadrado) && atoi(buffer_coluna) && atoi(buffer_linha))
        printf("O Sudoku esta escrito corretamente.\n");
    else    
        printf("Ops, tem um erro no sudoku! Verifique novamente.\n");

    wait(NULL);
    
    return 0;
}