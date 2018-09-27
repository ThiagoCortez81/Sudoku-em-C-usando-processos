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

	printf("Meu pid = %d. Estou verificando as colunas...\n", getpid());

	int flag = 1;
    for(j = 0; j < 9 && flag; j++)
        for(i = 0; i < 9 && flag; i++)
            for(k = 0; k < 9 && flag; k++)
                if((i != k) && (matriz[i][j] == matriz[k][j]))
                    flag = 0;

    char resposta[1] = "1";
    if (!flag)
        strcpy(resposta, "0");

    write(fd, resposta, sizeof(resposta));

    return 0;
}