#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER 256

int main(int argc,char *argv[]) {
	char *mat;
	int fd = atoi(argv[1]); 
	int i, j, k;
	int pos = 0;
	int matriz[9][9];

    mat = strtok(argv[2], ",");

    for(i = 0; i < 9; i++){
        for(j = 0; j < 9; j++){
            matriz[i][j]= (int)mat[pos] - 48;
            pos += 2;
        }
    }

	printf("Meu pid = %d. Estou verificando as linhas...\n", getpid());

    /*
    * O primeiro loop serve para percorrer as linhas da matriz, enquanto que
    * o segundo e o terceiro loop servem para comparar valores que ocupam a
    * mesma linha
    */
    int flag = 1;

    for(i = 0; i < 9 && flag; i++)
        for(j = 0; j < 9 && flag; j++)
            for(k = 0; k < 9 && flag; k++)
                if((j != k) && (matriz[i][j] == matriz[i][k]))
                    flag = 0;

    char resposta[1] = "1";
    if (!flag)
        strcpy(resposta, "0");

    write(fd, resposta, sizeof(resposta));

    return 0;
}