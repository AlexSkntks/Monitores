#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <time.h>
#include "SalaDeServico.h"

void* gatos(void* args){
	int t = (rand()%5)+1;
	printf("[GATO %d] preciso ir ao petShop...Estou na fila\n", (int)args);
	um_gato_quer_servico();
	printf("[GATO %d] Consegui entrar na sala de servico.\n", (int)args);
	sleep(t);
	gato_atendido();
	printf("[GATO %d]Estou saindo da sala de servico\n", (int)args);

}


void* caes(void* args){
	int t = (rand()%5)+1;
	printf("[CAO %d] preciso ir ao petShop...Estou na fila\n", (int)args);
	um_cao_quer_servivo();
	printf("[CAO %d] Consegui entrar na sala de servico.\n", (int)args);
	sleep(t);
	cao_atendido();
	printf("[CAO %d]Estou saindo da sala de servico\n", (int)args);
	
}


int main(){

	/*Cães*/
	int n_caes;
	int n_gatos;
	int tamSala;

	pthread_t tid_gatos[n_gatos], tid_caes[n_caes];

	printf("Digite o tamanho da sala de servico, e quantidade de caes e de gatos: ");
	scanf("%d%d%d", &tamSala, &n_caes, &n_gatos);
	
	if(inicializaSala(tamSala, n_caes, n_gatos) == -1){
		return 1;
	}

	/*Criando todas as threads*/

	for(int i = 0; i < n_gatos; i++){
		if(pthread_create(&tid_gatos[i], NULL, gatos, (void*)(i+5)) != 0) return 3;
	}
	for(int i = 0; i < n_caes; i++){
		if(pthread_create(&tid_caes[i], NULL, caes, (void*)i) != 0) return 2;
	}

	/*Esperando por todas as threads*/
	for(int i = 0; i < n_caes; i++){
		if(pthread_join(tid_caes[i], NULL) != 0) return 4;
	}
	for(int i = 0; i < n_gatos; i++){
		if(pthread_join(tid_gatos[i], NULL) != 0) return 5;
	}

	desalocaEstruturas();
	return 0;
}