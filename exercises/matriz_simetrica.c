#include <stdio.h>
#include <stdlib.h>

int main() {
    int matriz[3][3];
    int eh_simetrico = 1;

    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            printf("Insira um valor na posicao [%d][%d]: ", i, j);
            scanf("%d", &matriz[i][j]);
        }
    }
    printf("Vetor: \n");
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            if(matriz[i][j] != matriz[j][i]) {
                eh_simetrico = false;
            }
            printf("%d ", matriz[i][j]);
            //printf("%d ", matriz[j][i]);
        }
        printf("\n");
    }
    
    if (eh_simetrico) {
        printf("O vetor eh simetrico");
    }
    else {
        printf("O vetor nao eh simetrico");
    }
}