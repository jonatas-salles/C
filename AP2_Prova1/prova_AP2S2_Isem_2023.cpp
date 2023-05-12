/* PROVA PR�TICA DE AP2S2 - I SEM DE 2023 - 05/05/2023

	Coloque aqui seu nome completo e prontu�rio
	Jonatas Henrique Salles
	SC3022862
	
	ATEN��O: VOC� N�O DEVE MODIFICAR OS PROT�TIPOS DAS FUN��ES. 
	N�o ser� permitido o uso de vari�veis globais dentro das fun��es. 
*/
#include<stdio.h>
#include<locale.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
	char nome[40], cpf[15], cel[15], cidade[40]; 	
} Cliente;

/*QUEST�O 1 (1.5): Implemente a fun��o inserir_contato_cliente que recebe por par�metro um ponteiro para um vetor
com capacidade para at� 200 registros de cliente e um ponteiro para a posi��o do vetor na qual o registro 
ser� inserido pela fun��o. A fun��o dever� retornar 1, caso o contato tenha sido inclu�do com sucesso e -1, 
caso contr�rio. A mensagem informando se o contato foi inclu�do com sucesso
ou n�o ser� impressa na fun��o submenu_agenda_clientes().*/
int inserir_contato_cliente(Cliente agenda_cli[], int *i) 
{   
	printf("\nInserindo um novo contato na agenda:\n");
	
	fflush(stdin);
	printf("Nome: ");
	gets(agenda_cli[*i].nome);
	printf("CPF: ");
	gets(agenda_cli[*i].cpf);
	printf("Telefone: ");
	gets(agenda_cli[*i].cel);
	printf("Cidade: ");
	gets(agenda_cli[*i].cidade);
	
	(*i)++;
	return 1;
}

/*QUEST�O 2 (1.0): Implemente a fun��o buscar_contato_cliente que receba por par�metro um ponteiro para um vetor
com registros de clientes, o cpf do cliente e um contador, indicando a quantidade de contatos armazenados
no vetor. Caso o cpf esteja cadastrado, a fun��o dever� retornar o �ndice do registro no vetor. Caso n�o encontre,
a fun��o dever� retornar -1. A mensagem informando que o cpf do cliente n�o foi encontrado 
(quando acontecer) deve ser impressa na fun��o submenu_agenda_clientes().*/
int buscar_contato_cliente(Cliente agenda_cli[], char cpf[], int cont)
{	
	printf("\nBuscando um contato na agenda de clientes:\n");
	int i;
	for(i=0; i<cont; i++) {
		if (stricmp(agenda_cli[i].cpf, cpf) == 0) {
			return i;
		}
	}
	return -1;
	
}
/*QUEST�O 3 (1.5): Implemente a fun��o imprimir_contato_cliente() que receba por par�metro um ponteiro para um vetor
com registros de clientes e o contador de contatos cadastrados. A fun��o dever� solicitar o cpf do contato
como entrada e dever� transferir esse cpf, juntamente com o vetor agenda_cli, por par�metros para a fun��o 
buscar_contato_cliente(), que verificar� se esse cpf est� cadastrado. Se o retorno da fun��o buscar_contato_cliente() 
for maior ou igual a zero (ou seja, um �ndice v�lido), a fun��o imprimir_contato_cliente() dever� imprimir o nome, o celular,
e a cidade do cliente. Caso o retorno seja -1, a fun��o dever� apresentar uma mensagem 
informando que o cpf do cliente n�o foi localizado na agenda.*/
void imprimir_contato_cliente(Cliente agenda_cli[], int cont)
{	
	printf("\nImprimindo um contato da agenda:\n");
	printf("\nNome: %s\n", agenda_cli[cont].nome);
	printf("CPF: %s\n", agenda_cli[cont].cpf);
	printf("Telefone: %s\n", agenda_cli[cont].cel);
	printf("Cidade: %s\n", agenda_cli[cont].cidade);
}			    		

/*QUEST�O 4 (1.75): Implemente a fun��o excluir_contato_cliente() que receber� por par�metro um ponteiro para um vetor
com registros de clientes e um ponteiro para o contador de contatos cadastrados. A fun��o dever� solicitar o cpf do contato
a ser exclu�do. Em seguida dever� transferir esse cpf, juntamente com o vetor agenda_cli, por par�metro para a fun��o 
buscar_contato_cliente(), que verificar� se esse cpf est� cadastrado. Se o retorno da fun��o buscar_contato_cliente() 
for maior ou igual a zero (ou seja, um �ndice v�lido), a fun��o imprimir_contato_cliente() dever� excluir o 
contato do vetor agenda_cli. Caso o retorno seja -1, a fun��o excluir_contato_cliente
dever� apresentar uma mensagem informando que o cpf n�o foi localizado na agenda de contatos.*/
void excluir_contato_cliente(Cliente agenda_cli[], int *cont)
{	
	printf("\nExcluindo um contato da agenda:\n");
	char cpf[15];
	fflush(stdin);
	printf("Insira o CPF que deseja remover: ");
	gets(cpf);
	int encontrou, i;
	encontrou = buscar_contato_cliente(agenda_cli, cpf, *cont);

	if (encontrou != -1) {
		for (i=encontrou; i<(*cont) - 1; i++) {
			agenda_cli[i] = agenda_cli[i+1];
		}
		(*cont)--;
		printf("Removido com sucesso!\n");
	} else {
		printf("CPF n�o encontrado\n");
	}
}

/*QUEST�O 5 (1.75): Desenvolva o c�digo da fun��o imprimir_vetor() que receber� por par�metro um 
ponteiro para um vetor com 100 elementos inteiros e percorrer� esse vetor imprimindo os seus 
elementos. Para percorrer o vetor, a fun��o dever� usar 4 ponteiros (p,q,r,s) de forma SIMULT�NEA 
posicionados conforme seguem:
p: deve iniciar na posi��o 0
q: deve iniciar na posi��o 25
r: deve iniciar na posi��o 50
s: deve iniciar na posi��o 75
*/
void imprimir_vetor(int *vet)
{	
	printf("\nImprimindo o vetor de inteiros usando quatros ponteiros\n");
	
	int i, p = 0, q = 25, r = 50, s = 75, *pp = &p, *pq = &q, *pr = &r, *ps = &s;
	for (i=0; i<25; i++) {
		printf("%d ", vet[*pp]);
		printf("%d ", vet[*pq]);
		printf("%d ", vet[*pr]);
		printf("%d\n", vet[*ps]);
		
		(*pp)++;
		(*pq)++;
		(*pr)++;
		(*ps)++;
	}
	
}

/*QUEST�O 6 (1.25): Desenvolva o c�digo da fun��o preencher_vetor() que receber� um ponteiro para 
um vetor de inteiros (vazio) por par�metro e o preencher� automaticamente com 100 valores inteiros.*/
void preencher_vetor(int *vet)
{	
	printf("\nPreenchendo automaticamente o vetor de inteiros\n");
	int i = 0;
	for (i=0; i<100; i++) {
		*vet = i;
		*vet++;
	}
	
	
}

//Fun��o menu(): fun��o que apresenta o menu de op��es para o usu�rio
void menu(){
	printf("**************Menu de Op��es:****************\n\n");
	printf("\t1. Acessar submenu Agenda de Clientes\n");
	printf("\t2. Imprimir vetor de inteiros usando ponteiros\n");
	printf("\t3. Sair\n");
	printf("\nEscolha uma op��o (1 ou 2) ou digite 3 para encerrar o programa\n");
}
//Chamada das fun��es: (0.75)
void submenu_agenda_clientes(Cliente contatos[], int *cont){
	int op, flag;
	
	do
	{		
		printf("**************Submenu Agenda de Clientes:****************\n\n");
		printf("\t1. Inserir o contato de um novo cliente na Agenda\n");
		printf("\t2. Imprimir dados de um contato\n");
		printf("\t3. Remover o contato de um cliente da Agenda\n");
		printf("\t4. Voltar ao menu principal\n");
		printf("\nEscolha uma op��o entre 1 e 3 ou digite 4 para voltar ao menu principal\n");
		scanf("%d",&op);
	
		switch (op){
			case 1:
			/*INSIRA AQUI A CHAMADA DA FUN��O inserir_contato_cliente(), RESPEITANDO OS 
			PAR�METROS CONFORME O PROT�TIPO DA FUN��O*/
			inserir_contato_cliente(contatos, &(*cont));
			printf("Inserido com sucesso!\n");
			break;		
							
			case 2:
			/*INSIRA AQUI A CHAMADA DA FUN��O imprimir_contato_cliente(), RESPEITANDO OS 
			PAR�METROS CONFORME O PROT�TIPO DA FUN��O*/
			fflush(stdin);
			char cpf[15];
			printf("Insira o CPF que deseja buscar: ");
			gets(cpf);
			int encontrou;
			encontrou = buscar_contato_cliente(contatos, cpf, *cont);
			if (encontrou == -1) {
				printf("Cliente n�o encontrado\n");
			} else {
				imprimir_contato_cliente(contatos, encontrou);
			}
			break;
				
			case 3:
			/*INSIRA AQUI A CHAMADA DA FUN��O excluir_contato_cliente(), RESPEITANDO OS 
			PAR�METROS CONFORME O PROT�TIPO DA FUN��O*/
			excluir_contato_cliente(contatos, &(*cont));
			
			case 4:
				printf("Voltando para o menu principal\n");
				break;
			default: printf("Op��o incorreta!\n");
		}	
	} while(op >= 1 && op <3);
}

//Chamada das fun��es: (0.5)
main()
{	int op, cont = 0;
	Cliente contatos_cli[200];  
	setlocale(LC_ALL, "Portuguese");
		
	do
	{	
		menu();
		scanf("%d",&op);
		fflush(stdin);
		switch (op){
			case 1: system("cls");
			   //CHAMANDO O SUBMENU COM OP��ES PARA GERENCIAR AGENDA DE CLIENTES
				submenu_agenda_clientes(contatos_cli,&cont);			
				break;
			case 2: system("cls");
			   int vetor[100];
			   preencher_vetor(vetor);
			   imprimir_vetor(vetor);
			   break;	
			case 3: system("cls");
			   printf("\nEncerrando o programa...\n"); 
			   break;
			default: printf("Op��o incorreta!\n");
		}	
	} while (op >= 1 && op <3);	
}
