#include <stdio.h>
#include <stdlib.h>

int main() {
    int vetor[10];
    int aux, pode_trocar;

    for(int i = 0; i < 10; i++) {
        vetor[i] = rand() % 100 + 1;
    }

    for(int i = 0; i < 10; i++) {
        printf("%d ", vetor[i]);
        printf("\n");
    }

    pode_trocar = 1;
    while(pode_trocar) {
        pode_trocar = 0;
        for(int i = 0; i < 9; i++) {
            if(vetor[i] > vetor[i+1]) {
                aux = vetor[i];
                vetor[i] = vetor[i+1];
                vetor[i+1] = aux;
                pode_trocar = 1;
            }
        }
    }

    for(int i = 0; i < 10; i++) {
        printf("%d ", vetor[i]);
    }

    return 0;
}