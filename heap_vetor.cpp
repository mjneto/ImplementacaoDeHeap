/*	UNIVERSIDADE FEDERAL DO PARÁ
	****** **** Neto
	Ingrid *******
	Belém, 31/01/2017
	PROGRAMA DE IMPLEMENTAÇÃO DE HEAP COM VETOR	*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <locale.h>

//Referência das funções, para funcionarem em ordem diferente
int dez_val(int[], int);
void const_heap(int[], int);
void menu();
void mostrar(int[], int);
int imprime(int[], int, int, int);
void imprime_vetor(int[], int);
int inserir(int[], int);
int remover(int[], int);
void subir(int, int[]);
void descer(int, int[], int);
void heapsort(int[], int);

//declaração global do vetor usado, facilitando a passagem em funções
int fila[100];
int tam_heap = -1; //-1 para o indice começar em zero (tam_heap++ = 0 na função de valores aleatórios)

int main () {
	setlocale(LC_ALL, "Portuguese"); //suporte para ç, acentos e afins

	tam_heap = dez_val(fila, tam_heap);
	const_heap(fila, tam_heap);
	menu();
}

int dez_val(int fila[], int tam_heap) { //Alimentar o vetor com 10 valores aleatórios
	int x, i;

    srand((unsigned)time(NULL)); //função aleatória

    printf("---------IMPLEMENTAÇÃO EM HEAP----------\n");
	printf("Iniciando dez valores aleatórios...\n");
    for(i = 0 ; i < 10 ; i++) {
    	x = 10 + (rand() % 90); //entre 10 e 99
		fila[i] = x;
		printf("%i ", fila[i]);
		tam_heap++;
	}
	printf("\n\nContinue ");
	getchar();
	system("cls");
	return (tam_heap);
}

void const_heap(int fila[], int tam_heap) {
	int i;

	for(i = 1; i < 10; i++) {
        printf("---------IMPLEMENTAÇÃO EM HEAP----------\n");
        printf("Construção do heap...\n");
		mostrar(fila, tam_heap); //Mostra antes da mudança
		subir(i, fila);
        mostrar(fila, tam_heap); //Depois da mudança
        if(i != 9) {
            printf("Continue...");
        }
        else {
            printf("Finalizado...");
        }
        getchar();
        system("cls");
	}
}

void menu() {
	int op;

	do {
		printf("---------IMPLEMENTAÇÃO EM HEAP----------\n\n");
		printf("Mostrar ---------------------------- [1]\n");
		printf("Inserir ---------------------------- [2]\n");
		printf("Remover ---------------------------- [3]\n");
		printf("Heapsort --------------------------- [4]\n");
		printf("Sair ------------------------------- [0]\n");
		printf("\n>> ");
		scanf("%i", &op);
		fflush(stdin);
		system("cls");

		switch(op) {
			case 1:
			    printf("---------IMPLEMENTAÇÃO EM HEAP----------\n");
			    printf("[1] --------- Mostrar Heap -------------\n");
				mostrar(fila, tam_heap);
				imprime_vetor(fila, tam_heap);
				printf("\nContinue...");
				getchar();
				system("cls");
				break;
			case 2:
			    printf("---------IMPLEMENTAÇÃO EM HEAP----------\n");
			    printf("[2] ------------ Inserir ---------------\n\n");
			    tam_heap = inserir(fila, tam_heap);
			    printf("Continue...");
			    getchar();
			    system("cls");
				break;
			case 3:
			    printf("---------IMPLEMENTAÇÃO EM HEAP----------\n");
			    printf("[3] ------------ Remover ---------------\n\n");
			    tam_heap = remover(fila, tam_heap);
			    printf("Continue...");
			    getchar();
			    system("cls");
				break;
			case 4:
                printf("---------IMPLEMENTAÇÃO EM HEAP----------\n");
			    printf("[4] ------------ HeapSort --------------\n\n");
			    heapsort(fila, tam_heap);
			    printf("\nContinue...");
			    getchar();
			    system("cls");
				break;
			case 0:
			    printf("---------IMPLEMENTAÇÃO EM HEAP----------\n");
			    printf("[0] --------------- Sair ---------------\n\n");
				op = 0;
				printf("! TERMINADO !\n");
				getchar();
				break;
		}
	} while((op < -1 && op > 4) || op != 0);
}

void mostrar(int fila[], int tam_heap) {
	int x = 1, i = 0, esp, tab, aux;

	printf("\n");
	esp =  floor(tam_heap * 1.7);
	tab = esp;
	do {
		do {
			printf(" ");
			tab--;
		} while(tab > 0);
		i = imprime(fila, i, x, esp);
		x = 2 * x;
		printf("\n");
		esp = floor(esp/2);
		tab = esp;
	} while(i <= tam_heap);
    //cmd em tela cheia e entrada de valores com 2 digitos são recomendados
}

int imprime(int fila[], int i, int x, int esp) { //imprime() é apenas complemento de mostrar
	int contr;

	do {
		if(i > 0) {
			contr = esp;
			printf("%i", fila[i]);
			do {
				printf("  ");
				contr--;
			} while(contr > 0);
		}
		else {
			printf("%i", fila[i]);
		}
		i++; //incrementa para manter as posições do vetor
		x--; //decrementa somente nesta função
	} while(x > 0 && fila[i] != NULL);
	printf("\n");
	return (i);
}

void imprime_vetor(int fila[], int tam_heap) { //imprime_vetor() é apenas complemento
    int i;

    printf("Em vetor: ");
    for(i = 0; i <= tam_heap; i++) {
        printf("%i:[%i] ", i, fila[i]);
    }
    printf("\n");
}

int inserir(int fila[], int tam_heap) {
    int novo = 0;

    printf("Insira um número: ");
    scanf("%i", &novo);
    fflush(stdin);
    if(tam_heap <= 100) { //verifica se não está cheio
        fila[tam_heap+1] = novo;
        tam_heap++;
        mostrar(fila, tam_heap);
        subir(tam_heap, fila);
        printf("\n");
        mostrar(fila, tam_heap);
    }
    else {
        printf("Atenção - HEAP CHEIO!");
    }
    return(tam_heap);
}

int remover(int fila[], int tam_heap) { //apenas remove o de maior prioridade
    if(tam_heap != -1) { //verifica se não está vazio
        mostrar(fila, tam_heap);
        printf("%i troca com a ultima posição %i, e é removido\n", fila[0], fila[tam_heap]);
        fila[0] = fila[tam_heap];
        fila[tam_heap] = NULL;
        tam_heap--;
        mostrar(fila, tam_heap);
        getchar();
        descer(0, fila, tam_heap);
        mostrar(fila, tam_heap);
    }
    else {
    	printf("Atenção - HEAP VAZIO!\n\n");
	}
    return(tam_heap);
}

void subir(int i, int fila[]) { //sobe o elemento i no heap
	int j, aux;

	j = floor((i-1)/2);
	printf("Indice Pai: %i - ", j);
	printf("Indice Filho: %i -> ", i);
	if(j >= 0) { //Se i tem pai e que seja maior que i
		if(fila[i] > fila[j]) {
			printf("Troca %i com %i\n", fila[i], fila[j]);
			aux = fila[i];
			fila[i] = fila[j];
			fila[j] = aux;
			subir(j, fila); //e continua a subir...
		}
		else {
			printf("Não troca\n");
        }
    }
}

void descer(int i, int fila[], int tam_heap){
    int j, aux; //indice do filho de i e aux utilizada na troca

    j = (2 * i) + 1;
    if(j <= tam_heap) { //se i tem filhos
        if(j < tam_heap) {
            if (fila[j+1] > fila[j]) { //a procura do maior filho
                j++;
            }
        }
        printf("Indice Pai: %i - ", i);
        printf("Indice Filho: %i -> ", j);
        if(fila[i] < fila[j]) { //... e compara com o pai
            printf("Troca %i com %i\n", fila[i], fila[j]);
            aux = fila[i];
			fila[i] = fila[j]; //troca
			fila[j] = aux;
			descer(j, fila, tam_heap); //e continua a descer...
        }
        else {
            printf("Não troca\n");
        }
    }
}

void heapsort(int fila[], int tam_heap) {
    int i, m, heapsort[100], aux; //outros vetor e tam_heap apenas para heapsort

	if(tam_heap != -1) {
        printf("Criando HeapSort a partir deste heap\n");
        mostrar(fila, tam_heap);
	    m = tam_heap;
	    for(i = 0; i < 100; i++) {
	        heapsort[i] = fila[i];
	    }
	    do {
	        getchar();
	       	system("cls");
	        printf("---------IMPLEMENTAÇÃO EM HEAP----------\n");
	        printf("[4] --- HeapSort\n\n");
	        printf("Trocando posições 0 e %i (indices)\n", m);
	        mostrar(heapsort, tam_heap); //antes da troca
	        aux = heapsort[0];
			heapsort[0] = heapsort[m]; //troca o primeiro com o ultimo, pela definição de heapsort
			heapsort[m] = aux;
			mostrar(heapsort, tam_heap); //depois da troca
	        m--; //decrementa o tamanho do heapsort
	        printf("Aplicado descida\n\n");
	       	descer(0, heapsort, m);
	       	mostrar(heapsort, tam_heap); //depois da descida
	    } while(m > 0);
	    imprime_vetor(heapsort, tam_heap);
	}
	else {
		printf("Atenção - HEAP VAZIO!\n\n");
	}
}
