#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#define EMER 5
#define TAMVETOR 2
#define TAMINSERCOES 4

int atendimentos = 0, atendimentosEmergencia = 0;

typedef struct Node{//gera o tipo node
	int chave;
	int prioridade;
	struct Node *prox;
}node;

void inicia(node *FILA){//inicia a fila
	FILA->prox = NULL;
}

int vazia(node *FILA){//verifica se a fila esta vazia
	if(FILA->prox == NULL)
		return 1;
	else
		return 0;
}

node *aloca(int x){//aloca espaço e gera a chave
	node *novo = (node *) malloc(sizeof(node));

	if(!novo){
		printf("Sem memoria disponivel!\n");
		exit(1);
	}

	else if(x == 2){
		novo->chave = geraId(2);
		return novo;
	}

	else if(x == 1){
		novo->chave = geraId(1);
		if(emergencia(novo->chave)){
            novo->prioridade = 0;
		}

		else{
            novo->prioridade = 2;
		}
		return novo;
	}
}

void insere(node *FILA, int x){//insere o dado na fila
    if(x == 2){
        node *novo = aloca(2);
        novo->prox = NULL;

	if(vazia(FILA))
		FILA->prox=novo;
	else{
		node *tmp = FILA->prox;
        node *ant = FILA;

        //VERIFICA A PRIORIDADE E SE O ITEM NÃO É NULO
		while((tmp != NULL) && (tmp->prioridade <= novo->prioridade)){
			ant = tmp;
			tmp = tmp->prox;
		}

        //FAZ OS APONTAMENTOS CORRETOS INDEPENDENTE DA POSIÇÃO DO ITEM
        novo->prox = ant->prox;
        ant->prox = novo;

	}
    }

    if(x == 1){
        node *novo = aloca(1);
        novo->prox = NULL;

	if(vazia(FILA))
		FILA->prox=novo;
	else{
		node *tmp = FILA->prox;
        node *ant = FILA;

        //VERIFICA A PRIORIDADE E SE O ITEM NÃO É NULO
		while((tmp != NULL) && (tmp->prioridade <= novo->prioridade)){
			ant = tmp;
			tmp = tmp->prox;
		}

        //FAZ OS APONTAMENTOS CORRETOS INDEPENDENTE DA POSIÇÃO DO ITEM
        novo->prox = ant->prox;
        ant->prox = novo;

	}
    }

}

node *retira(node *FILA){//retira item da fila
	if(FILA->prox == NULL){
		return NULL;
	}else{
		node *tmp = FILA->prox;
		FILA->prox = tmp->prox;

		return tmp;
	}
}

void exibeA(node *FILA){//com condição de emergência(aterrissagem)
	if(vazia(FILA)){
		printf("Fila vazia!\n\n");
		return ;
	}

	node *tmp;
	tmp = FILA->prox;

	while(tmp != NULL){
        if(emergencia(tmp->chave)){
            printf("[*%d] ", tmp->chave);
        }
        else{
            printf("[%d] ", tmp->chave);
        }

		tmp = tmp->prox;
	}

	printf("\n\n");
}

void exibeD(node *FILA){//sem condição de emergência (decolagem)
	if(vazia(FILA)){
		printf("Fila vazia!\n\n");
		return ;
	}

	node *tmp;
	tmp = FILA->prox;

	while(tmp != NULL){
		printf("[%d] ", tmp->chave);
		tmp = tmp->prox;
	}

	printf("\n\n");
}

void libera(node *FILA){//não utilizado
	if(!vazia(FILA)){

		node *proxNode, *atual;

		atual = FILA->prox;

		while(atual != NULL){
			proxNode = atual->prox;
			free(atual);
			atual = proxNode;
		}
	}
}

int qtdIn(){//função que define número de inserções aleatóriamente
    int qtd;
    qtd = rand()%TAMINSERCOES;
    return qtd;
}

int geraId(int x){//função que gera id aleatória
    int num,parImpar;

    if(x == 2){
        do{
            num = rand()%1000+1;
            //printf("\n%i\n", t);
            parImpar = num%2;
          }while(parImpar != 0);
        //printf("\n%i\n", num);
        return num;
    }

    if(x == 1){
        do{
            num = rand()%1000+1;
            //printf("\n%i\n", t);
            parImpar = num%2;
          }while(parImpar == 0);
        //printf("\n%i\n", num);
        return num;
    }
}

int emergencia(int id){//emergência aleatória
    int soma=0;

    while(id>0){
        soma+=id%10;
        id/=10;
    }

    if(soma == EMER)
        return 1;
    else
        return 0;
}

int tamanho(node *FILA){//retorna o número de itens na lista
    int tam = 0;
    if(vazia(FILA)){
		return 0;
	}

	node *tmp;
	tmp = FILA->prox;

	while(tmp != NULL){
		tam++;
		tmp = tmp->prox;
	}

	return tam;
}

int pistas(node *decolagem, node *aterrissagem, int pista[]){//controle das aeronaves
    int tamDecolagem; //= tamanho(decolagem);
    int tamAterrissagem; //= tamanho(aterrissagem);
    int a;

    for(a = 0;a < TAMVETOR+1;a++){
        tamDecolagem = tamanho(decolagem);
        tamAterrissagem = tamanho(aterrissagem);

        if(vazia(decolagem)==0 && vazia(aterrissagem)==0){//duas filas estão ocupadas
            if(tamDecolagem > tamAterrissagem+3 && emergencia(pista[a]) == 0){
                pista[a] = retira(decolagem)->chave;
            }

            else{
                pista[a] = retira(aterrissagem)->chave;
            }
        }

        else if(vazia(decolagem)==0 && vazia(aterrissagem)){//aterrissagem vazia
            pista[a] = retira(decolagem)->chave;
        }

        else if(vazia(decolagem) && vazia(aterrissagem)==0){//decolagem vazia
            pista[a] = retira(aterrissagem)->chave;
        }

        else{//ambas vazias
            pista[a] = retira(aterrissagem);
        }
    }

    return pista;
}

void imprimePistas(int pista[]){
    int a;

    for(a = 0;a < TAMVETOR+1;a++){
        if(pista[a]!=0){
            if(pista[a]%2==0){
                printf("\nPista %d: [%d] (DECOLANDO)", a+1, pista[a]);
                atendimentos++;
            }

            else{
                if(emergencia(pista[a])){
                    printf("\nPista %d: [*%d] (ATERRISSANDO EM EMERGÊNCIA)", a+1, pista[a]);
                    atendimentosEmergencia++;
                }

                else{
                    printf("\nPista %d: [%d] (ATERRISSANDO)", a+1, pista[a]);
                    atendimentos++;
                }
            }
        }

        else{
            printf("\nPista %d: (VAZIA)", a+1);
        }

    }

    printf("\n\nAviões atendidos: %d\n", atendimentos);
    printf("Aviões em emergência: %d\n", atendimentosEmergencia);

}

int main(void){//rotina principal
    int inAterrissagem, inDecolagem, a, vetor[TAMVETOR]; //ctdPrioridade=0;
	node *decolagem = (node *) malloc(sizeof(node));
	node *aterrissagem = (node *) malloc(sizeof(node));

	srand(time(NULL));
	setlocale(LC_ALL, "");

	if(!decolagem || !aterrissagem){
		printf("Sem memoria disponivel!\n");
		exit(1);
	}
	else{

        inicia(decolagem);
        inicia(aterrissagem);
	}

    do{
        system("cls");

        //define quantidade de inserções
        inDecolagem = qtdIn();
        inAterrissagem = qtdIn();

        for (a = 0;a < inDecolagem;a++){//loop inserção decolagem
            insere(decolagem,2);
        }

        for (a = 0;a < inAterrissagem;a++){//loop inserção aterrissagem
            insere(aterrissagem,1);
        }

        //envia as filas para retirar aviões e o vetor da pista para receber as ids dos aviões
        pistas(decolagem,aterrissagem,vetor);

        //imprime as filas
        printf("Fila de decolagem:");
        exibeD(decolagem);
        printf("\nFila de aterrissagem: ");
        exibeA(aterrissagem);

        //imprime as filas
        imprimePistas(vetor);

        getch();
    } while(1);


    return 0;

}


