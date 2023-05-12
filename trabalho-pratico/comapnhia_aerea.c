#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define MAX_PILOTO 100
#define MAX_VOOS 100
#define MAX_VIAGENS 100

// SC3022862 - Jonatas Henrique Salles
// SC3029948 - Deividi Filho

typedef struct {
	int dia, mes, ano;
} Data;

typedef struct {
    char registro_piloto[15], nome[40], sexo[20], curso[50], emails[10][50], telefones[10][50];
    int qtd_emails, qtd_telefones;
    Data data_nascimento;
} Piloto;

typedef struct {
	int numero, qtd_escalas;
	char cidade_origem[50], cidade_destino[50], aeronave[50], escalas[50][10], tempo_medio[10];
	float distancia;
} Voo;

typedef struct {
	int numero_voo, qtd_ocorrencias;
	char registro_piloto[15], hora_saida[10], hora_chegada[10], ocorrencias[200][10], pk[200];
	Data data_saida, data_chegada;
} Viagem;

void menu();

// PILOTOS
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

// VOOS
void submenu_voos(Voo voos[], int *idx_voos);
int inserir_voo(Voo voos[], int *idx_voos);
int buscar_voo(Voo voos[], int num, int qtd_voos);
void listar_voo(Voo voos[], int indice, int qtd_voos);
void listar_todos_voos(Voo voos[], int qtd_voos);
int alterar_voo(Voo voos[], int indice, int qtd_voos);
int adicionar_escala(Voo voos[], int indice);
int alterar_escala(Voo voos[], int indice, int idx_escala);
int remover_escala(Voo voos[], int indice, int idx_escala);
void remover_voo(Voo voos[], int indice, int *qtd_voos);

// VIAGENS
void submenu_viagens(Viagem viagens[], Voo voos[], Piloto pilotos[], int *idx_viagens, int idx_voos, int idx_pilotos);
int inserir_viagem(Viagem viagens[], Voo voos[], Piloto pilotos[], int *idx_viagens, int idx_voos, int idx_pilotos);
int buscar_viagem(Viagem viagens[], char pk[], int qtd_viagens);
void listar_viagem(Viagem viagens[], int indice, int qtd_viagens);
void listar_todas_viagens(Viagem viagens[], int qtd_viagens);
int listar_viagens_por_voo(Viagem viagens[], int num, int qtd_viagens);
void alterar_viagem(Viagem viagens[], int indice, int qtd_viagens);
int adicionar_ocorrencia(Viagem viagens[], int indice);
int alterar_ocorrencia(Viagem viagens[], int indice, int idx_ocorrencia);
int remover_ocorrencia(Viagem viagens[], int indice, int idx_ocorrencia);
void remover_viagem(Viagem viagens[], int indice, int *qtd_viagens);

// RELATORIOS
void submenu_relatorios(Viagem viagens[], Voo voos[], Piloto pilotos[], int idx_viagens, int idx_voos, int idx_pilotos);
int calcular_idade(Piloto pilotos[], int indice, int qtd_pilotos);
int verificar_intervalo_datas(Viagem viagem, Data data_x, Data data_y);

void main() {
	setlocale(LC_ALL, "Portuguese");
	int opcao, qtd_pilotos = 0, qtd_voos = 0, qtd_viagens = 0;
	Piloto pilotos[MAX_PILOTO];
	Voo voos[MAX_VOOS];
	Viagem viagens[MAX_VIAGENS];
	
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
			
			case 2: system("cls");
				submenu_voos(voos, &qtd_voos);
				break;
				
			case 3: system("cls");
				submenu_viagens(viagens, voos, pilotos, &qtd_viagens, qtd_voos, qtd_pilotos);
				break;
				
			case 4: system("cls");
				submenu_relatorios(viagens, voos, pilotos, qtd_viagens, qtd_voos, qtd_pilotos);
				break;
			
			default: printf("Opcao invalida!\n");
			
		}
	} while (opcao != 0 && opcao >= 1 && opcao <= 4);
}

void menu() {
	system("cls");
	printf("**********Menu de Opcoes**********\n\n");
	printf("\t1. Acessar submenu Pilotos.\n");
	printf("\t2. Acessar submenu Voos.\n");
	printf("\t3. Acessar submenu Viagens.\n");
	printf("\t4. Acessar submenu Relatorios.\n");
	printf("\nEscolha uma opcao entre 1 e 4 ou digite 0 para sair: ");
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
		printf("\nEscolha uma opcao entre 1 e 5 ou digite 0 para voltar ao menu principal: ");
		scanf("%d", &opcao);
	
		switch(opcao) {
			case 0:
				printf("Voltando para o menu principal...\n");
				break;
				
			case 1:
				if (inserir_piloto(pilotos, &(*idx_pilotos)) == 1) {
					printf("Piloto registrado com sucesso!\n");
				} else {
					printf("Registro de piloto ja existe!\n");
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
					printf("Piloto nao encontrado!\n");
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
					printf("Piloto nao encontrado!\n");
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
					printf("Piloto nao encontrado!\n");
				}
				break;
			
			default: printf("Opcao invalida!\n");
		}
	} while (opcao != 0 && opcao >= 1 && opcao <= 5);
}

int inserir_piloto(Piloto pilotos[], int *idx_pilotos) {
	char entrada[50], registro[15];
	int i;
	
	fflush(stdin);
	printf("\nRegistro Piloto: ");
    gets(registro);
    if (buscar_piloto(pilotos, registro, *idx_pilotos) >= 0 || *idx_pilotos >= MAX_PILOTO) {
    	return -1;
	}
	strcpy(pilotos[*idx_pilotos].registro_piloto, registro);
    printf("Nome: ");
    gets(pilotos[*idx_pilotos].nome);
    printf("Data de nascimento\n");
    printf("Dia: ");
    scanf("%d", &pilotos[*idx_pilotos].data_nascimento.dia);
    printf("Mes: ");
    scanf("%d", &pilotos[*idx_pilotos].data_nascimento.mes);
    printf("Ano: ");
    scanf("%d", &pilotos[*idx_pilotos].data_nascimento.ano);
    fflush(stdin);
    printf("Sexo: ");
    gets(pilotos[*idx_pilotos].sexo);
    printf("Curso: ");
    gets(pilotos[*idx_pilotos].curso);
    
    printf("\nInsercao de emails: Digite 0 para encerrar insercao\n\n");
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
	
	printf("\nInsercao de telefones: Digite 0 para encerrar insercao\n\n");
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
	printf("Data de Nascimento: %2d/%02d/%04d\n", pilotos[indice].data_nascimento.dia, pilotos[indice].data_nascimento.mes, pilotos[indice].data_nascimento.ano);
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
	
	printf("Alterando Piloto de registro: %s\n", pilotos[indice].registro_piloto);
	
	do {
		listar_piloto(pilotos, indice, qtd_pilotos);
		
		printf("**********Menu de Alteracao**********\n\n");
		printf("\t1. Alterar nome\n");
		printf("\t2. Alterar data de nascimento\n");
		printf("\t3. Alterar sexo\n");
		printf("\t4. Alterar curso\n");
		printf("\t5. Submenu emails\n");
		printf("\t6. Submenu telefones\n");
		printf("\nEscolha uma opcao de 1 a 6 ou digite 0 para voltar ao submenu de pilotos: ");
		scanf("%d", &opcao);
		fflush(stdin);
		
		switch (opcao) {
			case 0:
				printf("Voltando ao submenu de pilotos\n");
				break;
				
			case 1:
				printf("Nome: ");
				gets(pilotos[indice].nome);
				break;
			
			case 2:
				printf("Data de Nascimento: ");
				printf("Dia: ");
			    scanf("%d", &pilotos[indice].data_nascimento.dia);
			    printf("Mes: ");
			    scanf("%d", &pilotos[indice].data_nascimento.mes);
			    printf("Ano: ");
			    scanf("%d", &pilotos[indice].data_nascimento.ano);
			    fflush(stdin);
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
				printf("**********Submenu de alteracao de emails**********\n\n");
				printf("\t1. Adicionar email\n");
				printf("\t2. Alterar email\n");
				printf("\t3. Remover email\n");
				printf("\nEscolha uma opcao de 1 a 3 ou digite 0 para voltar ao ao menu de alteracao: ");
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
							printf("Indice de email invalido!\n");
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
							printf("Indice de email invalido!\n");
						}
						
						break;
					
					default: printf("Opcao invalida!\n");
				}
				break;
				
			case 6:
				system("cls");
				printf("**********Submenu de alteracao de telefones**********\n\n");
				printf("\t1. Adicionar telefone\n");
				printf("\t2. Alterar telefone\n");
				printf("\t3. Remover telefone\n");
				printf("\nEscolha uma opcao de 1 a 3 ou digite 0 para voltar ao menu de alteracao: ");
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
							printf("Indice de telefone invalido!\n");
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
							printf("Indice de telefone invalido!\n");
						}
						
						break;
				}
				break;
			
			default: printf("Opcao invalida!\n");
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

// VOOS
void submenu_voos(Voo voos[], int *idx_voos) {
	int num, opcao, encontrou;
	do {
		printf("\n**********Submenu de Voos**********\n\n");
		printf("\t1. Registrar Voo.\n");
		printf("\t2. Listar um Voo.\n");
		printf("\t3. Listar todos os Voos.\n");
		printf("\t4. Alterar Voo.\n");
		printf("\t5. Excluir Voo.\n");
		printf("\nEscolha uma opcao entre 1 e 5 ou digite 0 para voltar ao menu principal: ");
		scanf("%d", &opcao);
		
		switch(opcao) {
			case 0:
				printf("Voltando para o menu principal...\n");
				break;
				
			case 1:
				if (inserir_voo(voos, &(*idx_voos)) == 1) {
					printf("Voo registrado com sucesso!\n");
				} else {
					printf("Numero de voo ja existe!\n");
				}
				break;
			
			case 2:
				fflush(stdin);
				printf("Digite o numero de voo que deseja imprimir: ");
				scanf("%d", &num);
				encontrou = buscar_voo(voos, num, *idx_voos);
				
				if (encontrou >=0) {
					listar_voo(voos, encontrou, *idx_voos);
				} else {
					printf("Voo nao encontrado!\n");
				}
				break;
				
			case 3:
				listar_todos_voos(voos, *idx_voos);
				break;
			
			case 4:
				fflush(stdin);
				printf("Digite o numero do voo que deseja alterar: ");
				scanf("%d", &num);
				encontrou = buscar_voo(voos, num, *idx_voos);
				
				if (encontrou >= 0) {
					alterar_voo(voos, encontrou, *idx_voos);
					printf("Voo alterado com sucesso!\n");
				} else {
					printf("Voo nao encontrado!\n");
				}
				
				break;
				
			case 5:
				fflush(stdin);
				printf("Digite o numero do voo que deseja excluir: ");
				scanf("%d", &num);
				encontrou = buscar_voo(voos, num, *idx_voos);
				
				if (encontrou >=0) {
					remover_voo(voos, encontrou, &(*idx_voos));
					printf("Voo removido com sucesso!\n");
				} else {
					printf("Voo nao encontrado!\n");
				}
				
				break;
			
			default: printf("Opcao invalida!\n");
		}
	} while (opcao != 0 && opcao >= 1 && opcao <= 5);
}

int inserir_voo(Voo voos[], int *idx_voos) {
	int numero, i;
	char escala[50];
	
	printf("\nNumero do Voo: ");
	scanf("%d", &numero);
	fflush(stdin);
	
	if (buscar_voo(voos, numero, *idx_voos) >=0 || *idx_voos >= MAX_VOOS) {
		return -1;
	}
	
	voos[*idx_voos].numero = numero;
	
	printf("Cidade de origem: ");
	gets(voos[*idx_voos].cidade_origem);
	printf("Cidade de destino: ");
	gets(voos[*idx_voos].cidade_destino);
	printf("Distancia em KM: ");
	scanf("%f", &voos[*idx_voos].distancia);
	fflush(stdin);
	printf("Tempo medio: ");
	gets(voos[*idx_voos].tempo_medio);
	printf("Aeronave: ");
	gets(voos[*idx_voos].aeronave);
	
	printf("\nInserção de escalas: Digite 0 para encerrar inserção\n\n");
	for (i=0; i<10; i++) {
		printf("Escala %d: ", i+1);
		gets(escala);
		if (stricmp(escala, "0") != 0) {
			strcpy(voos[*idx_voos].escalas[i], escala);
			voos[*idx_voos].qtd_escalas++;
		} else {
			i = 50;
		}
	}
	
	(*idx_voos)++;
	return 1;
}

int buscar_voo(Voo voos[], int num, int qtd_voos) {
	int i;
	for (i=0; i<qtd_voos; i++) {
		if (voos[i].numero == num) {
			return i;
		}
	}
	return -1;
}

void listar_voo(Voo voos[], int indice, int qtd_voos) {
	int i;
	
	printf("\n****************************************\n");
	printf("\nImprimindo Voo de numero: %d\n", voos[indice].numero);
	printf("Cidade de origem: %s\n", voos[indice].cidade_origem);
	printf("Cidade de destino: %s\n", voos[indice].cidade_destino);
	printf("Distancia: %.2fkm\n", voos[indice].distancia);
	printf("Tempo medio: %s\n", voos[indice].tempo_medio);
	printf("Aeronave: %s\n", voos[indice].aeronave);
	
	for (i=0; i<voos[indice].qtd_escalas; i++) {
		printf("Escala %d: %s", i+1, voos[indice].escalas[i]);
		printf("\n");
	}
	printf("\n****************************************\n");
}

void listar_todos_voos(Voo voos[], int qtd_voos) {
	int i;
	
	for (i=0; i<qtd_voos; i++) {
		listar_voo(voos, i, qtd_voos);
		printf("\n");
	}
}

int alterar_voo(Voo voos[], int indice, int qtd_voos) {
	int opcao, opcao_escala, i;
	
	printf("Alterando Voo de numero: %d\n", voos[indice].numero);
	
	do {
		listar_voo(voos, indice, qtd_voos);
		
		printf("**********Menu de Alteracao**********\n\n");
		printf("\t1. Cidade origem\n");
	    printf("\t2. Cidade destino\n");
	    printf("\t3. Distância\n");
	    printf("\t4. Tempo médio\n");
	    printf("\t5. Aeronave\n");
	    printf("\t6. Submenu escalas\n");
	    printf("\nEscolha uma opcao de 1 a 6 ou digite 0 para voltar ao submenu de voos: ");
	    scanf("%d", &opcao);
		fflush(stdin);
		
		switch (opcao) {
			case 0:
				printf("Voltando ao submenu de voos\n");
				break;
				
			case 1:
				printf("Cidade de origem: ");
				gets(voos[indice].cidade_origem);
				
				break;
			
			case 2:
				printf("Cidade de destino: ");
				gets(voos[indice].cidade_destino);
				
				break;
			
			case 3:
				printf("Distancia em KM: ");
				scanf("%f", &voos[indice].distancia);
				fflush(stdin);
				
				break;
			
			case 4:
				printf("Tempo medio: ");
				gets(voos[indice].tempo_medio);
				
				break;
				
			case 5:
				printf("Aeronave: ");
				gets(voos[indice].aeronave);
			
			case 6:
				system("cls");
				printf("**********Submenu de alteracao de escalas**********\n\n");
				printf("\t1. Adicionar escala\n");
				printf("\t2. Alterar escala\n");
				printf("\t3. Remover escala\n");
				printf("\nEscolha uma ocao de 1 a 3 ou digite 0 para retornar ao menu de alteracao: ");
				scanf("%d", &opcao_escala);
				
				switch (opcao_escala) {
					case 0:
						printf("Voltando ao menu de alteracao...");
						break;
						
					case 1:
						if (adicionar_escala(voos, indice) == 1) {
							printf("Escala adicionada com sucesso!\n");
						} else {
							printf("Limite de escalas atingido\n");
						}
						
						break;
						
					case 2:
						system("cls");
						fflush(stdin);
						
						for (i=0; i<voos[indice].qtd_escalas; i++) {
							printf("%d: %s\n", i+1, voos[indice].escalas[i]);
						}
						
						printf("Insira o indice da escala que deseja alterar: ");
						scanf("%d", &i);
						
						if (alterar_escala(voos, indice, i-1) == 1) {
							printf("Escala alterada com sucesso!\n");
						} else {
							printf("Indice de escala invalido\n");
						}
						
						break;
						
					case 3:
						system("cls");
						fflush(stdin);
						
						for (i=0; i<voos[indice].qtd_escalas; i++) {
							printf("%d: %s\n", i+1, voos[indice].escalas[i]);
						}
						
						printf("Insira o indice da escala que deseja remover: ");
						scanf("%d", &i);
						
						if (remover_escala(voos, indice, i-1) == 1) {
							printf("Escala removida com sucesso!\n");
						} else {
							printf("Indice de escala invalido\n");
						}
						
						break;
				}
				break;
				
			default: printf("Opcao invalida!\n");				
		} 
	} while (opcao != 0 && opcao >= 1 && opcao <= 6);
}

int adicionar_escala(Voo voos[], int indice) {
	int idx_escala = voos[indice].qtd_escalas;
	if (idx_escala >= 10) {
		return -1;
	}
	
	fflush(stdin);
	printf("Escala: ");
	gets(voos[indice].escalas[idx_escala]);
	
	voos[indice].qtd_escalas++;
	
	return 1;
}

int alterar_escala(Voo voos[], int indice, int idx_escala) {
	int qtd_escalas = voos[indice].qtd_escalas;
	if (idx_escala >= qtd_escalas) {
		return -1;
	}
	
	fflush(stdin);
	printf("Escala: ");
	gets(voos[indice].escalas[idx_escala]);
	
	return 1;
}

int remover_escala(Voo voos[], int indice, int idx_escala) {
	int qtd_escalas = voos[indice].qtd_escalas, i;
	
	if (idx_escala >= qtd_escalas) {
		return -1;
	}
	
	for (i=idx_escala; i<qtd_escalas - 1; i++) {
		strcpy(voos[indice].escalas[i], voos[indice].escalas[i+1]);
	}
	
	voos[indice].qtd_escalas--;
	return 1;
}

void remover_voo(Voo voos[], int indice, int *qtd_voos) {
	int i;
	
	for (i=indice; i < (*qtd_voos) - 1; i++) {
		voos[i] = voos[i+1];
	}
	
	(*qtd_voos)--;
}

// VIAGENS
void submenu_viagens(Viagem viagens[], Voo voos[], Piloto pilotos[], int *idx_viagens, int idx_voos, int idx_pilotos) {
	int opcao, encontrou, numero_voo, i;
	char registro[15];
	
	do {
		printf("\n**********Submenu de Viagens**********\n\n");
		printf("\t1. Registrar Viagem.\n");
		printf("\t2. Listar viagem por indice.\n");
		printf("\t3. Listar todas viagens.\n");
		printf("\t4. Listar viagens por voo.\n");
		printf("\t5. Alterar viagem.\n");
		printf("\t6. Remover viagem.\n");
		printf("\nEscolha uma opcao entre 1 e 6 ou digite 0 para voltar ao menu principal: ");
		scanf("%d", &opcao);
		
		switch (opcao) {
			case 0:
				printf("Voltando para o menu principal...\n");
				break;
				
			case 1:
				i = inserir_viagem(viagens, voos, pilotos, &(*idx_viagens), idx_voos, idx_pilotos) == 1;
				if (i == 1) {
					printf("Viagem adicionada com sucesso!\n");
				} else {
					if (i == 0) {
						printf("Dado(s) de viagem invalido(s)\n");
					} else {
						printf("Viagem ja existe\n");
					}
				}
				break;
			
			case 2:
				printf("Digite o indice da viagem que deseja imprimir: ");
				scanf("%d", &i);
				if (i <= *idx_viagens) {
					listar_viagem(viagens, i, *idx_viagens);
				} else {
					printf("Indice invalido\n");
				}
				break;
				
			case 3:
				listar_todas_viagens(viagens, *idx_viagens);
				break;
			
			case 4:
				printf("Insira o numero do Voo que deseja listar: ");
				scanf("%d", &numero_voo);
				if(listar_viagens_por_voo(viagens, numero_voo, *idx_viagens) == -1) {
					printf("Nenhuma viagem encontrada\n");
				}
				
				break;
			
			case 5:
				printf("Digite o indice da viagem que deseja alterar: ");
				scanf("%d", &i);
				
				if (i <= *idx_viagens) {
					alterar_viagem(viagens, i-1, *idx_viagens);
					printf("Viagem alterada com sucesso!\n");
				} else {
					printf("Indice invalido\n");
				}
				break;
				
			case 6:
				printf("Digite o indice da viagem que deseja remover: ");
				scanf("%d", &i);
				
				if (i <= *idx_viagens) {
					remover_viagem(viagens, i-1, &(*idx_viagens));
					printf("Viagem removida com sucesso!\n");
				} else {
					printf("Indice invalido\n");
				}
				break;
			
			default: printf("Opcao invalida!\n");
		}
	} while (opcao != 0 && opcao >= 1 && opcao <= 6);
}

int inserir_viagem(Viagem viagens[], Voo voos[], Piloto pilotos[], int *idx_viagens, int idx_voos, int idx_pilotos) {
	int num, dia, mes, ano, i;
	char registro[15], hora_saida[10], ocorrencia[200], pk[200], str[10];
	strcpy(pk, "");
	
	// RECEBENDO DADOS QUE FORMAM PK
	printf("\nNumero Voo: ");
	scanf("%d", &num);
	fflush(stdin);
	
	if (buscar_voo(voos, num, idx_voos) == -1) {
		printf("Voo nao encontrado!\n");
		return 0;
	}
	
	sprintf(str, "%d", num);
	strcat(pk, str);
	
	printf("Registro do piloto: ");
	gets(registro);
	
	if (buscar_piloto(pilotos, registro, idx_pilotos) == -1) {
		printf("Piloto nao encontrado!\n");
		return 0;
	}
	
	strcat(pk, registro);
	
	printf("Data Saida: \n");
	printf("Dia (1-31): ");
	scanf("%d", &dia);
	sprintf(str, "%d", dia);
	strcat(pk, str);
	printf("Mes (1-12): ");
	scanf("%d", &mes);
	sprintf(str, "%d", mes);
	strcat(pk, str);
	printf("Ano (1900 - 2100): ");
	scanf("%d", &ano);
	sprintf(str, "%d", ano);
	strcat(pk, str);
	fflush(stdin);
	
	printf("Hora saida (HH:MM): ");
	gets(hora_saida);
	strcat(pk, hora_saida);
	
	if (buscar_viagem(viagens, pk, *idx_viagens) >= 0) {
		return -1;
	}
	
	strcpy(viagens[*idx_viagens].pk, pk);
	
	//SALVANDO DADOS
	viagens[*idx_viagens].numero_voo = num;
	strcpy(viagens[*idx_viagens].registro_piloto, registro);
	viagens[*idx_viagens].data_saida.dia = dia;
	viagens[*idx_viagens].data_saida.mes = mes;
	viagens[*idx_viagens].data_saida.ano = ano;
	strcpy(viagens[*idx_viagens].hora_saida, hora_saida);
	
	// LEITURA E GRAVACAO DOS DADOS RESTANTES
	printf("Data chegada: ");
	printf("Dia (1-31): ");
	scanf("%d", &viagens[*idx_viagens].data_chegada.dia);
	printf("Mes (1-12): ");
	scanf("%d", &viagens[*idx_viagens].data_chegada.mes);
	printf("Ano (1900 - 2100): ");
	scanf("%d", &viagens[*idx_viagens].data_chegada.ano);
	fflush(stdin);
	printf("Hora chegada (HH:MM): ");
	gets(viagens[*idx_viagens].hora_chegada);
	
	printf("\nInsercao de ocorrencias: Digite 0 para encerrar insercao\n\n");
	for (i=0; i<10; i++) {
		printf("Ocorrencia %d: ", i+1);
		gets(ocorrencia);
		
		if (stricmp(ocorrencia, "0") != 0) {
			strcpy(viagens[*idx_viagens].ocorrencias[i], ocorrencia);
			viagens[*idx_viagens].qtd_ocorrencias++;
		} else {
			i = 50;
		}
	}
	
	(*idx_viagens)++;
	return 1;	
}

int buscar_viagem(Viagem viagens[], char pk[], int qtd_viagens) {
	int i;
	for (i=0; i<qtd_viagens; i++) {
		printf("PK struct: %s\n", viagens[i].pk);
		if(stricmp(viagens[i].pk, pk) == 0) {
			return i;
		}
	}
	return -1;
}

void listar_viagem(Viagem viagens[], int indice, int qtd_viagens) {
	int i;
	
	printf("\n****************************************\n");
	printf("\nImprimindo Viagem\n");
	printf("Numero Voo: %d\n", viagens[indice].numero_voo);
	printf("Registro Piloto: %s\n", viagens[indice].registro_piloto);
	printf("Data saida: %02d/%02d/%04d\n", viagens[indice].data_saida.dia, viagens[indice].data_saida.mes, viagens[indice].data_saida.ano);
	printf("Hora saida: %s\n", viagens[indice].hora_saida);
	printf("Data chegada: %02d/%02d/%04d\n", viagens[indice].data_chegada.dia, viagens[indice].data_chegada.mes, viagens[indice].data_chegada.ano);
	printf("Hora chegada: %s\n", viagens[indice].hora_chegada);
	
	for (i=0; i<viagens[indice].qtd_ocorrencias; i++) {
		printf("Ocorrencia %d: %s", i+1, viagens[indice].ocorrencias[i]);
		printf("\n");
	}
	printf("\n****************************************\n");
}

void listar_todas_viagens(Viagem viagens[], int qtd_viagens) {
	int i;
	
	for (i=0; i<qtd_viagens; i++) {
		printf("********** Viagem %d **********", i+1);
		listar_viagem(viagens, i, qtd_viagens);
		printf("\n");
	}
}

int listar_viagens_por_voo(Viagem viagens[], int num, int qtd_viagens) {
	int i, retorno = -1;
	
	for (i=0; i<qtd_viagens; i++) {
		if (viagens[i].numero_voo == num) {
			listar_viagem(viagens, i, qtd_viagens);
			printf("\n");
			retorno = 1;
		}
	}
	
	return retorno;
}

void alterar_viagem(Viagem viagens[], int indice, int qtd_viagens) {
	int opcao, opcao_ocorrencia, i;
	
	printf("Alterando viagem do indice:  %d\n", indice);
	
	do {
		listar_viagem(viagens, indice, qtd_viagens);
		
		printf("**********Menu de Alteracao**********\n\n");
		printf("\t1. Data de chegada\n");
		printf("\t2. Hora de chegada\n");
		printf("\t3. Submenu ocorrencias\n");
		printf("\nEscolha uma opcao de 1 a 3 ou digite 0 para voltar ao submenu de viagens: ");
		scanf("%d", &opcao);
		fflush(stdin);
		
		switch (opcao) {
			case 0:
				printf("Voltando ao submenu de viagens\n");
				break;
				
			case 1:
				printf("Data chegada: \n");
				printf("Dia (1-31): ");
				scanf("%d", &viagens[indice].data_chegada.dia);
				printf("Mes (1-12): ");
				scanf("%d", &viagens[indice].data_chegada.mes);
				printf("Ano (1900 - 2100): ");
				scanf("%d", &viagens[indice].data_chegada.ano);
				fflush(stdin);
				
				break;
				
			case 2:
				printf("Hora chegada (HH:MM): ");
				gets(viagens[indice].hora_chegada);
				
				break;
				
			case 3:
				system("cls");
				printf("**********Submenu de alteracao de ocorrencias**********\n\n");
				printf("\t1. Adicionar ocorrencia\n");
				printf("\t2. Alterar ocorrencia\n");
				printf("\t3. Remover ocorrencia\n");
				printf("\nEscolha uma ocao de 1 a 3 ou digite 0 para retornar ao menu de alteracao: ");
				scanf("%d", &opcao_ocorrencia);
				
				switch (opcao_ocorrencia) {
					case 0:
						printf("Voltando ao menu de alteracao...");
						break;
						
					case 1:
						if (adicionar_ocorrencia(viagens, indice) == 1) {
							printf("Ocorrencia adicionada com sucesso!\n");
						} else {
							printf("Limite de ocorrencias atingido\n");
						}
						
						break;
						
					case 2:
						system("cls");
						fflush(stdin);
						
						for (i=0; i<viagens[indice].qtd_ocorrencias; i++) {
							printf("%d: %s\n", i+1, viagens[indice].ocorrencias[i]);
						}
						
						printf("Insira o indice da ocorrencia que deseja alterar: ");
						scanf("%d", &i);
						
						if (alterar_ocorrencia(viagens, indice, i-1) == 1) {
							printf("Ocorrencia alterada com sucesso!\n");
						} else {
							printf("Indice de ocorrencia invalido\n");
						}
						
						break;
						
					case 3:
						system("cls");
						fflush(stdin);
						
						for (i=0; i<viagens[indice].qtd_ocorrencias; i++) {
							printf("%d: %s\n", i+1, viagens[indice].ocorrencias[i]);
						}
						
						printf("Insira o indice da ocorrencia que deseja remover: ");
						scanf("%d", &i);
						
						if (remover_ocorrencia(viagens, indice, i-1) == 1) {
							printf("Ocorrencia removida com sucesso!\n");
						} else {
							printf("Indice de ocorrencia invalido\n");
						}
						
						break;
				}
				break;
				
			default: printf("Opcao invalida!\n");
		}
	} while (opcao != 0 && opcao >= 1 && opcao <= 3);
}

int adicionar_ocorrencia(Viagem viagens[], int indice) {
	int idx_ocorrencia = viagens[indice].qtd_ocorrencias;
	if (idx_ocorrencia >= 10) {
		return -1;
	}
	
	fflush(stdin);
	printf("Ocorrencia: ");
	gets(viagens[indice].ocorrencias[idx_ocorrencia]);
	
	viagens[indice].qtd_ocorrencias++;
	
	return 1;
}

int alterar_ocorrencia(Viagem viagens[], int indice, int idx_ocorrencia) {
	int qtd_ocorrencias = viagens[indice].qtd_ocorrencias;
	
	if (idx_ocorrencia >= qtd_ocorrencias) {
		return -1;
	}
	
	fflush(stdin);
	printf("Ocorrencia: ");
	gets(viagens[indice].ocorrencias[idx_ocorrencia]);
	
	return 1;
}

int remover_ocorrencia(Viagem viagens[], int indice, int idx_ocorrencia) {
	int qtd_ocorrencias = viagens[indice].qtd_ocorrencias, i;
	
	if (idx_ocorrencia >= qtd_ocorrencias) {
		return -1;
	}
	
	for (i=idx_ocorrencia; i<qtd_ocorrencias; i++) {
		strcpy(viagens[indice].ocorrencias[i], viagens[indice].ocorrencias[i+1]);
	}
	
	viagens[indice].qtd_ocorrencias--;
	return 1;
}

void remover_viagem(Viagem viagens[], int indice, int *qtd_viagens) {
	int i;
	
	for (i=indice; i < (*qtd_viagens) - 1; i++) {
		viagens[i] = viagens[i+1];
	}
	
	(*qtd_viagens)--;
}

//RELATORIOS
void submenu_relatorios(Viagem viagens[], Voo voos[], Piloto pilotos[], int idx_viagens, int idx_voos, int idx_pilotos) {
	int i, j, opcao, idade, idade_buscada, encontrou;
	char cidade[50];
	Voo voo;
	Data data_inicial, data_final;
	
	do {
		printf("\n**********Submenu de Relatorios**********\n\n");
		printf("\t1. Listar piloto acima de certa idade.\n");
		printf("\t2. Listar voo por cidade na escala.\n");
		printf("\t3. Listar viagens por intervalo de data.\n");
		printf("\nEscolha uma opcao entre 1 e 3 ou digite 0 para voltar ao menu principal: ");
		scanf("%d", &opcao);
		
		switch (opcao) {
			case 0:
				printf("Voltando para o menu principal...\n");
				break;
				
			case 1:
				printf("Idade: ");
				scanf("%d", &idade_buscada);
				for (i=0; i<idx_pilotos; i++) {
					idade = calcular_idade(pilotos, i, idx_pilotos);
					
					if (idade == -1 || idade_buscada <= 0) {
						printf("Erro ao calcular idade");
					}
					if (idade > idade_buscada) {
						listar_piloto(pilotos, i, idx_pilotos);
					}
				}
				break;
				
			case 2:
				fflush(stdin);
				printf("Cidade: ");
				gets(cidade);
				
				for (i=0; i<idx_voos; i++) {
					voo = voos[i];
					for (j=0; j<voo.qtd_escalas; j++) {
						if (stricmp(cidade, voo.escalas[i]) == 0) {
							listar_voo(voos, i, idx_voos);
						}
					}
				}
				break;
				
			case 3:
				printf("Data inicial do intervalo\n");
				printf("Dia: ");
				scanf("%d", &data_inicial.dia);
				printf("Mes: ");
				scanf("%d", &data_inicial.mes);
				printf("Ano: ");
				scanf("%d", &data_inicial.ano);
				printf("Data final do intervalo\n");
				printf("Dia: ");
				scanf("%d", &data_final.dia);
				printf("Mes: ");
				scanf("%d", &data_final.mes);
				printf("Ano: ");
				scanf("%d", &data_final.ano);
				
				for (i=0; i<idx_viagens; i++) {
					if (verificar_intervalo_datas(viagens[i], data_inicial, data_final) == 1) {
						encontrou = buscar_piloto(pilotos, viagens[i].registro_piloto, idx_pilotos);
						printf("\n****************************************\n");				
						printf("Viagem comandada pelo piloto: %s\n", pilotos[encontrou].nome);
						listar_viagem(viagens, i, idx_viagens);
					}
				}
				break;
				
			default: printf("Opcao invalida!\n");			
		}
	} while (opcao != 0 && opcao >= 1 && opcao <= 3);
}

int calcular_idade(Piloto pilotos[], int indice, int qtd_pilotos) {
	Data data_atual;
	int dia, mes, ano, idade;
	printf("Insira a data atual\n");
	printf("Dia: ");
	scanf("%d", &dia);
	printf("Mes: ");
	scanf("%d", &mes);
	printf("Ano: ");
	scanf("%d", &ano);
	fflush(stdin);
	
	if (ano < pilotos[indice].data_nascimento.ano) {
		return -1;
	}
	
	idade = ano - pilotos[indice].data_nascimento.ano;
	
	if (pilotos[indice].data_nascimento.mes == mes) {
		if(pilotos[indice].data_nascimento.dia < dia) {
			idade--;
		}
	}
	
	if (pilotos[indice].data_nascimento.mes < mes) {
		idade--;
	}
	
	return idade;
}

int verificar_intervalo_datas(Viagem viagem, Data data_x, Data data_y) {
	Data data_viagem;
	data_viagem = viagem.data_saida;
	int retorno;
	
	if (data_x.ano <= viagem.data_saida.ano && data_y.ano >= viagem.data_saida.ano) {
		retorno = 1;
		if (data_x.ano == viagem.data_saida.ano) {
			if (data_x.mes > viagem.data_saida.mes) {
				retorno = 0;
			} else if (data_x.mes == viagem.data_saida.mes) {
				if (data_x.dia > viagem.data_saida.dia) {
					retorno = 0;
				}
			}
		}
		
		if (data_y.ano == viagem.data_saida.ano) {
			if (data_y.mes < viagem.data_saida.mes) {
				retorno = 0;
			} else if (data_y.mes == viagem.data_saida.mes) {
				if (data_y.dia < viagem.data_saida.dia) {
					retorno = 0;
				}
			}
		}
	}
	
	return retorno;
}



































