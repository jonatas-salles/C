#include <stdio.h>
#include <stdlib.h>

int main() {
  int fator_a, fator_b, produto = 0;

  printf("Digite o fator A: ");
  scanf("%d", &fator_a);

  fflush(stdin);
  printf("Digite o fator B: ");
  scanf("%d", &fator_b);

  printf("\n===============\n");

  for(int i = 0; i <= fator_b; i++) {
    produto = 0;
    produto = fator_a * i;
    printf("%d x %d = %d\n", fator_a, i, produto);
  }

  printf("===============");
  
  return 0;
}