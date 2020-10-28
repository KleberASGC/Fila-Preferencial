#include "filapreferencial.h"

PFILA criarFila(){
	PFILA res = (PFILA) malloc(sizeof(FILAPREFERENCIAL));
	res->inicio = NULL;
	res->fimPref = NULL;
	res->inicioNaoPref = NULL;
	res->fim = NULL;
	return res;
}

int tamanho(PFILA f){
	PONT atual = f->inicio;
	int tam = 0;
	while (atual) {
		atual = atual->prox;
		tam++;
	}
	return tam;
}

PONT buscarID(PFILA f, int id){
	PONT atual = f->inicio;
	 while (atual) {
		if (atual->id == id) return atual;
		atual = atual->prox;
	}
	return NULL;
}

void exibirLog(PFILA f){
	int numElementos = tamanho(f);
	printf("\nLog fila [elementos: %i] - Inicio:", numElementos);
	PONT atual = f->inicio;
	while (atual){
		printf(" [%i;%i]", atual->id, atual->idade);
		atual = atual->prox;
	}
	printf("\n\n");
}


int consultarIdade(PFILA f, int id){
	PONT atual = f->inicio;
	 while (atual) {
		if (atual->id == id) return atual->idade;
		atual = atual->prox;
	}
	return -1;
}



bool inserirPessoaNaFila(PFILA f, int id, int idade){
if (idade < 0 || id < 0 || buscarID(f,id) != NULL) return false;
PONT novo;
if (idade < IDADEPREFERENCIAL) {
	novo = (PONT) malloc(sizeof(ELEMENTO));
	if (f->inicio == NULL) {
		f->inicio = novo;;
		f->fim = novo;
		f->inicioNaoPref = novo;
		novo->id = id;
		novo->idade = idade;
		novo->prox = NULL;
		return true;
	}
	novo->id = id;
	novo->idade = idade;
	novo->prox = NULL;
	f->fim->prox = novo;
	f->fim = novo;
	if(f->inicioNaoPref == NULL) f->inicioNaoPref = novo;
	return true;
}
if (idade >= IDADEPREFERENCIAL) {
	novo = (PONT) malloc (sizeof(ELEMENTO));
	if (f->inicio == NULL) {
		f->inicio = novo;
		f->fim = novo;
		f->fimPref = novo;
		novo->id = id;
		novo->idade = idade;
		novo->prox = NULL;
		return true;
	}
	if (f->fimPref == NULL) { 
	 	f->fimPref = novo;
	 	f->inicioNaoPref = f->inicio;
	 	f->inicio = novo;
	}
	f->fimPref->prox = novo;
	novo->id = id;
	novo->idade = idade;
	novo->prox = f->inicioNaoPref;
	f->fimPref = novo;
	return true;
} 

}

bool atenderPrimeiraDaFila(PFILA f, int* id){
	if(f->inicio == NULL) return false; 
	PONT atender;
	*id = f->inicio->id;
	atender = f->inicio;
	if (f->inicio == f->fim) {
	f->inicio = NULL;
	f->fim = NULL;
	f->fimPref = NULL;
	f->inicioNaoPref = NULL;
	free (atender);
	return true;
	}
	if (f->inicio == f->fimPref) {
		f->fimPref = NULL;
		f->inicio = f->inicioNaoPref;
		free (atender);
		return true;
	}
	f->inicio = f->inicio->prox;
	free (atender);
	if (f->inicio == NULL) {
	 f->fim = NULL;
	 f->fimPref = NULL;
	 f->inicioNaoPref = NULL;
	}
	return true;
} 

int descobrePos(PFILA f, int id){
	PONT atual = f->inicio;
	int i = 0;
	 while (atual) {
		if (atual->id == id) return i;
		atual = atual->prox;
		i++;
	}
	return -1;
}

PONT descobreProx(PFILA f, int pos) {
	PONT atual = f->inicio;
	int i = 0;
	while (i < pos) {
		atual = atual -> prox;
		i++;
	}
	if (atual == NULL) return NULL;
	return atual->prox;
}

bool desistirDaFila(PFILA f, int id){
	if (buscarID(f,id) == NULL) return false;
	int i, j;
	PONT apagar = buscarID(f,id); 
	PONT ant;
	if (apagar == f->inicio && apagar == f->fim) {
		f->inicio = NULL;
		f->fim = NULL;
		f->fimPref = NULL;
		f->inicioNaoPref = NULL;
		free(apagar);
		return true;
	}
	if (apagar == f->inicio) {
		f->inicio = apagar->prox;
		free(apagar);
		return true;
	}
	if (apagar == f->fimPref) {
		i = descobrePos(f,id-2);
		f->fimPref = descobreProx(f,i);
		f->fimPref->prox = f->inicioNaoPref;
		free(apagar);
		return true;
	}
	if (apagar == f->inicioNaoPref) {
		f->fimPref->prox = f->inicioNaoPref->prox;
		free(apagar);
		return true;
	}
	if (apagar == f->fim) {
		i = descobrePos(f,id-1);
		ant = descobreProx(f,i);
		ant = NULL;
		j =  descobrePos(f,id-2);
		f->fim = descobreProx(f, j);
		free(apagar);
		return true;
	}
	i = descobrePos(f,id-1);
	ant = descobreProx(f,i);
	ant = apagar->prox;
	free(apagar);
	return true; 
}
