#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

typedef struct Piloto {
    char registro_piloto[15], nome[40], data_nascimento[11], sexo[20], curso[50], emails[10][50], telefones[10][50];
    int qtd_emails, qtd_telefones;
} Piloto;

void menu();
void submenu_pilotos(Piloto pilotos[], int *idx_pilotos);
int inserir_piloto(Piloto pilotos[], int *idx_pilotos);
int buscar_piloto(Piloto pilotos[], char registro[], int qtd_pilotos);
void listar_piloto(Piloto pilotos[], int indice, int qtd_pilotos);
void listar_todos_pilotos(Piloto pilotos[], int qtd_pilotos);
int alterar_piloto(Piloto pilotos[], int indice, int qtd_pilotos);
int adicionar_email(Piloto pilotos[], int indice);
int alterar_email(Piloto pilotos[], int indice, int idx_email);
int remover_email(Piloto pilotos[], int indice, int idx_email);
int adicionar_telefone(Piloto pilotos[], int indice);
int alterar_telefone(Piloto pilotos[], int indice, int idx_telefone);
int remover_telefone(Piloto pilotos[], int indice, int idx_telefone);
void remover_piloto(Piloto pilotos[], int indice, int *qtd_pilotos);

void main() {
	setlocale(LC_ALL, "Portuguese");
	int opcao, qtd_pilotos = 0;
	Piloto pilotos[100];
	
	do {
		menu();
		scanf("%d", &opcao);
		switch (opcao) {
			case 0: system("cls");
				printf("\nSaindo...\n");
				break;
			case 1: system("cls");
				submenu_pilotos(pilotos, &qtd_pilotos);
				break;
			default: printf("Op��o inv�lida!\n");
		}
	} while (opcao != 0 && opcao >= 1 && opcao <= 1);
}

void menu() {
	system("cls");
	printf("**********Menu de Op��es**********\n\n");
	printf("\t1. Acessar submenu Pilotos.\n");
	printf("\nEscolha uma op��o (1) ou digite 0 para sair: ");
}

// PILOTOS
void submenu_pilotos(Piloto pilotos[], int *idx_pilotos) {
	int opcao, encontrou;
	char registro[15];
	do {
		printf("\n**********Submenu de Pilotos**********\n\n");
		printf("\t1. Registrar Piloto.\n");
		printf("\t2. Listar um Piloto.\n");
		printf("\t3. Listar todos os Pilotos.\n");
		printf("\t4. Alterar Piloto.\n");
		printf("\t5. Excluir Piloto.\n");
		printf("\nEscolha uma op��o entre 1 e 5 ou digite 0 para voltar ao menu principal: ");
		scanf("%d", &opcao);
	
		switch(opcao) {
			case 0:
				printf("Voltando para o menu principal...\n");
				break;
				
			case 1:
				if (inserir_piloto(pilotos, &(*idx_pilotos)) == 1) {
					printf("Piloto registrado com sucesso!\n");
				} else {
					printf("Registro de piloto j� existe!\n");
				}
				break;
			
			case 2:
				fflush(stdin);
				printf("Digite o registro do piloto que deseja imprimir: ");
				gets(registro);
				encontrou = buscar_piloto(pilotos, registro, *idx_pilotos);
				
				if (encontrou >= 0) {
					listar_piloto(pilotos, encontrou, *idx_pilotos);
				} else {
					printf("Piloto n�o encontrado!\n");
				}
				break;
			
			case 3:
				listar_todos_pilotos(pilotos, *idx_pilotos);
				break;
			
			case 4:
				fflush(stdin);
				printf("Digite o registro do piloto que deseja alterar: ");
				gets(registro);
				encontrou = buscar_piloto(pilotos, registro, *idx_pilotos);
				
				if (encontrou >= 0) {
					alterar_piloto(pilotos, encontrou, *idx_pilotos);
					printf("Piloto alterado com sucesso!");
				} else {
					printf("Piloto n�o encontrado!\n");
				}
				break;
				
			case 5:
				fflush(stdin);
				printf("Digite o registro do piloto que deseja excluir: ");
				gets(registro);
				encontrou = buscar_piloto(pilotos, registro, *idx_pilotos);
				
				if (encontrou >= 0) {
					remover_piloto(pilotos, encontrou, &(*idx_pilotos));
					printf("Piloto removido com sucesso!\n");
				} else {
					printf("Piloto n�o encontrado!\n");
				}
				break;
			
			default: printf("Op��o invalida!\n");
		}
	} while (opcao != 0 && opcao >= 1 && opcao <= 5);
}

int inserir_piloto(Piloto pilotos[], int *idx_pilotos) {
	char entrada[50], registro[15];
	int i;
	
	fflush(stdin);
	printf("\nRegistro Piloto: ");
    gets(registro);
    if (buscar_piloto(pilotos, registro, *idx_pilotos) >= 0) {
    	return -1;
	}
	strcpy(pilotos[*idx_pilotos].registro_piloto, registro);
    printf("Nome: ");
    gets(pilotos[*idx_pilotos].nome);
    printf("Data de nascimento: ");
    gets(pilotos[*idx_pilotos].data_nascimento);
    printf("Sexo: ");
    gets(pilotos[*idx_pilotos].sexo);
    printf("Curso: ");
    gets(pilotos[*idx_pilotos].curso);
    
	for(i=0; i<10; i++) {
    	printf("Email %d: ", i+1);
    	gets(entrada);
    	if (stricmp(entrada, "0") != 0) {
			strcpy(pilotos[*idx_pilotos].emails[i], entrada);
			pilotos[*idx_pilotos].qtd_emails++;
		} else {
			i = 50;
		}
	}
	
	for(i=0; i<10; i++) {
    	printf("Telefone %d: ", i+1);
    	gets(entrada);
    	if (stricmp(entrada, "0") != 0) {
			strcpy(pilotos[*idx_pilotos].telefones[i], entrada);
			pilotos[*idx_pilotos].qtd_telefones++;
		} else {
			i = 50;
		}
	}
	
	(*idx_pilotos)++;
	return 1;
}

int buscar_piloto(Piloto pilotos[], char registro[], int qtd_pilotos) {
	int i;
	
	for (i=0; i<qtd_pilotos; i++) {
		if (stricmp(pilotos[i].registro_piloto, registro) == 0) {
			return i;
		}
	}
	return -1;
}

void listar_piloto(Piloto pilotos[], int indice, int qtd_pilotos) {
	int i;
	
	printf("\n****************************************\n");
	printf("\nImprimindo Piloto de registro: %s\n", pilotos[indice].registro_piloto);
	printf("\nNome: %s\n", pilotos[indice].nome);
	printf("Data de Nascimento: %s\n", pilotos[indice].data_nascimento);
	printf("Sexo: %s\n", pilotos[indice].sexo);
	printf("Curso: %s\n", pilotos[indice].curso);
	for (i=0; i<pilotos[indice].qtd_emails; i++) {
		printf("Email %d: %s\n", i+1, pilotos[indice].emails[i]);
	}
	for (i=0; i<pilotos[indice].qtd_telefones; i++) {
		printf("Telefone %d: %s\n", i+1, pilotos[indice].telefones[i]);
	}
	printf("\n****************************************\n");
}

void listar_todos_pilotos(Piloto pilotos[], int qtd_pilotos) {
	int i;
	
	for (i=0; i<qtd_pilotos; i++) {
		listar_piloto(pilotos, i, qtd_pilotos);
		printf("\n");
	}
}

int alterar_piloto(Piloto pilotos[], int indice, int qtd_pilotos) {
	int opcao, opcao_email, opcao_telefone, i;
	
	printf("Alterando Piloto de registro: %d\n", pilotos[indice].registro_piloto);
	
	do {
		listar_piloto(pilotos, indice, qtd_pilotos);
		
		printf("**********Menu de Altera��o**********\n\n");
		printf("\t1. Alterar nome\n");
		printf("\t2. Alterar data de nascimento\n");
		printf("\t3. Alterar sexo\n");
		printf("\t4. Alterar curso\n");
		printf("\t5. Submenu emails\n");
		printf("\t6. Submenu telefones\n");
		printf("\nEscolha uma op��o de 1 a 6 ou digite 0 para voltar ao submenu de pilotos: ");
		scanf("%d", &opcao);
		fflush(stdin);
		
		switch (opcao) {
			case 0:
				printf("Voltando ao menu principal\n");
				break;
				
			case 1:
				printf("Nome: ");
				gets(pilotos[indice].nome);
				break;
			
			case 2:
				printf("Data de Nascimento: ");
				gets(pilotos[indice].data_nascimento);
				break;
				
			case 3:
				printf("Sexo: ");
				gets(pilotos[indice].sexo);
				break;
				
			case 4:
				printf("Curso: ");
				gets(pilotos[indice].curso);
				break;
				
			case 5:
				system("cls");
				printf("**********Submenu de altera��o de emails**********\n\n");
				printf("\t1. Adicionar email\n");
				printf("\t2. Alterar email\n");
				printf("\t3. Remover email\n");
				printf("\nEscolha uma op��o de 1 a 3 ou digite 0 para voltar ao ao menu de altera��o: ");
				scanf("%d", &opcao_email);
				
				switch (opcao_email) {
					case 0:
						printf("Voltando ao submenu de pilotos...");
						break;
						
					case 1:
						if (adicionar_email(pilotos, indice) == 1) {
							printf("Email adicionado com sucesso!\n");
						} else {
							printf("Limite de emails atingido\n");
						}
						
						break;
					
					case 2:
						system("cls");
						fflush(stdin);
						
						for (i=0; i<pilotos[indice].qtd_emails; i++) {
							printf("%d: %s\n", i+1, pilotos[indice].emails[i]);
						}
						
						printf("Insira o indice do email que deseja alterar: ");
						scanf("%d", &i);
						
						if (alterar_email(pilotos, indice, i-1) == 1) {
							printf("Email alterado com sucesso!\n");
						} else {
							printf("Indice de email inv�lido!\n");
						}
						
						break;
					
					case 3:
						system("cls");
						fflush(stdin);
						
						for (i=0; i<pilotos[indice].qtd_emails; i++) {
							printf("%d: %s\n", i+1, pilotos[indice].emails[i]);
						}
						
						printf("Insira o indice do email que deseja remover: ");
						scanf("%d", &i);
						
						if (remover_email(pilotos, indice, i-1) == 1) {
							printf("Email removido com sucesso!\n");
						} else {
							printf("Indice de email inv�lido!\n");
						}
						
						break;
					
					default: printf("Op��o invalida!\n");
				}
				break;
				
			case 6:
				system("cls");
				printf("**********Submenu de altera��o de telefones**********\n\n");
				printf("\t1. Adicionar telefone\n");
				printf("\t2. Alterar telefone\n");
				printf("\t3. Remover telefone\n");
				printf("\nEscolha uma op��o de 1 a 3 ou digite 0 para voltar ao menu de altera��o: ");
				scanf("%d", &opcao_telefone);
				
				switch (opcao_telefone) {
					case 0:
						printf("Voltando ao submenu de pilotos...");
						break;
						
					case 1:
						if (adicionar_telefone(pilotos, indice) == 1) {
							printf("Telefone adicionado com sucesso!\n");
						} else {
							printf("Limite de telefones atingido\n");
						}
						
						break;
						
					case 2:
						system("cls");
						fflush(stdin);
						
						for (i=0; i<pilotos[indice].qtd_telefones; i++) {
							printf("%d: %s\n", i+1, pilotos[indice].telefones[i]);
						}
						
						printf("Insira o indice do telefone que deseja alterar: ");
						scanf("%d", &i);
						
						if (alterar_telefone(pilotos, indice, i-1) == 1) {
							printf("Telefone alterado com sucesso!\n");
						} else {
							printf("Indice de telefone inv�lido!\n");
						}
						
						break;
						
					case 3:
						system("cls");
						fflush(stdin);
						
						for (i=0; i<pilotos[indice].qtd_telefones; i++) {
							printf("%d: %s\n", i+1, pilotos[indice].telefones[i]);
						}
						
						printf("Insira o indice do telefone que deseja remover: ");
						scanf("%d", &i);
						
						if (remover_telefone(pilotos, indice, i-1) == 1) {
							printf("Telefone removido com sucesso!\n");
						} else {
							printf("Indice de telefone inv�lido!\n");
						}
						
						break;
				}
				break;
			
			default: printf("Op��o invalida!\n");
		}
	} while (opcao != 0 && opcao >= 1 && opcao <= 6);
	
}

int adicionar_email(Piloto pilotos[], int indice) {
	int idx_email = pilotos[indice].qtd_emails;
	if (idx_email >= 10) {
		return -1;
	}
	
	fflush(stdin);
	printf("Email: ");
	gets(pilotos[indice].emails[idx_email]);
	
	pilotos[indice].qtd_emails++;
	
	return 1;
}

int alterar_email(Piloto pilotos[], int indice, int idx_email) {
	int qtd_emails = pilotos[indice].qtd_emails;
	if (idx_email >= qtd_emails) {
		return -1;
	}
	
	fflush(stdin);
	printf("Email: ");
	gets(pilotos[indice].emails[idx_email]);
	
	return 1;
}

int remover_email(Piloto pilotos[], int indice, int idx_email) {
	int qtd_emails = pilotos[indice].qtd_emails, i;
	if (idx_email >= qtd_emails) {
		return -1;
	}
	
	for (i=idx_email; i<qtd_emails - 1; i++) {
		strcpy(pilotos[indice].emails[i], pilotos[indice].emails[i+1]);
	}
	
	pilotos[indice].qtd_emails--;
	return 1;
}

int adicionar_telefone(Piloto pilotos[], int indice) {
	int idx_telefone = pilotos[indice].qtd_telefones;
	if (idx_telefone >= 10) {
		return -1;
	}
	
	fflush(stdin);
	printf("Telefone: ");
	gets(pilotos[indice].telefones[idx_telefone]);
	
	pilotos[indice].qtd_telefones++;
	
	return 1;
}

int alterar_telefone(Piloto pilotos[], int indice, int idx_telefone) {
	int qtd_telefones = pilotos[indice].qtd_telefones;
	if (idx_telefone >= qtd_telefones) {
		return -1;
	}
	
	fflush(stdin);
	printf("Telefone: ");
	gets(pilotos[indice].telefones[idx_telefone]);
	
	return 1;
}

int remover_telefone(Piloto pilotos[], int indice, int idx_telefone) {
	int qtd_telefones = pilotos[indice].qtd_telefones, i;
	if (idx_telefone >= qtd_telefones) {
		return -1;
	}
	
	for (i=idx_telefone; i<qtd_telefones - 1; i++) {
		strcpy(pilotos[indice].telefones[i], pilotos[indice].telefones[i+1]);
	}
	
	pilotos[indice].qtd_telefones--;
	return 1;
}

void remover_piloto(Piloto pilotos[], int indice, int *qtd_pilotos) {
	int i;
	
	for (i=indice; i < (*qtd_pilotos) - 1; i++) {
		pilotos[i] = pilotos[i+1];
	}
	
	(*qtd_pilotos)--;
}

