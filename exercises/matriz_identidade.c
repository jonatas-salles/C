#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    int eh_identidade = 1;

    printf("Informe o tamanho da matriz: ");
    scanf("%d", &n);

    int matriz[n][n];

    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            printf("Insira um valor na posicao [%d][%d]: ", i, j);
            scanf("%d", &matriz[i][j]);
        }
    }

    for (int i=0; i<n && eh_identidade; i++) {
        for (int j=0; j<n && eh_identidade; j++) {
            if (i == j && matriz[i][j] != 1) {
                eh_identidade = 0;
            }
            else if (i != j && matriz[i][j] != 0) {
                eh_identidade = 0;
            }
        }
    }

    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
    if (eh_identidade) {
        printf("\nO vetor eh identidade");

    }
    else {
        printf("\nO vetor nao eh identidade");
    }
}