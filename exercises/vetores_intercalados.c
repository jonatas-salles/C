#include <stdio.h>
#include <stdlib.h>

int main() {
    int vetor_a[10];
    int vetor_b[10];
    int vetor_final[20];
    int index_final = 0;
    int i;

    printf("Digite 10 inteiros:");
    for (i = 0; i < 10; i++) {
        scanf("%d", &vetor_a[i]);
    }
    printf("\nDigite mais 10 inteiros:");
    for (i = 0; i < 10; i++) {
        scanf("%d", &vetor_b[i]);
    }
    for (i = 0; i < 10; i++) {
        vetor_final[index_final] = vetor_a[i];
        index_final++;
        vetor_final[index_final] = vetor_b[i];
        index_final++; 
    }
    
    printf("\nVetor final: ");
    for (i = 0; i < index_final; i++) {
        printf("%d ", vetor_final[i]);
    }

    system("pause");
}