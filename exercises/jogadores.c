#if 0
Em um campeonato de futebol existem 5 times com 11
jogadores cada. Faça um programa que receba a
idade, o peso e a altura de cada um dos jogadores,
calcule e mostre:
A quantidade de jogadores com menos de 18 anos;
A média de idade dos jogadores de cada time;
A altura média de todos os jogadores do
campeonato;
A porcentagem de jogadores de todos os times com
mais de 80 quilos.
#endif

#include <stdio.h>
#include <stdlib.h>

int main() {
    int times, jogadores, idade, menores_18;
    double peso, altura, media_altura, media_idade, mais_80kg;
    
    for (times = 1; times <= 5; times++) {
        for (jogadores = 1; jogadores <= 11; jogadores++) {
            printf("\nInsira a idade do jogador: ");
            scanf("%d", &idade);
            if (idade < 18) {
                menores_18 += 1;
            }            
            media_idade += idade;
            
            printf("Insira o peso do jogador: ");
            scanf("%lf", &peso);
            if (peso > 80) {
                mais_80kg += 1    ;
            }
            
            printf("Insira a altura do jogador: ");
            scanf("%lf", &altura);
            media_altura += altura;
        }
        media_idade = media_idade / 11;
        printf("\nMedia de idade dos jogadores do time %d: %lf", times, media_idade);
    }
    printf("\nQuantidade de jogadores menores de 18 anos: %d", menores_18);
    
    media_altura = media_altura / (11 * 5);
    printf("\nAltura media de todos os jogadores do campeonato: %lf", media_altura);
    
    mais_80kg = ((mais_80kg / (11 * 5)) * 100);
    printf("\nPorcentagem de jogadores de todos os times com mais de 80 quilos %lf%", mais_80kg);
}