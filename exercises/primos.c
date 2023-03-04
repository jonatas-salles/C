#include <stdio.h>
#include <stdlib.h>

int main() { 
    int num, i;
    int primo = 1;

    printf("Entre com um valor inteiro:");
    scanf("%d", &num);

    if (num > 1) {
        i = 2;
        while(i < num && primo == 1) {
            if (num % i == 0) {
                primo = 0;
            }
            i++;
        }
        if (primo == 1) {
            printf("%d e primo\n", num);
        } else {
            printf("%d nao e primo\n", num);
        }
    } else {
        printf("Numero informado deve ser maior que 1\n");
    }

    system("pause");
}