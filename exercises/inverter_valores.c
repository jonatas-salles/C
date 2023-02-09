#include <stdio.h>
#include <stdlib.h>

int main() {
    int primeiro_valor, segundo_valor = 0;

    printf("Primeiro valor: ");
    scanf("%d", &primeiro_valor);

    fflush(stdin);
    printf("Segundo valor: ");
    scanf("%d", &segundo_valor);

    printf("Primeiro valor antes da troca: %d | Segundo valor antes da troca: %d\n", primeiro_valor, segundo_valor);
    printf("\n================================================================================\n");

    primeiro_valor = primeiro_valor + segundo_valor;
    segundo_valor = primeiro_valor - segundo_valor;
    primeiro_valor = primeiro_valor - segundo_valor;

    printf("\nPrimeiro valor após a troca: %d | Segundo valor após a troca: %d", primeiro_valor, segundo_valor);

    return 0;
}