//Linear Simplesmente Encadeada
//autor: Adalberto dos Santos Pinheiro
/*Objetivo: implementar uma lista simplsmente encadeada para fins didaticos*/

#include<stdio.h>
#include<stdlib.h>

typedef struct no {

    int dado;
    struct no *prox;        //por ser simplismente encadeada, não possui *ant

} No;

typedef struct {

    No *inicio;
    No *fim;
    int tam;

} ListaLSE;

//funcoes de manipulacao

void cria(ListaLSE *l);
int insere(ListaLSE *l, int dado);
int retira(ListaLSE *l, int dado);

//funcoes de visualizacao

int estaVazia(ListaLSE l);
int getTamanho(ListaLSE l);
void mostra(ListaLSE);
int verifica(ListaLSE l, int dado);


int main(){

    ListaLSE l;
    int dado, sucesso, opcao;

    cria(&l);

    //INSERINDO DESORDENADO
    sucesso = insere(&l, 400); // eu optei por nao verificar se houve sucesso na insercao
    sucesso = insere(&l, 250);
    sucesso = insere(&l, 666);
    sucesso = insere(&l, 5000);
    sucesso = insere(&l, 10);
    if(!estaVazia(l)){ //exibindo a lista
        printf("\n-------------------------------------------------\n");
        mostra(l);
    }
    opcao = 1;
    while(opcao == 1){ // remover ate o usuario nao querer mais


        printf("\n-------------------------------------------------\n");
        printf("Qual dado deseja remover? ");
        scanf("%d", &dado);
        getchar();

        verifica(l, dado);
        sucesso = retira(&l, dado); // removo o elemento solicitado pelo usuario
        if(!sucesso)
            printf("FALHA EM REMOVER: %d\n\n", dado);
        else{
            printf("Removido com sucesso\n");
            mostra(l); // exibo a lista atualizada
        }
            
            if(!estaVazia(l)){
            printf("\nDeseja remover mais algum elemento? \n1 - sim \n2 - nao\n");
            scanf("%d", &opcao);
            getchar();
            }
            else
            return 0;
    }
return 0; 
}

void cria(ListaLSE *l){

    l->inicio = NULL;
    l->fim = NULL;
    l->tam = 0;
}

int insere(ListaLSE *l, int dado){

    // alocando no na memoria e checando se deu certo
    No *aux = (No *) malloc(sizeof(No));

    if(aux == NULL)
        return 0;

    // guardando o dado e incrementando o tamanho da lista
    aux->dado = dado;
    l->tam++;

    // 1o caso: primeiro elemento
    if(l->inicio == NULL){

        l->inicio = aux;
        l->fim = aux;
        aux->prox = NULL;

        return 1;
    }
    else{
        // 2o caso: ja ha elementos, insere no fim
        l->fim->prox = aux;
        aux->prox = NULL;
        l->fim = aux;
        return 1;
    }
}

int verifica(ListaLSE l, int dado){
    No *aux;

    aux = l.inicio;
    while(aux->prox != NULL){
        aux = aux->prox;
        if(dado == aux->dado){
            printf("Dado encontrado!\n");
            return 1;
        }
        if(aux->prox == NULL && aux->dado != dado)
        printf("Dado nao encontrado\n");
        return 0;          
    }
    return 0;
}

int retira(ListaLSE *l, int dado){

    No *aux ;

    if(l->inicio == NULL){
        printf("Lista vazia\n");
        return 0;
    }

    /* 1o caso: lista unitaria */
    if((dado == l->inicio->dado) && (l->inicio == l->fim)) {
        aux = l->inicio; // aux aponta para o no que vou remover
        l->inicio = NULL; //inicio aponta pra null
        l->fim = NULL; // fim aponta pra null
        free(aux); // libero a memoria
        printf("Dado unitario removido com sucesso.\n");
        l->tam--;

        return 1;
    }

    /* 2o caso: removendo primeiro elemento */
    if(dado == l->inicio->dado ) {

        aux = l->inicio; // aux aponta para o no que vou remover
        l->inicio = aux->prox; //inicio aponta para o novo inicio (o segundo elemento)
        free(aux); //libero memoria
        printf("Dado removido com sucesso..\n");
        l->tam--;

        return 1;
    }

    /* 3o caso: removendo ultimo elemento */
    else if(dado == l->fim->dado) {

        No *ant = NULL;

        aux = l->inicio;

        while(aux != NULL){            
            if(dado == aux->dado)
                break;
            ant = aux;
            aux = aux->prox;
                    
        }
        
        l->fim = ant;
        ant->prox = NULL;
        free(aux); //libero a memoria
        printf("Dado removido com sucesso.\n");
        l->tam--;

        return 1;
    }

    /* 4o caso: removendo elemento no meio */
    else {
        No *ant = NULL;
        No *aux = l->inicio;

        while (aux != NULL && aux->dado != dado) {
            ant = aux;
            aux = aux->prox;
        }

        if (aux == NULL) {
            printf("Dado nao encontrado.\n");
            return 0;
        }

        if (ant == NULL) {
            l->inicio = aux->prox;
        } else {
            ant->prox = aux->prox;
        }

        printf("Dado removido.\n");
        free(aux);
        return 1;
    }
     free(aux);
}

int estaVazia(ListaLSE l){

    if(l.inicio == NULL)
        return 1;

    return 0;
}

int getTamanho(ListaLSE l){

    return l.tam;
}

void mostra(ListaLSE l){

    No *aux;

    if(l.inicio == NULL)// lista vazia, nao mostra nada
            printf("Lista vazia!\n\n");

    else { // lista possui elementos, mostra dependendo do sentido

        printf("\n-------------------------------------------------\n");
        printf("Mostrando Lista\n\n");
        // percorrendo do inicio ao fim
            aux = l.inicio;
            while(aux != NULL){
                printf("Dado: %d\n", aux->dado);
                aux = aux->prox;
            }
    }
}
