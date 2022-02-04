#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "MonitorBanheiro.h"

#define MAX 5

void* thread_flamenguista(void *id) // cada flamenguista terá um identificador de 1 a 10
{
	while (1){
		printf ("Eu sou o(a) flamenguista%d:...Estou apertado(a)! Vou no banheiro!\n",(int)id); 
		flamenguistaQuerEntrar();
		printf ("Eu sou flamenguista-%d: ... UFA! Entrei no banheiro!\n",(int)id);
		sleep(5);
		flamenguistaSai();
		printf ("Eu sou flamenguista-%d: ... Estou aliviado! Vou torcer!\n", (int)id); sleep(5);
	}
}


void* thread_vascaino(void *id) // cada flamenguista terá um identificador de 1 a 10
{
	while (1){
		printf ("Eu sou o(a) vascaino%d:...Estou apertado(a)! Vou no banheiro!\n",(int)id); 
		vascainoQuerEntrar();
		printf ("Eu sou vascaino-%d: ... UFA! Entrei no banheiro!\n",(int)id);
		sleep(5);
		vascainoQuerSair();
		printf ("Eu sou vascaino-%d: ... Estou aliviado! Vou torcer!\n", (int)id); sleep(5);
	}
}

int main(){

	pthread_t flamenguistaID[MAX];
	pthread_t vascainoID[MAX];

	for(int i = 0; i < MAX; i++){
		pthread_create(&flamenguistaID[i], NULL, thread_flamenguista, (void*)i);
		pthread_create(&vascainoID[i], NULL, thread_vascaino, (void*)5+i);
	}

	for(int i = 0; i < MAX; i++){
		pthread_join(flamenguistaID[i], NULL);
	}
	for(int i = 0; i < MAX; i++){
		pthread_join(vascainoID[i], NULL);
	}
	return 0;
}