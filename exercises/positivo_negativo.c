#include <stdio.h>
#include <stdlib.h>

int main() {
    int vetor_inicial[8];
    int vetor_positivo[8];
    int vetor_negativo[8];
    int i;
    int index_positivo = 0;
    int index_negativo = 0;

    printf("Digite 8 valores inteiros:");
    for (i = 0; i < 8; i++) {
        scanf("%d", &vetor_inicial[i]);
    }

    for (i = 0; i < 8; i++) {
        if (vetor_inicial[i] >= 0) {
            vetor_positivo[index_positivo] = vetor_inicial[i];
            index_positivo++;
        } else {
            vetor_negativo[index_negativo] = vetor_inicial[i];
            index_negativo++;
        }
    }

    printf("positivos: ");
    for (i = 0; i < index_positivo; i++) {
        printf("%d ", vetor_positivo[i]);
    }
    printf("\nnegativos: ");
    for (i = 0; i < index_negativo; i++) {
        printf("%d ", vetor_negativo[i]);
    }

    system("pause");
}