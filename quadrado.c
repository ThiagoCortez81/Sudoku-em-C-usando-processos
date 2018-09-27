#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER 256

/*
* Esta função serve para checar os quadrados menores do jogo de Sudoku, para
* fazer isso, recebe uma matriz 3x3, que tem o tamanho de um setor do jogo
* de Sudoku e verifica se esse mesmo é válido. Ela é alimentada pela função
* checarQuadrados()
*/
int checarMenor(int mini[3][3]){
    int i, j, num, existe = 0;

    /*
    * Os loops passam por todos os valores da matriz e sempre que encontram o
    * número "num" em um dos espaços incrementam a variável "existe" em mais 1.
    * Se "existe" for maior que 1, isto é, se ouver mais de um número "num" no mesmo
    * setor, o setor é automaticamente inválido e retorna falso.
    */
    for(num = 1; num <= 9; num++){
        for(i = 0; i < 3; i++)
            for(j = 0; j < 3; j++)
                if(mini[i][j] == num) existe++;
        if(existe > 1) return 0;
        existe = 0;
    }

    return 1;
}

int main(int argc,char *argv[]) {
	char *mat;
	int fd = atoi(argv[1]); 
	int i, j, k, l;
	int pos = 0;
	int matriz[9][9];

    mat = strtok(argv[2], ",");

    for(i = 0; i < 9; i++){
        for(j = 0; j < 9; j++){
            matriz[i][j]= (int)mat[pos] - 48;
            pos += 2;
        }
    }

	printf("Meu pid = %d. Estou verificando cada mini sudoku...\n", getpid());


    /*
    * O for a seguir serve para separar os quadrados menores (3x3)
    * do geral (9x9). O primeiro delimita a linha, o segundo a Coluna
    * o terceiro itera sobre as linhas separadas pelo primeiro for e 
    * o quarto for itera sobre as colunas separadas pelo segundo for 
    */
    int mini[3][3];

    for(i = 0; i < 9; i += 3)
        for(j = 0; j < 9; j += 3){
            for(k = 0; k < 3; k++)
                for(l = 0; l < 3; l++)
                    mini[k][l] = matriz[k+i][l+j];
            if(!checarMenor(mini)){
                char resposta[1] = "0";
                write(fd, resposta, sizeof(resposta));

                return 0;
            }
        }

        char resposta[1] = "1";
        write(fd, resposta, sizeof(resposta));
        
        return 0;
}